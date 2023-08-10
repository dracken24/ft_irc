/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMemory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:54:37 by nadesjar          #+#    #+#             */
/*   Updated: 2023/07/26 20:59:11 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMEMORY_HPP 
# define DEMEMORY_HPP

# include "../includes/defines.hpp"
# include "Logger.hpp"

# include <iostream>
# include <string>
# include <vector>

typedef enum	memoryTag
{
	IRC_MEMORY_TAG_UNKNOWN,
	IRC_MEMORY_TAG_APPLICATION,
	IRC_MEMORY_TAG_SERVER,
	IRC_MEMORY_TAG_CLIENTS,

	IRC_MEMORY_TAG_MAX_TAGS
}	memoryTag;

typedef struct memoryStats
{
	uint64	allocTotal;								// Total Bits allocate
	uint64	allocTagged[IRC_MEMORY_TAG_MAX_TAGS];	// Each cathegory
}	memoryStats;

typedef struct	memorySystemState
{
	struct memoryStats	stats;
	uint64				allocCount;	// Nbr of allocation
}	memorySystemState;

class IrcMemory
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//

	public:
		IrcMemory(void);
		IrcMemory(IrcMemory const &copy);
		IrcMemory &operator=(IrcMemory const &copy);
		~IrcMemory(void);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		void		*Mallocate(uint64 size, memoryTag tag, class Logger *log);

		template <typename T>
		void 		FreeMem(T block, uint64 size, memoryTag tag)
		{
			if (tag == IRC_MEMORY_TAG_UNKNOWN)
			{
				std::cerr << "FreeMem called using IRC_MEMORY_TAG_UNKNOWN. Re-class this allocation." << std::endl;
			}

			_memSystem.stats.allocTotal -= size;
			_memSystem.stats.allocTagged[tag] -= size;
			_memSystem.allocCount--;

			delete block;
		}

		void		*CopyMemory(void* dest, const void* source, uint64 size);

		std::string	GetMemoryUsageStr(void);

		uint64		GetMemoryAllocCount(void);

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//

	private:
		memorySystemState			_memSystem;

		std::vector<std::string>	_memoryTagStrings;
};

#endif
