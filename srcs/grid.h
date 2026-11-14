/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:11:21 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 21:54:48 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

# define GRID_MAX_SIZE 5

typedef struct s_cell_bounds
{
	int	top;
	int	left;
	int	bottom;
	int	right;
} t_cell_bounds;

typedef struct s_grid
{
	int				rows;
	int				columns;
	unsigned long long	values[GRID_MAX_SIZE][GRID_MAX_SIZE];
	int				origin_y;
	int				origin_x;
	int				cell_height;
	int				cell_width;
	int				layout_valid;
} t_grid;

int				grid_init(t_grid *grid, int rows, int columns);
int				grid_set_value(t_grid *grid, int row, int column,
					unsigned long long value);
unsigned long long	grid_get_value(const t_grid *grid, int row, int column);
int				grid_layout(t_grid *grid, int terminal_rows, int terminal_columns);
int				grid_get_cell_bounds(const t_grid *grid, int row, int column,
					t_cell_bounds *bounds);
void			grid_draw(t_grid *grid);
void			grid_init_colors(void);

#endif
