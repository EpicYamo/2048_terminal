/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 23:11:12 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:11:13 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include <curses.h>

static void	draw_main_menu(const t_scores *scores, int selected);
static void	draw_best_scores(const t_scores *scores,
		int start_row, int column);
static void	draw_menu_item(int item, int row);
static int	is_enter_key(int key);

t_menu_choice	menu_select_board(const t_scores *scores)
{
	int	selected;
	int	key;

	selected = 0;
	while (1)
	{
		draw_main_menu(scores, selected);
		key = getch();
		if (key == 27)
			return (MENU_EXIT);
		if (key == KEY_UP)
			selected = (selected + 2) % 3;
		else if (key == KEY_DOWN)
			selected = (selected + 1) % 3;
		else if (is_enter_key(key))
		{
			if (selected == 0)
				return (MENU_START_4X4);
			if (selected == 1)
				return (MENU_START_5X5);
			return (MENU_EXIT);
		}
	}
}

static void	draw_main_menu(const t_scores *scores, int selected)
{
	int	item;

	erase();
	if (has_colors())
		attron(COLOR_PAIR(13));
	attron(A_BOLD);
	mvprintw(1, 3, "2048");
	attroff(A_BOLD);
	if (has_colors())
		attroff(COLOR_PAIR(13));
	mvprintw(3, 3, "Select board size:");
	item = 0;
	while (item < 3)
	{
		if (item == selected)
			attron(A_REVERSE);
		draw_menu_item(item, 5 + item * 2);
		if (item == selected)
			attroff(A_REVERSE);
		item++;
	}
	mvprintw(4, 30, "BEST SCORES");
	draw_best_scores(scores, 6, 30);
	mvprintw(LINES - 1, 2, "Use UP/DOWN and ENTER");
	refresh();
}

static void	draw_best_scores(const t_scores *scores,
		int start_row, int column)
{
	int	index;

	index = 0;
	while (index < SCORE_COUNT)
	{
		mvprintw(start_row + index, column, "%d. %llu", index + 1,
			scores->values[index]);
		index++;
	}
}

static void	draw_menu_item(int item, int row)
{
	if (item == 0)
		mvprintw(row, 3, "Start 4x4");
	else if (item == 1)
		mvprintw(row, 3, "Start 5x5");
	else
		mvprintw(row, 3, "Exit");
}

static int	is_enter_key(int key)
{
	return (key == '\n' || key == '\r' || key == KEY_ENTER);
}
