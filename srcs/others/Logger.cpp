/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <nadesjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:28 by nadesjar          #+#    #+#             */
/*   Updated: 2023/07/03 12:52:14 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include <cstdarg>

void	PlatconsoleWriteError(std::string message, uint8 color);
void	PlatconsoleWrite(std::string message, uint8 color);
void	Ftoa(float nbr, char *destination, int afterpoint);

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

Logger::Logger(void)
{

}

Logger::Logger(Logger const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

Logger &Logger::operator=(Logger const &copy)
{
	if (this != &copy)
	{
	}

	return (*this);
}

Logger::~Logger(void)
{
	
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

void	Logger::LogMessage(logLevel level, const char *message, ...)
{
	const char	*levelStr[6] = {"[*FATAL*]   : ", "[*ERROR*]   : ", "[*WARNING*] : ",
		"[*INFO*]    : ", "[*DEBUG*]   : ", "[*TRACE*]   : "};
	bl8 shouldLog = level < IRC_LOG_LEVEL_WARNING;

	std::string outMessage = levelStr[level];

	std::va_list args;
	va_start(args, message);
	char tmp[32];
	for (const char *p = message; *p != '\0'; ++p)
	{
		if (*p != '%')
		{
			outMessage += *p;
			continue;
		}
		switch (*++p)
		{
			case 's':
			{
				char *s = va_arg(args, char *);
				outMessage += s;
				break;
			}
			case 'd':
			{
				int32 d = va_arg(args, int);
				Ftoa(d, tmp, 0);
				outMessage += tmp;
				break;
			}
			case 'c':
			{
				int32 c = va_arg(args, int);
				outMessage += c;
				break;
			}
			case 'f':
			{
				dbl64 f = va_arg(args, double);
				Ftoa(f, tmp, 2);
				outMessage += tmp;
				break;
			}
			case '%':
				outMessage += '%';
				break;
		}
	}
	va_end(args);

	if (shouldLog)
	{
		PlatconsoleWriteError(outMessage, level);
	}
	else
	{
		PlatconsoleWrite(outMessage, level);
	}
	outMessage.clear();
}

void	PlatconsoleWrite(std::string message, uint8 color)
{
	// WARN,INFO,DEBUG,TRACE
	std::string colorStr[] = {T_YELLOW, T_GREEN, T_BLUE, T_CYAN};

	std::cout << colorStr[color - 2] << message << T_RESET << std::endl;
}

void	PlatconsoleWriteError(std::string message, uint8 color)
{
	// FATAL,ERROR
	std::string colorStr[] = {T_RED, T_MAGENTA};

	if (color == 0)
	{
		std::cerr << colorStr[color] << message << T_RESET << std::endl;
		// exit(-1);
	}
	else
		std::cout << colorStr[color] << message << T_RESET << std::endl;
}
