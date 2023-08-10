/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:14 by nadesjar          #+#    #+#             */
/*   Updated: 2023/08/08 12:50:52 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_HPP
# define DEFINES_HPP

# include <cstddef>

// int
typedef int		int32;

// Unsigned int types.
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

// Signed int types.
typedef signed char			sint8;
typedef signed short		sint16;
typedef signed int			sint32;
typedef signed long long	sint64;

// Floating point types
typedef float	fl32;
typedef double	dbl64;

// Boolean types
typedef char	bl8;

// color
# define T_RESET "\033[0m"
# define T_BOLD "\033[1m"
# define T_DIM "\033[2m"
# define T_ITALIC "\033[3m"
# define T_UNDERLINE "\033[4m"
# define T_BLINK "\033[5m"
# define T_INVERT "\033[6m"
# define T_REVERSE "\033[7m"
# define T_CONCEALED "\033[8m"

# define T_BLACK "\033[30m"
# define T_RED "\033[31m"
# define T_GREEN "\033[32m"
# define T_YELLOW "\033[33m"
# define T_BLUE "\033[36m"
# define T_MAGENTA "\033[35m"
# define T_CYAN "\033[34m"
# define T_WHITE "\033[37m"

# define true 1
# define false 0
# define s_t size_t

# ifndef nullptr
#  define nullptr NULL
# endif

# define MAX_CLIENTS 24
# define MAX_MSG_LEN 1024

// Commands
# define JOIN 		"JOIN"
# define PART 		"PART"
# define LIST 		"LIST"
# define PRIVMSG 	"PRIVMSG"
# define QUIT 		"QUIT"
# define PONG 		"PONG"
# define KICK 		"KICK"
# define INVITE 	"INVITE"
# define TOPIC	 	"TOPIC"
# define MODE	 	"MODE"
# define ADMIN      "ADMIN"

// Platform detection
# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  define IRC_PLATFORM_WINDOWS 1
# ifndef _WIN64
#  error "64-bit is required on Windows!"
# endif
# elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#  define IRC_PLATFORM_LINUX 1
# if defined(__ANDROID__)
#  define IRC_PLATFORM_ANDROID 1
# endif
# elif __APPLE__
// Apple platforms
#  define IRC_PLATFORM_APPLE 1
#  include <TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#  define IRC_PLATFORM_IOS 1
#  define IRC_PLATFORM_IOS_SIMULATOR 1
# elif TARGET_OS_IPHONE
#  define IRC_PLATFORM_IOS 1
// iOS device
# elif TARGET_OS_MAC
// Other kinds of Mac OS
# else
#  error "Unknown Apple platform"
# endif
# else
#  error "Unknown platform!"
# endif

# ifdef IRC_EXPORT
// Exports
# ifdef _MSC_VER
#  define MACROS __declspec(dllexport)
# else
#  define MACROS __attribute__((visibility("default")))
# endif
# else
// Imports
#  ifdef _MSC_VER
#   define MACROS __declspec(dllimport)
#  else
#   define MACROS
#  endif
# endif

#endif
