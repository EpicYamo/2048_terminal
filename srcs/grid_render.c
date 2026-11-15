/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:55:27 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/15 22:44:56 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grid.h"
#include <ncurses.h>

static void			draw_grid_lines(const t_grid *grid);
static int			number_length(unsigned long long value);
static void			draw_cell_values(const t_grid *grid);
static void			draw_ascii_value(const t_grid *grid, int row, int column,
						unsigned long long value, int length);
static void			draw_ascii_power(const t_grid *grid, int row, int column,
						int exponent);
static void			draw_ascii_digit(int x, int y, int digit);
static void			fill_cell(const t_grid *grid, int row, int column);
static void			draw_compact_value(const t_grid *grid, int row, int column,
						unsigned long long value, int length);
static const char	*digit_row(int digit, int line);
static int			tile_color_pair(unsigned long long value);
static int			power_of_two_exponent(unsigned long long value);

void	grid_init_colors(void)
{
	if (!has_colors() || (start_color() == ERR))
		return ;
	if ((COLORS >= 256) && (COLOR_PAIRS >= 14))
	{
		init_pair(1, COLOR_BLACK, 254);
		init_pair(2, COLOR_BLACK, 223);
		init_pair(3, COLOR_BLACK, 216);
		init_pair(4, COLOR_BLACK, 215);
		init_pair(5, COLOR_BLACK, 209);
		init_pair(6, COLOR_BLACK, 202);
		init_pair(7, COLOR_BLACK, 221);
		init_pair(8, COLOR_BLACK, 220);
		init_pair(9, COLOR_BLACK, 184);
		init_pair(10, COLOR_BLACK, 178);
		init_pair(11, COLOR_BLACK, 214);
		init_pair(12, 231, 238);
		init_pair(13, 15, 17);
	}
	else
	{
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		init_pair(2, COLOR_BLACK, COLOR_YELLOW);
		init_pair(3, COLOR_BLACK, COLOR_RED);
		init_pair(4, COLOR_BLACK, COLOR_GREEN);
		init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
		init_pair(6, COLOR_BLACK, COLOR_CYAN);
		init_pair(7, COLOR_BLACK, COLOR_BLUE);
		init_pair(8, COLOR_BLACK, COLOR_CYAN);
		init_pair(9, COLOR_BLACK, COLOR_WHITE);
		init_pair(10, COLOR_BLACK, COLOR_GREEN);
		init_pair(11, COLOR_BLACK, COLOR_YELLOW);
		init_pair(12, COLOR_WHITE, COLOR_BLUE);
		init_pair(13, COLOR_CYAN, COLOR_BLACK);
	}
}

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

static void	draw_cell_values(const t_grid *grid)
{
	int					row;
	int					column;
	int					length;
	unsigned long long	value;

	row = 0;
	while (row < grid->rows)
	{
		column = 0;
		while (column < grid->columns)
		{
			value = grid_get_value(grid, row, column);
			if (value != 0)
			{
				if (has_colors())
					attron(COLOR_PAIR(tile_color_pair(value)));
				fill_cell(grid, row, column);
				length = number_length(value);
				if (value <= 8192)
					draw_ascii_value(grid, row, column, value, length);
				else if (power_of_two_exponent(value) >= 0)
					draw_ascii_power(grid, row, column,
						power_of_two_exponent(value));
				else
					draw_compact_value(grid, row, column, value, length);
				if (has_colors())
					attroff(COLOR_PAIR(tile_color_pair(value)));
			}
			column++;
		}
		row++;
	}
}

static int	tile_color_pair(unsigned long long value)
{
	if (value == 2)
		return (1);
	if (value == 4)
		return (2);
	if (value == 8)
		return (3);
	if (value == 16)
		return (4);
	if (value == 32)
		return (5);
	if (value == 64)
		return (6);
	if (value == 128)
		return (7);
	if (value == 256)
		return (8);
	if (value == 512)
		return (9);
	if (value == 1024)
		return (10);
	if (value == 2048)
		return (11);
	return (12);
}

