#include "main.h"

/**
 * create_file - Creates a file and writes a string to it.
 *
 * @file_path: The path of the file to create.
 * @text_content: The string to write to the file.
 *
 * Return: If the function fails - -1.
 *         Otherwise - 1.
 */
int create_file(const char *file_path, char *text_content)
{
    int file_descriptor, bytes_written, text_length = 0;

    if (file_path == NULL)
        return (-1);

    if (text_content != NULL)
    {
        while (text_content[text_length] != '\0')
            text_length++;
    }

    file_descriptor = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (file_descriptor == -1)
        return (-1);

    bytes_written = write(file_descriptor, text_content, text_length);
    if (bytes_written == -1 || bytes_written != text_length)
    {
        close(file_descriptor);
        return (-1);
    }

    close(file_descriptor);

    return (1);
}
