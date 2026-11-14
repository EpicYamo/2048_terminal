/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 19:42:51 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 21:56:57 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grid.h"
#include "ft_printf.h"
#include <curses.h>

static void	load_demo_values(t_grid *grid);

int	main(void)
{
	t_grid	grid;
	int		key;

	if (!grid_init(&grid, 4, 4))
	{
		ft_printf(FT_STDERR, "Error: could not initialize the grid.\n");
		return (1);
	}
	load_demo_values(&grid);//remove later
	if (initscr() == NULL)
	{
		ft_printf(FT_STDERR, "Error: could not initialize ncurses.\n");
		return (1);
	}
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	while (1)
	{
		erase();
		mvprintw(0, 0, "2048 - grid renderer demo");
		grid_draw(&grid);
		mvprintw(LINES - 1, 0, "Press ESC to quit; resize the terminal to test.");
		refresh();
		key = getch();
		if (key == 27)
			break ;
	}
	endwin();
	return (0);
}

static void	load_demo_values(t_grid *grid)
{
	grid_set_value(grid, 0, 0, 2);
	grid_set_value(grid, 0, 1, 4);
	grid_set_value(grid, 0, 2, 8);
	grid_set_value(grid, 0, 3, 16);
	grid_set_value(grid, 1, 0, 32);
	grid_set_value(grid, 1, 1, 64);
	grid_set_value(grid, 1, 2, 128);
	grid_set_value(grid, 1, 3, 256);
	grid_set_value(grid, 2, 0, 512);
	grid_set_value(grid, 2, 1, 1024);
	grid_set_value(grid, 2, 2, 2048);
	grid_set_value(grid, 2, 3, 2048);
	grid_set_value(grid, 3, 0, 2048);
	grid_set_value(grid, 3, 1, 2048);
	grid_set_value(grid, 3, 2, 2048);
	grid_set_value(grid, 3, 3, 2048);
}
