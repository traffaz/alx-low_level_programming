#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *allocate_buffer(char *filename);
void close_file_descriptor(int fd);

/**
 * allocate_buffer - Allocates 1024 bytes of memory for a buffer.
 * @filename: The name of the file that the buffer will be used for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *allocate_buffer(char *filename)
{
    char *buffer = malloc(sizeof(char) * 1024);

    if (buffer == NULL)
    {
        dprintf(STDERR_FILENO,
            "Error: Can't allocate memory for buffer in file %s\n", filename);
        exit(99);
    }

    return buffer;
}

/**
 * close_file_descriptor - Closes a file descriptor.
 * @fd: The file descriptor to be closed.
 */
void close_file_descriptor(int fd)
{
    int result = close(fd);

    if (result == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close file descriptor %d\n", fd);
        exit(100);
    }
}

/**
 * main - Copies the contents of one file to another.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of pointers to the program's arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect, exit with status code 97.
 * If the input file does not exist or cannot be read, exit with status code 98.
 * If the output file cannot be created or written to, exit with status code 99.
 * If either file cannot be closed, exit with status code 100.
 */
int main(int argc, char *argv[])
{
    int input_fd, output_fd, read_result, write_result;
    char *buffer;

    if (argc != 3)
    {
        dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
        exit(97);
    }

    buffer = allocate_buffer(argv[2]);

    input_fd = open(argv[1], O_RDONLY);

    read_result = read(input_fd, buffer, 1024);

    output_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

    do {
        if (input_fd == -1 || read_result == -1)
        {
            dprintf(STDERR_FILENO,
                "Error: Can't read from input file %s\n", argv[1]);
            free(buffer);
            exit(98);
        }

        write_result = write(output_fd, buffer, read_result);

        if (output_fd == -1 || write_result == -1)
        {
            dprintf(STDERR_FILENO,
                "Error: Can't write to output file %s\n", argv[2]);
            free(buffer);
            exit(99);
        }

        read_result = read(input_fd, buffer, 1024);

        output_fd = open(argv[2], O_WRONLY | O_APPEND);

    } while (read_result > 0);

    free(buffer);

    close_file_descriptor(input_fd);
    close_file_descriptor(output_fd);

    retu
