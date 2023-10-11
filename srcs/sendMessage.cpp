/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:15:42 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/10 17:33:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

int	sendMessage(const char *message, user &receiver) {
	int	messageSize;
	int	total;
	int	bytesleft;
	int	n;

	total = 0;
	messageSize = strlen(message);
	bytesleft = messageSize;
	while (total < messageSize) {
		n = send(receiver.get_fd_socket(), message + total, bytesleft, 0);
		if (n == -1)
			break;
		total += n;
		bytesleft -=n;
	}
	
	if (n == -1)
		return (n);
	else
		return (total);
}
