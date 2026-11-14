/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:55:27 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 21:55:28 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grid.h"
#include <curses.h>

static void	draw_grid_lines(const t_grid *grid);
static int	number_length(unsigned int value);
static void	draw_cell_values(const t_grid *grid);

void	grid_draw(t_grid *grid)
{
	int	terminal_rows;
	int	terminal_columns;

	getmaxyx(stdscr, terminal_rows, terminal_columns);
	if (!grid_layout(grid, terminal_rows, terminal_columns))
	{
		mvprintw(0, 0, "Terminal too small; enlarge it to display the grid.");
		return ;
	}
	draw_grid_lines(grid);
	draw_cell_values(grid);
}

static void	draw_grid_lines(const t_grid *grid)
{
	int	row;
	int	column;
	int	height;
	int	width;

	height = grid->rows * grid->cell_height + 1;
	width = grid->columns * grid->cell_width + 1;
	row = 0;
	while (row <= grid->rows)
	{
		mvhline(grid->origin_y + row * grid->cell_height,
			grid->origin_x, ACS_HLINE, width);
		row++;
	}
	column = 0;
	while (column <= grid->columns)
	{
		mvvline(grid->origin_y, grid->origin_x + column * grid->cell_width,
			ACS_VLINE, height);
		column++;
	}
	row = 0;
	while (row <= grid->rows)
	{
		column = 0;
		while (column <= grid->columns)
		{
			mvaddch(grid->origin_y + row * grid->cell_height,
				grid->origin_x + column * grid->cell_width, ACS_PLUS);
			column++;
		}
		row++;
	}
}

static int	number_length(unsigned int value)
{
	int	length;

	length = 1;
	while (value >= 10)
	{
		value /= 10;
		length++;
	}
	return (length);
}

static void	draw_cell_values(const t_grid *grid)
{
	int			row;
	int			column;
	int			length;
	int			x;
	unsigned int	value;

	row = 0;
	while (row < grid->rows)
	{
		column = 0;
		while (column < grid->columns)
		{
			value = grid_get_value(grid, row, column);
			if (value != 0)
			{
				length = number_length(value);
				x = grid->origin_x + column * grid->cell_width + 1
					+ (grid->cell_width - 1 - length) / 2;
				mvprintw(grid->origin_y + row * grid->cell_height + 2,
					x, "%u", value);
			}
			column++;
		}
		row++;
	}
}
