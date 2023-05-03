/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toString.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:51:25 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/18 15:53:19 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

std::string toString(int nb)
{
	std::stringstream ss;
	ss << nb;
	return (ss.str());
}
