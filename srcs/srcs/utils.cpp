/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayrand <smayrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:08:06 by dracken24         #+#    #+#             */
/*   Updated: 2023/09/04 14:03:57 by smayrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/defines.hpp"

#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <stdio.h>
#include <map>

// ********************************* Ftoa() ********************************* //

// Reverses a string
static void	Reverse(char *str, int len)
{
	std::string strTmp = str;
	int j = std::strlen(str) - 1;

	for (size_t i = 0; i < strTmp.size(); i++)
	{
		str[i] = strTmp[j];
		j--;
	}

	std::map<int, int> test;
}

static int	IntToStr(int nbr, char str[], int len)
{
	int i = 0;
	while (nbr)
	{
		str[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}

	// Add 0 at end to fill
	while (i < len)
		str[i++] = '0';
		
	str[i] = '\0';
	Reverse(str, i);
	str[i] = '\0';
	
	return i;
}

static int	Pow(int nbr, int power)
{
	int ret = nbr;
	for (int i = 0; i < power; i++)
	{
		ret *= nbr;
	}

	return ret;
}

// Converts a floating-point/double number to a string.
void	Ftoa(float nbr, char *destination, int afterpoint)
{
	if (afterpoint != 0)
		afterpoint--;
	// Take int
	int integer = (int)nbr;
	// Take after dot
	float floating = nbr - (float)integer;
	// convert int to str
	int i = IntToStr(integer, destination, 0);

	if (!destination[0])
	{
		destination[0] = '0';
		i++;
	}

	// if have afterpoint, else is like itoa()
	if (afterpoint != 0)
	{
		// add dot
		destination[i] = '.';
		
		// for put 0 after dot if needed
		floating = floating * Pow(10, afterpoint);
		IntToStr((int)floating, destination + i + 1, afterpoint);
	}
}

// ******************************** Is...() ********************************* //

bool	IsDigit(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}

	return true;
}

int		IsAscii(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < 33 || str[i] > 126)
		{
			return false;
		}
	}
	
	return true;
}

// ************************************************************************** //

std::string	GetChannel(std::string channel)
{
	char tmp[MAX_MSG_LEN];
	channel.copy(tmp, channel.length(), 9);
	int j = 0;
	for (; tmp[j] && tmp[j] != ' '; j++)
		;
	tmp[j] = '\0';
	
	return tmp;
}

std::string Itoa(int value)
{
    std::ostringstream out;
    out << value;
    return out.str();
}

void Ct_mprintf(void *ptr, size_t size, int type, int name)
{
	size_t i;

	i = 0;
	printf("[%c]", name);
	if (type == 0)
	{
		while (i < size)
			printf("%12d | ", ((char *)ptr)[i++]);
	}
	else if (type == 1)
	{
		while (i < size)
		{
			if (((char *)ptr)[i] > 31 && ((char *)ptr)[i] < 127)
				printf("%3c | ", ((char *)ptr)[i]);
			else if (((char *)ptr)[i] == 0)
				printf(" \\0 | ");
			else if (((char *)ptr)[i] == 1)
				printf("SHO | ");
			else if (((char *)ptr)[i] == 2)
				printf("STX | ");
			else if (((char *)ptr)[i] == 3)
				printf("ETX | ");
			else if (((char *)ptr)[i] == 4)
				printf("EOT | ");
			else if (((char *)ptr)[i] == 5)
				printf("ENQ | ");
			else if (((char *)ptr)[i] == 6)
				printf("ACK | ");
			else if (((char *)ptr)[i] == 7)
				printf(" \\a | ");
			else if (((char *)ptr)[i] == 8)
				printf(" \\b | ");
			else if (((char *)ptr)[i] == 9)
				printf(" \\t | ");
			else if (((char *)ptr)[i] == 10)
				printf(" \\n | ");
			else if (((char *)ptr)[i] == 11)
				printf(" \\v | ");
			else if (((char *)ptr)[i] == 12)
				printf(" \\f | ");
			else if (((char *)ptr)[i] == 13)
				printf(" \\r | ");
			else if (((char *)ptr)[i] == 14)
				printf(" SO | ");
			else if (((char *)ptr)[i] == 15)
				printf(" SI | ");
			else if (((char *)ptr)[i] == 16)
				printf("DLE | ");
			else if (((char *)ptr)[i] == 17)
				printf("DC1 | ");
			else if (((char *)ptr)[i] == 18)
				printf("DC2 | ");
			else if (((char *)ptr)[i] == 19)
				printf("DC3 | ");
			else if (((char *)ptr)[i] == 20)
				printf("DC4 | ");
			else if (((char *)ptr)[i] == 21)
				printf("NAK | ");
			else if (((char *)ptr)[i] == 22)
				printf("SYN | ");
			else if (((char *)ptr)[i] == 23)
				printf("ETB | ");
			else if (((char *)ptr)[i] == 24)
				printf("CAN | ");
			else if (((char *)ptr)[i] == 25)
				printf(" EM | ");
			else if (((char *)ptr)[i] == 26)
				printf("SUB | ");
			else if (((char *)ptr)[i] == 27)
				printf("ESC | ");
			else if (((char *)ptr)[i] == 28)
				printf(" FS | ");
			else if (((char *)ptr)[i] == 29)
				printf(" GS | ");
			else if (((char *)ptr)[i] == 30)
				printf(" RS | ");
			else if (((char *)ptr)[i] == 31)
				printf(" US | ");
			else
				printf("%3d | ", ((char *)ptr)[i]);
			i++;
		}
	}
	printf("\n");
}
