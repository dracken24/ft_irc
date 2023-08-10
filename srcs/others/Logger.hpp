/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:46 by nadesjar          #+#    #+#             */
/*   Updated: 2023/07/26 20:58:56 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

// # include "../srcs/IrcCore.hpp"
# include "IrcMemory.hpp"
# include "../includes/defines.hpp"

# include <cstring>
# include <iostream>

# define LOG_WARNING_ENABLED true
# define LOG_INFO_ENABLED true
# define LOG_DEBUG_ENABLED true
# define LOG_TRACE_ENABLED true

// Disable debug and trace logs in release builds
# if DE_RELEASE == 1
#  undef LOG_DEBUG_ENABLED 0
#  undef LOG_TRACE_ENABLED 0
# endif

typedef enum	logLevel
{
	IRC_LOG_LEVEL_FATAL = 0,
	IRC_LOG_LEVEL_ERROR = 1,
	IRC_LOG_LEVEL_WARNING = 2,
	IRC_LOG_LEVEL_INFO = 3,
	IRC_LOG_LEVEL_DEBUG = 4,
	IRC_LOG_LEVEL_TRACE = 5
}	logLevel;

class Logger
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		Logger(void);
		
		Logger(Logger const &copy);
		Logger	&operator=(Logger const &copy);
		
		~Logger(void);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		// Fonction Macros
		MACROS void	LogMessage(logLevel level, const char *message, ...);
	
	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	private:
};


// Log an error message as a fatal error lvl.
# define FATAL(message, ...) LogMessage(IRC_LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

# ifndef ERROR
// Log an error message as an error lvl.
#  define ERROR(message, ...) LogMessage(IRC_LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
# endif

# if LOG_WARNING_ENABLED == 1
// Log an error message as a warning lvl.
#  define WARNING(message, ...) LogMessage(IRC_LOG_LEVEL_WARNING, message, ##__VA_ARGS__);
# else
// if warnings are disabled, just ignore them
#  define WARNING(message, ...) ;
# endif

# if LOG_INFO_ENABLED == 1
// Log an error message as an info lvl.
#  define INFO(message, ...) LogMessage(IRC_LOG_LEVEL_INFO, message, ##__VA_ARGS__);
# else
// if info logs are disabled, just ignore them
#  define INFO(message, ...) ;
# endif

# if LOG_DEBUG_ENABLED == 1
// Log an error message as a debug lvl.
#  define DEBUG(message, ...) LogMessage(IRC_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
# else
// if debug logs are disabled, just ignore them
#  define DEBUG(message, ...) ;
# endif

# if LOG_TRACE_ENABLED == 1
// Log an error message as a trace lvl.
#  define TRACE(message, ...) LogMessage(IRC_LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
# else
// if trace logs are disabled, just ignore them
#  define TRACE(message, ...) ;
# endif

#endif
