/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 19:42:51 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:09:04 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ft_printf.h"
#include "menu.h"
#include <curses.h>
#include <stdlib.h>
#include <time.h>

static int	get_direction(int key, t_direction *direction);

int	main(void)
{
	t_grid				grid;
	t_scores			scores;
	int					board_size;
	int					key;
	int					game_over;
	int					won;
	unsigned long long	score;
	unsigned long long	best_score;
	t_direction			direction;

	scores_load(&scores);
	if (initscr() == NULL)
	{
		ft_printf(FT_STDERR, "Error: could not initialize ncurses.\n");
		return (1);
	}
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	grid_init_colors();
	srand((unsigned int)time(NULL));
	while (1)
	{
		board_size = (int)menu_select_board(&scores);
		if (board_size == MENU_EXIT)
			break ;
		if (board_size == MENU_START_4X4)
			board_size = 4;
		else
			board_size = 5;
		if (!game_init(&grid, board_size, board_size))
			continue ;
		score = 0;
		won = 0;
		while (1)
		{
			if (game_has_won(&grid))
				won = 1;
			game_over = game_is_over(&grid);
			best_score = score;
			if (scores.values[0] > best_score)
				best_score = scores.values[0];
			erase();
			mvprintw(0, 3, "2048  Score: %llu  Best: %llu",
				score, best_score);
			grid_draw(&grid);
			if (game_over && won)
				mvprintw(LINES - 1, 2, "2048 reached; no moves left. M: menu, ESC: quit.");
			else if (game_over)
				mvprintw(LINES - 1, 2, "Game over - M: menu, ESC: quit.");
			else if (won)
				mvprintw(LINES - 1, 2, "2048 reached! M: menu, ESC: quit.");
			else
				mvprintw(LINES - 1, 2, "Arrows: move; M: menu; ESC: quit.");
			refresh();
			key = getch();
			if (key == 27)
			{
				board_size = MENU_EXIT;
				break ;
			}
			if ((key == 'm') || (key == 'M'))
				break ;
			if (!game_over && get_direction(key, &direction)
				&& game_move(&grid, direction, &score))
				game_spawn_tile(&grid);
		}
		scores_record(&scores, score);
		if (board_size == MENU_EXIT)
			break ;
	}
	endwin();
	return (0);
}

static int	get_direction(int key, t_direction *direction)
{
	if (key == KEY_UP)
		*direction = DIR_UP;
	else if (key == KEY_DOWN)
		*direction = DIR_DOWN;
	else if (key == KEY_LEFT)
		*direction = DIR_LEFT;
	else if (key == KEY_RIGHT)
		*direction = DIR_RIGHT;
	else
		return (0);
	return (1);
}
