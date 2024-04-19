/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:08 by ymeziane          #+#    #+#             */
/*   Updated: 2024/04/19 21:18:17 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Initialize all field flags to zero.
 * This function sets up the tracking structure for determining whether all required
 * fields have been successfully parsed and validated.
 *
 * @param f Pointer to the fields structure to be initialized.
 */
void init_fields(t_fields *f)
{
    f->c = 0;
    f->f = 0;
    f->no = 0;
    f->so = 0;
    f->ea = 0;
    f->we = 0;
    f->is_ok = 0;
}

/**
 * Compares a string after trimming leading spaces against a target string.
 *
 * @param base Pointer to the string to trim and compare.
 * @param to_compare Pointer to the string to compare against.
 * @param size Number of characters to compare.
 * @return 0 if the strings are equivalent, non-zero otherwise.
 */
int trim_compare(char *base, char *to_compare, size_t size)
{
    while (*base && *base == ' ')
        base++;
    return (ft_strncmp(base, to_compare, size));
}

/**
 * Validates if a string represents a valid number for RGB values (0-255).
 *
 * @param nb Pointer to the string representing the number.
 * @return 1 if the string is a valid number, 0 otherwise.
 */
static int is_valid_number(char *nb)
{
    char *original_nb;  // Save the start of the string for conversion
	int nb_int;

	original_nb = nb;
    // Skip leading spaces
    while (*nb && *nb == ' ')
        nb++;
    // Check for digits
    while (*nb && ft_isdigit(*nb))
        nb++;
    // Ensure there are no additional characters after the number
    if (*nb != '\0')
        return 0;

    // Convert the numeric part of the string to an integer
    nb_int = ft_atoi(original_nb);
    // Validate the integer is within the RGB range
    return (nb_int >= 0 && nb_int <= 255);
}


/**
 * Validates RGB data, ensuring it consists of exactly three valid numbers separated by commas.
 *
 * @param line Pointer to the string containing the RGB data.
 * @return 1 if the data is valid, 0 otherwise.
 */
static int is_valid_rgb_data(char *line)
{
    char **data;
    int i, valid_data = 1;

    while (*line && !ft_isdigit(*line))
        line++;
    if (!*line)
        return 0;

    data = ft_split(line, ',');
    for (i = 0; data && data[i]; i++) {
        if (!is_valid_number(data[i]))
            valid_data = 0;
        free(data[i]);
    }
    if (data)
        free(data);
    return valid_data && i == 3;
}

/**
 * Validates if a texture path is valid by checking if the file can be opened.
 *
 * @param line Pointer to the string containing the texture path.
 * @return 1 if the file path is valid, 0 otherwise.
 */
bool	valid_texture_path(char *line)
{
	int	i;
	int	fd;

	if (!line)
        return 0;  // Check for NULL input to prevent segmentation faults
	i = 0;
	while (*line && *line == ' ')
		line++;
	line += 3; // Skip the texture identifier like "NO "
	while (*line && *line == ' ')
		line++;
	 // Check for non-empty line after skipping whitespace
    if (*line == '\0')
		return 0;  // Ensure line is not empty after removing spaces
	while (line[i] && line[i] != ' ')
		i++;
	line[i] = '\0';
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
        perror("Failed to open texture file");
        return 0;
    }
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}


/**
 * Processes a line of input to determine and validate what field it represents.
 * Updates the fields structure accordingly.
 *
 * @param line Pointer to the line to be processed.
 * @param fields Pointer to the fields structure being populated.
 * @return 1 if the line is processed, 0 if there is an error in processing.
 */
int check_fields(char *line, t_fields *fields)
{
    if (trim_compare(line, "NO ", 3) == 0 && valid_texture_path(line))
        fields->no++;
    else if (trim_compare(line, "EA ", 3) == 0 && valid_texture_path(line))
        fields->ea++;
    else if (trim_compare(line, "SO ", 3) == 0 && valid_texture_path(line))
        fields->so++;
    else if (trim_compare(line, "WE ", 3) == 0 && valid_texture_path(line))
        fields->we++;
    else if (trim_compare(line, "C ", 2) == 0 && is_valid_rgb_data(line))
        fields->c++;
    else if (trim_compare(line, "F ", 2) == 0 && is_valid_rgb_data(line))
        fields->f++;
    else
        return 0;  // Invalid field or failed validation

    // Update the is_ok flag if all required fields have been successfully parsed and validated
    fields->is_ok = (fields->no == 1 && fields->ea == 1 && fields->so == 1 && fields->we == 1
                     && fields->c == 1 && fields->f == 1);
    return 1;
}
