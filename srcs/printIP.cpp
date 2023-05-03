/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printIP.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:46:38 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 17:25:08 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

#define HOST_NAME_SIZE_MAX sysconf(_SC_HOST_NAME_MAX)

void print_IP(void)
{
	char *hostname;
	struct hostent *host_val;
	char *ip;

	hostname = (char *)malloc(sizeof(char) * HOST_NAME_SIZE_MAX);
	if (!hostname)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	if (gethostname(hostname, sizeof(char) * HOST_NAME_SIZE_MAX))
	{
		perror("Error gethostname");
		exit(EXIT_FAILURE);
	}

	host_val = gethostbyname(hostname);
	if (!host_val)
	{
		perror("Error gethostbyname");
		exit(EXIT_FAILURE);
	}

	std::cout << "Address IP available" << std::endl;
	for (size_t i = 0; host_val->h_addr_list[i]; i++)
	{
		ip = inet_ntoa(*((struct in_addr *)host_val->h_addr_list[i]));
		std::cout << i + 1 << ": " << ip << std::endl;
	}
	free(hostname);
}
