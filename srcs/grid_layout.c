/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_layout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 23:11:42 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:11:43 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grid.h"

#define CELL_WIDTH 15
#define CELL_HEIGHT 4
#define GRID_MARGIN_Y 1
#define GRID_MARGIN_X 2

int	grid_layout(t_grid *grid, int terminal_rows, int terminal_columns)
{
	int	grid_height;
	int	grid_width;
	int	usable_height;

	if (!grid)
		return (0);
	grid->layout_valid = 0;
	grid->cell_height = CELL_HEIGHT;
	grid->cell_width = CELL_WIDTH;
	grid_height = grid->rows * grid->cell_height + 1;
	grid_width = grid->columns * grid->cell_width + 1;
	usable_height = terminal_rows - GRID_MARGIN_Y * 2;
	if ((usable_height < grid_height)
		|| (terminal_columns - GRID_MARGIN_X * 2 < grid_width))
		return (0);
	grid->origin_y = GRID_MARGIN_Y + (usable_height - grid_height) / 2;
	grid->origin_x = (terminal_columns - grid_width + 1) / 2;
	grid->layout_valid = 1;
	return (1);
}

int	grid_get_cell_bounds(const t_grid *grid, int row, int column,
		t_cell_bounds *bounds)
{
	if (!grid || !bounds || !grid->layout_valid || (row < 0)
		|| (row >= grid->rows) || (column < 0)
		|| (column >= grid->columns))
		return (0);
	bounds->top = grid->origin_y + row * grid->cell_height;
	bounds->left = grid->origin_x + column * grid->cell_width;
	bounds->bottom = bounds->top + grid->cell_height;
	bounds->right = bounds->left + grid->cell_width;
	return (1);
}
