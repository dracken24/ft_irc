/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:17:35 by dracken24         #+#    #+#             */
/*   Updated: 2023/02/22 16:20:49 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <stdio.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// // #include <string.h>
// #include <stdlib.h>

// #include <cstring>
// #include <iostream>
// #include <stdexcept>

// int main(int argc, char **argv)
// {
// 	struct sockaddr_in server_addr;     // set server addr and port
    
// 	std::memset(&server_addr, 0, sizeof(server_addr));
// 	server_addr.sin_family = AF_INET;
// 	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
// 	server_addr.sin_port = htons(8000);  // server default port

//     int sock_client;
// 	char send_buf[65536];
//     char send_content[64] = "I am client";
    
// 	std::memset(send_buf, '\0', sizeof(send_buf));
//     // strcpy(send_buf, send_content);

//     if ((sock_client = socket(AF_INET,SOCK_STREAM, 0)) < 0)
// 	{
//         return 0;
//     }

//     //connect server, return 0 with success, return -1 with error
//     if (connect(sock_client, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
//     {
//         perror("connect");
//         return 0;
//     }

//     char server_ip[INET_ADDRSTRLEN]="";
//     inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, INET_ADDRSTRLEN);
//     printf("connected server(%s:%d). \n", server_ip, ntohs(server_addr.sin_port));

//     //send a message to server
//     send(sock_client, send_buf, strlen(send_buf), 0);
//     close(sock_client);

// 	return 0;
// }

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	struct sockaddr_in server_addr; // set server addr and port
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(8000); // server default port

	int sock_client;
	char send_buf[65536];
	memset(send_buf, '\0', sizeof(send_buf));
	
	const char *send_content = "I am client";
	strcpy(send_buf, send_content);

	if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Failed to create socket" << std::endl;
		return 1;
	}

	//connect server, return 0 with success, return -1 with error
	if (connect(sock_client, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "Failed to connect server" << std::endl;
		// perror("connect");
		return 1;
	}

	char server_ip[INET_ADDRSTRLEN] = "";
	inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, INET_ADDRSTRLEN);
	std::cout << "connected server(" << server_ip << ":" << ntohs(server_addr.sin_port) << ")." << std::endl;

	//send a message to server
	send(sock_client, send_buf, strlen(send_buf), 0);
	close(sock_client);

	return 0;
}
