/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scores.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 22:52:53 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/15 00:23:07 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCORES_H
# define SCORES_H

# define SCORE_COUNT 5

typedef struct s_scores
{
	unsigned long long values[SCORE_COUNT];
} t_scores;

void	scores_load(t_scores *scores);
void	scores_record(t_scores *scores, unsigned long long score);

#endif
