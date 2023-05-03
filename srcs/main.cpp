/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchini <ltrinchini@student.42lyon.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:38:37 by ltrinchi          #+#    #+#             */
/*   Updated: 2023/05/03 18:00:50 by ltrinchini       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "USAGE: " << av[0] << " [port] [password]" << std::endl;
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	Server server(atoi(av[1]), av[2]);

	server.startServer();

	return (EXIT_FAILURE);
}
