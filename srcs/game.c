/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 23:11:51 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:12:28 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <limits.h>
#include <stdlib.h>

int	game_init(t_grid *grid, int rows, int columns)
{
	if (!grid_init(grid, rows, columns))
		return (0);
	if (!game_spawn_tile(grid) || !game_spawn_tile(grid))
		return (0);
	return (1);
}

int	game_spawn_tile(t_grid *grid)
{
	int	row;
	int	column;
	int	empty_count;
	int	selected;
	int	value;

	if (!grid || ((grid->rows != 4) && (grid->rows != 5))
		|| (grid->columns != grid->rows))
		return (0);
	empty_count = 0;
	row = 0;
	while (row < grid->rows)
	{
		column = 0;
		while (column < grid->columns)
		{
			if (grid_get_value(grid, row, column) == 0)
				empty_count++;
			column++;
		}
		row++;
	}
	if (empty_count == 0)
		return (0);
	selected = rand() % empty_count;
	value = 2;
	if (rand() % 10 == 0)
		value = 4;
	row = 0;
	while (row < grid->rows)
	{
		column = 0;
		while (column < grid->columns)
		{
			if (grid_get_value(grid, row, column) == 0)
			{
				if (selected == 0)
				{
					grid_set_value(grid, row, column,
						(unsigned long long)value);
					return (1);
				}
				selected--;
			}
			column++;
		}
		row++;
	}
	return (0);
}

int	game_is_over(const t_grid *grid)
{
	int					row;
	int					column;
	unsigned long long	value;

	if (!grid || ((grid->rows != 4) && (grid->rows != 5))
		|| (grid->columns != grid->rows))
		return (1);
	row = 0;
	while (row < grid->rows)
	{
		column = 0;
		while (column < grid->columns)
		{
			value = grid_get_value(grid, row, column);
			if (value == 0)
				return (0);
			if ((column + 1 < grid->columns)
				&& (value == grid_get_value(grid, row, column + 1))
				&& (value <= ULLONG_MAX / 2))
				return (0);
			if ((row + 1 < grid->rows)
				&& (value == grid_get_value(grid, row + 1, column))
				&& (value <= ULLONG_MAX / 2))
				return (0);
			column++;
		}
		row++;
	}
	return (1);
}

int	game_has_won(const t_grid *grid)
{
	int	row;
	int	column;

	if (!grid || ((grid->rows != 4) && (grid->rows != 5))
		|| (grid->columns != grid->rows))
		return (0);
	row = 0;
	while (row < grid->rows)
	{
		column = 0;
		while (column < grid->columns)
		{
			if (grid_get_value(grid, row, column) >= WIN_VALUE)
				return (1);
			column++;
		}
		row++;
	}
	return (0);
}
