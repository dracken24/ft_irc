/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:20:43 by dracken24         #+#    #+#             */
/*   Updated: 2023/02/23 15:17:38 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// telnet :> open 127.0.0.1 8000

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for close
#include <cstring>

#include <iostream>
#include <stdexcept>

	int
	main(void)
{

	int server_sockfd;							// server socket fd	
	struct sockaddr_in server_addr;				// server info struct
	
	server_addr.sin_family = AF_INET; 			// TCP/IP
	server_addr.sin_addr.s_addr = INADDR_ANY;	// server addr--permit all connection
	server_addr.sin_port = htons(8000); 		// server port

	/* create socket fd with IPv4 and TCP protocal*/
	if((server_sockfd = socket(PF_INET,SOCK_STREAM,0))<0)
	{  
		throw std::runtime_error("socket error");
		return 1;
	}

	/* bind socket with server addr */
	if(bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) < 0)
	{
		throw std::runtime_error("bind error");
		return 1;
	}

	/* listen connection request with a queue length of 20 */
	if(listen(server_sockfd,20) < 0)
	{
		throw std::runtime_error("listen error");
		return 1;
	}
	std::cout << "listen success." << std::endl;

	std::string recv_buf;
	std::memset((void*)recv_buf.c_str(), '\0', sizeof(recv_buf));

	while (1)
	{
		struct sockaddr_in client_addr;
		socklen_t length = sizeof(client_addr);
		
		// block on accept until positive fd or error
		int conn = accept(server_sockfd, (struct sockaddr*)&client_addr,&length);
		if(conn<0)
		{
			throw std::runtime_error("accept error");
			return -1;
		}

		std::cout << "new client accepted" << std::endl;

		char client_ip[INET_ADDRSTRLEN] = "";
		inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

		while(recv(conn, (void*)recv_buf.c_str(), sizeof(recv_buf), 0) > 0 )
		{
			std::cout << "recv " << recv_buf << " from client(" << client_ip << ":" << ntohs(client_addr.sin_port) << ")." << std::endl;
			memset((void*)recv_buf.c_str(), '\0', recv_buf.size());
			break;
		}
	}

	std::cout << "close socket." << std::endl;
	close(server_sockfd);
	return 0;
}
