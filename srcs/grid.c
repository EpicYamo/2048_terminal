/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:31:02 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:11:34 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grid.h"

static int	is_valid_cell(const t_grid *grid, int row, int column);

int	grid_init(t_grid *grid, int rows, int columns)
{
	int	row;
	int	column;

	if (!grid || (rows != columns) || ((rows != 4) && (rows != 5)))
		return (0);
	grid->rows = rows;
	grid->columns = columns;
	grid->origin_y = 0;
	grid->origin_x = 0;
	grid->cell_height = 0;
	grid->cell_width = 0;
	grid->layout_valid = 0;
	row = 0;
	while (row < GRID_MAX_SIZE)
	{
		column = 0;
		while (column < GRID_MAX_SIZE)
		{
			grid->values[row][column] = 0;
			column++;
		}
		row++;
	}
	return (1);
}

int	grid_set_value(t_grid *grid, int row, int column,
		unsigned long long value)
{
	if (!is_valid_cell(grid, row, column))
		return (0);
	grid->values[row][column] = value;
	return (1);
}

unsigned long long	grid_get_value(const t_grid *grid, int row, int column)
{
	if (!is_valid_cell(grid, row, column))
		return (0);
	return (grid->values[row][column]);
}

static int	is_valid_cell(const t_grid *grid, int row, int column)
{
	return (grid && (row >= 0) && (row < grid->rows)
		&& (column >= 0) && (column < grid->columns));
}
