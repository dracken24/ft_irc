/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircMemory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:54:30 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/25 13:06:01 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcMemory.hpp"

void	Ftoa(float n, char *res, int afterpoint);

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

IrcMemory::IrcMemory(void)
{
	_memSystem.allocCount = 0;
	_memSystem.stats.allocTotal = 0;

	for (int i = 0; i < IRC_MEMORY_TAG_MAX_TAGS; i++)
		_memSystem.stats.allocTagged[i] = 0;

	_memoryTagStrings.push_back("              UNKNOWN     : ");
	_memoryTagStrings.push_back("              APPLICATION : ");
	_memoryTagStrings.push_back("              SERVER      : ");
	_memoryTagStrings.push_back("              CLIENTS     : ");
	_memoryTagStrings.push_back("\n              TOTAL       : ");
}

IrcMemory::IrcMemory(IrcMemory const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

IrcMemory	&IrcMemory::operator=(IrcMemory const &copy)
{
	if (this != &copy)
	{
		_memSystem.allocCount = copy._memSystem.allocCount;
		_memSystem.stats.allocTotal = copy._memSystem.stats.allocTotal;

		for (int i = 0; i < IRC_MEMORY_TAG_MAX_TAGS; i++)
			_memSystem.stats.allocTagged[i] = copy._memSystem.stats.allocTagged[i];
	}

	return *this;
}

IrcMemory::~IrcMemory(void)
{
	
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

void	*IrcMemory::Mallocate(uint64 size, memoryTag tag, class Logger *log)
{
	if (tag == IRC_MEMORY_TAG_UNKNOWN)
	{
		log->WARNING("Mallocate called using IRC_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	_memSystem.stats.allocTotal += size;
	_memSystem.stats.allocTagged[tag] += size;
	_memSystem.allocCount++;

	void *block = new char[size];

	return block;
}

void*	IrcMemory::CopyMemory(void* dest, const void* source, uint64 size)
{
	return std::memcpy(dest, source, size);
}

std::string	IrcMemory::GetMemoryUsageStr(void)
{
	const uint64 gib = 1024 * 1024 * 1024;
	const uint32 mib = 1024 * 1024;
	const uint16 kib = 1024;
	char tmp[32];

	static std::string buffer;
	buffer.clear();
	buffer = "------------------------------\n";
	buffer += "              Memory in use for the engine :\n\n";

	for (uint32 i = 0; i <= IRC_MEMORY_TAG_MAX_TAGS; ++i)
	{
		char unit[4] = " Xb";
		float amount = 1.0f;

		if (i < IRC_MEMORY_TAG_MAX_TAGS)
			amount = (float)_memSystem.stats.allocTagged[i];
		else
			amount = (float)_memSystem.stats.allocTotal;

		if (_memSystem.stats.allocTagged[i] >= gib || (_memSystem.stats.allocTotal
			>= gib && i >= IRC_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'G';
			amount /= (float)gib;
		}
		else if (_memSystem.stats.allocTagged[i] >= mib || (_memSystem.stats.allocTotal
			>= mib && i >= IRC_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'M';
			amount /= (float)mib;
		}
		else if (_memSystem.stats.allocTagged[i] >= kib || (_memSystem.stats.allocTotal
			>= kib && i >= IRC_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'K';
			amount /= (float)kib;
		}
		else
		{
			unit[1] = 'B';
			unit[2] = 0;
		}
		Ftoa(amount, tmp, 4);
		buffer += _memoryTagStrings.at(i).c_str();
		buffer += tmp;
		buffer += unit;
		buffer += "\n";
	}
	buffer += "\n              NBR OF ALLOC: ";
	Ftoa(static_cast<float>(_memSystem.allocCount), tmp, 0);
	buffer += tmp;
	buffer += "\n              ------------------------------\n";

	return (buffer);
}

uint64	IrcMemory::GetMemoryAllocCount(void)
{
	return _memSystem.allocCount;
}
