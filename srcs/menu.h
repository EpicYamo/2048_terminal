/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 23:11:16 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:11:16 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "scores.h"

typedef enum e_menu_choice
{
	MENU_EXIT,
	MENU_START_4X4,
	MENU_START_5X5
} t_menu_choice;

t_menu_choice	menu_select_board(const t_scores *scores);

#endif