static void	fill_cell(const t_grid *grid, int row, int column)
{
	int	y;
	int	bottom;
	int	x;

	y = grid->origin_y + row * grid->cell_height + 1;
	bottom = grid->origin_y + (row + 1) * grid->cell_height;
	x = grid->origin_x + column * grid->cell_width + 1;
	while (y < bottom)
	{
		mvhline(y, x, ' ', grid->cell_width - 1);
		y++;
	}
}

static int	number_length(unsigned long long value)
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

static void	draw_ascii_value(const t_grid *grid, int row, int column,
	unsigned long long value, int length)
{
	char	digits[20];
	int	count;
	int	line;
	int	index;
	int	x;
	int	y;

	count = 0;
	while (value > 0)
	{
		digits[count++] = (char)(value % 10);
		value /= 10;
	}
	x = grid->origin_x + column * grid->cell_width + 1
		+ (grid->cell_width - 1 - length * 3) / 2;
	y = grid->origin_y + row * grid->cell_height + 1;
	line = 0;
	while (line < 3)
	{
		index = count - 1;
		while (index >= 0)
		{
			mvaddstr(y + line, x, digit_row(digits[index], line));
			x += 3;
			index--;
		}
		x = grid->origin_x + column * grid->cell_width + 1
			+ (grid->cell_width - 1 - length * 3) / 2;
		line++;
	}
}

static int	power_of_two_exponent(unsigned long long value)
{
	int	exponent;

	if ((value == 0) || ((value & (value - 1)) != 0))
		return (-1);
	exponent = 0;
	while (value > 1)
	{
		value >>= 1;
		exponent++;
	}
	return (exponent);
}

static void	draw_ascii_power(const t_grid *grid, int row, int column,
	int exponent)
{
	char	digits[3];
	int	count;
	int	index;
	int	x;
	int	y;
	int	width;

	count = 0;
	while (exponent > 0)
	{
		digits[count++] = (char)(exponent % 10);
		exponent /= 10;
	}
	width = 4 + count * 3;
	x = grid->origin_x + column * grid->cell_width + 1
		+ (grid->cell_width - 1 - width) / 2;
	y = grid->origin_y + row * grid->cell_height + 1;
	draw_ascii_digit(x, y, 2);
	mvaddch(y + 1, x + 3, '^');
	x += 4;
	index = count - 1;
	while (index >= 0)
	{
		draw_ascii_digit(x, y, digits[index]);
		x += 3;
		index--;
	}
}

static void	draw_ascii_digit(int x, int y, int digit)
{
	int	line;

	line = 0;
	while (line < 3)
	{
		mvaddstr(y + line, x, digit_row(digit, line));
		line++;
	}
}

static void	draw_compact_value(const t_grid *grid, int row, int column,
	unsigned long long value, int length)
{
	int	x;
	int	y;
	int	exponent;

	y = grid->origin_y + row * grid->cell_height + 2;
	if (length <= grid->cell_width - 1)
	{
		x = grid->origin_x + column * grid->cell_width + 1
			+ (grid->cell_width - 1 - length) / 2;
		mvprintw(y, x, "%llu", value);
	}
	else
	{
		exponent = power_of_two_exponent(value);
		x = grid->origin_x + column * grid->cell_width + 3;
		if (exponent >= 0)
			mvprintw(y, x, "2^%d", exponent);
		else
			mvprintw(y, x, "TOO LARGE");
	}
}

static const char	*digit_row(int digit, int line)
{
	if (line == 0)
	{
		if ((digit == 1) || (digit == 4))
			return ("   ");
		return (" _ ");
	}
	if (line == 1)
	{
		if (digit == 0)
			return ("| |");
		if ((digit == 4) || (digit == 8) || (digit == 9))
			return ("|_|");
		if (digit == 1)
			return (" | ");
		if (digit == 7)
			return ("  |");
		if ((digit == 2) || (digit == 3))
			return (" _|");
		return ("|_ ");
	}
	if ((digit == 0) || (digit == 6) || (digit == 8))
		return ("|_|");
	if (digit == 2)
		return ("|_ ");
	if ((digit == 3) || (digit == 5) || (digit == 9))
		return (" _|");
	if (digit == 1)
		return (" | ");
	return ("  |");
}
