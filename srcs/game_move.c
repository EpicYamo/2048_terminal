/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 23:11:56 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/15 22:45:35 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <limits.h>

static int	move_line(t_grid *grid, t_direction direction, int line,
		unsigned long long *score);
static unsigned long long	read_line_cell(const t_grid *grid,
		t_direction direction, int line, int position);
static void	write_line_cell(t_grid *grid, t_direction direction,
		int line, int position, unsigned long long value);

int	game_move(t_grid *grid, t_direction direction,
		unsigned long long *score)
{
	int	line;
	int	changed;

	if (!grid || (grid->rows != grid->columns)
		|| ((grid->rows != 4) && (grid->rows != 5))
		|| (direction < DIR_UP) || (direction > DIR_RIGHT))
		return (0);
	line = 0;
	changed = 0;
	while (line < grid->rows)
	{
		if (move_line(grid, direction, line, score))
			changed = 1;
		line++;
	}
	return (changed);
}

static int	move_line(t_grid *grid, t_direction direction, int line,
	unsigned long long *score)
{
	unsigned long long	values[GRID_MAX_SIZE];
	unsigned long long	result[GRID_MAX_SIZE];
	unsigned long long	merged_value;
	int					position;
	int					source;
	int					target;
	int					changed;

	position = 0;
	while (position < grid->rows)
	{
		values[position] = read_line_cell(grid, direction, line, position);
		position++;
	}
	source = 0;
	target = 0;
	while (source < grid->rows)
	{
		if (values[source] != 0)
			values[target++] = values[source];
		source++;
	}
	while (target < grid->rows)
		values[target++] = 0;
	source = 0;
	target = 0;
	while (source < grid->rows)
	{
		if ((values[source] != 0) && (source + 1 < grid->rows)
			&& (values[source] == values[source + 1])
			&& (values[source] <= ULLONG_MAX / 2))
		{
			merged_value = values[source] * 2;
			result[target] = merged_value;
			if (score && (*score > ULLONG_MAX - merged_value))
				*score = ULLONG_MAX;
			else if (score)
				*score += merged_value;
			target++;
			source += 2;
		}
		else
		{
			result[target] = values[source];
			target++;
			source++;
		}
	}
	while (target < grid->rows)
		result[target++] = 0;
	position = 0;
	changed = 0;
	while (position < grid->rows)
	{
		if (result[position] != read_line_cell(grid, direction,
				line, position))
			changed = 1;
		write_line_cell(grid, direction, line, position, result[position]);
		position++;
	}
	return (changed);
}

static unsigned long long	read_line_cell(const t_grid *grid,
	t_direction direction, int line, int position)
{
	int	row;
	int	column;

	if ((direction == DIR_LEFT) || (direction == DIR_RIGHT))
	{
		row = line;
		column = position;
		if (direction == DIR_RIGHT)
			column = grid->columns - 1 - position;
	}
	else
	{
		column = line;
		row = position;
		if (direction == DIR_DOWN)
			row = grid->rows - 1 - position;
	}
	return (grid_get_value(grid, row, column));
}

static void	write_line_cell(t_grid *grid, t_direction direction,
	int line, int position, unsigned long long value)
{
	int	row;
	int	column;

	if ((direction == DIR_LEFT) || (direction == DIR_RIGHT))
	{
		row = line;
		column = position;
		if (direction == DIR_RIGHT)
			column = grid->columns - 1 - position;
	}
	else
	{
		column = line;
		row = position;
		if (direction == DIR_DOWN)
			row = grid->rows - 1 - position;
	}
	grid_set_value(grid, row, column, value);
}
