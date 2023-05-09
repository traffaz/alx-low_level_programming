#include "main.h"
#include <stdlib.h>

/**
 * read_textfile- Read a text file and print its contents to STDOUT.
 * @file_path: Path to the text file to be read.
 * @num_letters: The number of letters to read and print.
 *
 * Return: The number of bytes read and printed, or 0 if the function fails or
 *         the file is empty.
 */
ssize_t read_textfile(const char *file_path, size_t num_letters)
{
    char *buffer;
    ssize_t file_descriptor, bytes_read, bytes_written;

    file_descriptor = open(file_path, O_RDONLY);
    if (file_descriptor == -1)
        return (0);

    buffer = malloc(sizeof(char) * num_letters);
    if (buffer == NULL)
        return (0);

    bytes_read = read(file_descriptor, buffer, num_letters);
    if (bytes_read == -1)
    {
        free(buffer);
        return (0);
    }

    bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
    if (bytes_written == -1 || bytes_written != bytes_read)
    {
        free(buffer);
        return (0);
    }

    free(buffer);
    close(file_descriptor);

    return (bytes_written);
}
