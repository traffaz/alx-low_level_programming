#include "main.h"

/**
 * append_text_to_file - Appends text to the end of a file.
 *
 * @file_path: The path of the file to append to.
 * @text_content: The string to append to the file.
 *
 * Return: If the function fails or file_path is NULL - -1.
 *         If the file does not exist or the user lacks write permissions - -1.
 *         Otherwise - 1.
 */
int append_text_to_file(const char *file_path, char *text_content)
{
    int file_descriptor, bytes_written, text_length = 0;

    if (file_path == NULL)
        return (-1);

    if (text_content != NULL)
    {
        while (text_content[text_length] != '\0')
            text_length++;
    }

    file_descriptor = open(file_path, O_WRONLY | O_APPEND);
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
