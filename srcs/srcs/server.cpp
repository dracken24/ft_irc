/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:20:43 by dracken24         #+#    #+#             */
/*   Updated: 2023/07/26 21:19:58 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// in terminal for connect to server
// telnet 127.0.0.1 8888
#include "IrcCore.hpp"

#ifdef IRC_PLATFORM_LINUX
# include <cstdlib>
#endif

void	MemoryTests(IrcCore *irc, Logger *log);

int main(int argc, char **argv)
{
	// Principal class
	IrcMemory	ircMemory;
	Logger		log;
	IrcCore		irc(&ircMemory, &log);
	
	try
	{
		// Test memory and logger, TODO: delete before correction
		MemoryTests(&irc, &log);
		log.INFO(ircMemory.GetMemoryUsageStr().c_str());

		// Checking command line arguments, LINK: <init.cpp>
		CheckEntry(&irc, &log, argc, argv);

		log.INFO("Welcome to NS irc server v1.0.0.1")

		// Initialization of address structures , LINK: <init.cpp>
		BuildServerInfo(&irc, &log, argv[1]);
		SetQueueSocketAndClient(&irc, &log);

		// LINK: <mainLoop.cpp>
		MainLoop(&irc, &log, &ircMemory);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "Error, server crash!!" << std::endl;
	}

	// log.INFO(ircMemory.GetMemoryUsageStr().c_str());
	irc.FreeCore(&ircMemory);
	//irc.DeleteAllClient(&ircMemory);

	return 0;
}

void	MemoryTests(IrcCore *irc, Logger *log)
{
	// TODO: remove when prog is done
	log->FATAL("Hello World! %f lol %s", 1.0f, "test");
	log->ERROR("Hello World! %f lol %s", 1.0f, "test");
	log->WARNING("Hello World! %f lol %s", 1.0f, "test");
	log->INFO("Hello World! %f lol %s", 1.0f, "test");
	log->DEBUG("Hello World! %f lol %s", 1.0f, "test");
	log->TRACE("Hello World! %f lol %s", 1.0f, "test\n");
}
