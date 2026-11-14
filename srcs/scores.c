/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scores.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 22:52:41 by aaycan            #+#    #+#             */
/*   Updated: 2026/11/15 02:10:59 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scores.h"
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#define SCORE_FILE ".2048_scores"
#define SCORE_BUFFER_SIZE 256

static int	score_insert(t_scores *scores, unsigned long long score);
static void	scores_save(const t_scores *scores);
static int	append_score(char *buffer, int position,
		unsigned long long score);

void	scores_load(t_scores *scores)
{
	char				buffer[SCORE_BUFFER_SIZE];
	int					fd;
	int					length;
	int					position;
	int					valid;
	int					has_digit;
	int					digit;
	ssize_t				bytes_read;
	unsigned long long	value;

	if (!scores)
		return ;
	position = 0;
	while (position < SCORE_COUNT)
		scores->values[position++] = 0;
	fd = open(SCORE_FILE, O_RDONLY);
	if (fd < 0)
		return ;
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return ;
	length = (int)bytes_read;
	buffer[length] = '\0';
	position = 0;
	while (position < length)
	{
		value = 0;
		valid = 1;
		has_digit = 0;
		while ((position < length) && (buffer[position] != '\n'))
		{
			if ((buffer[position] >= '0') && (buffer[position] <= '9'))
			{
				digit = buffer[position] - '0';
				has_digit = 1;
				if (valid && (value > (ULLONG_MAX - (unsigned int)digit) / 10))
					valid = 0;
				else if (valid)
					value = value * 10 + (unsigned int)digit;
			}
			else
				valid = 0;
			position++;
		}
		if (valid && has_digit && (value > 0))
			score_insert(scores, value);
		position++;
	}
}

void	scores_record(t_scores *scores, unsigned long long score)
{
	if (scores && (score > 0) && score_insert(scores, score))
		scores_save(scores);
}

static int	score_insert(t_scores *scores, unsigned long long score)
{
	int	position;
	int	index;

	position = 0;
	while ((position < SCORE_COUNT) && (scores->values[position] >= score))
		position++;
	if (position == SCORE_COUNT)
		return (0);
	index = SCORE_COUNT - 1;
	while (index > position)
	{
		scores->values[index] = scores->values[index - 1];
		index--;
	}
	scores->values[position] = score;
	return (1);
}

static void	scores_save(const t_scores *scores)
{
	char				buffer[SCORE_COUNT * 21];
	int					length;
	int					position;
	int					fd;
	ssize_t				bytes_written;
	unsigned long long	score;

	length = 0;
	position = 0;
	while (position < SCORE_COUNT)
	{
		score = scores->values[position];
		if (score > 0)
			length = append_score(buffer, length, score);
		position++;
	}
	fd = open(SCORE_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	position = 0;
	while (position < length)
	{
		bytes_written = write(fd, buffer + position,
			(size_t)(length - position));
		if (bytes_written <= 0)
			break ;
		position += (int)bytes_written;
	}
	close(fd);
}

static int	append_score(char *buffer, int position,
		unsigned long long score)
{
	char	digits[20];
	int		count;

	count = 0;
	while (score > 0)
	{
		digits[count++] = (char)('0' + score % 10);
		score /= 10;
	}
	while (count > 0)
		buffer[position++] = digits[--count];
	buffer[position++] = '\n';
	return (position);
}
