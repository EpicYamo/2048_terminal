/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 23:11:45 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/14 23:11:46 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "grid.h"

enum e_const
{
	WIN_VALUE = 2048
};

typedef enum e_direction
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
} t_direction;

int	game_move(t_grid *grid, t_direction direction,
		unsigned long long *score);
int	game_init(t_grid *grid, int rows, int columns);
int	game_spawn_tile(t_grid *grid);
int	game_is_over(const t_grid *grid);
int	game_has_won(const t_grid *grid);

#endif
