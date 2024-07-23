#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_PATH_LENGTH 260

// Reads a file and returns it as binary
unsigned char *readFileAsBinary(const char *filePath, size_t *fileSize)
{

    // Open file as binary
    FILE *file = fopen(filePath, "rb");
    if (file == NULL)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // determine the length by steping to the end of the file and rewinding to the start
    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    rewind(file);

    // Allocate momory to hold the contents of the file
    unsigned char *buffer = (unsigned char *)malloc(*fileSize);
    if (buffer == NULL)
    {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Reaad the file into the buffer
    // bytesRead is just to make sure the right amount of data was read
    size_t bytesRead = fread(buffer, 1, *fileSize, file);
    if (bytesRead != *fileSize)
    {
        perror("Failed to read the file");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    return buffer;
}

void writeFileFromBinary(unsigned char *fileData, size_t *fileSize, char *filePath, char encryptOrDecrypt)
{

    // Change filepath depending on encryption or decryption opperation
    char *writeFilePath = editFilePath(filePath, encryptOrDecrypt);

    FILE *file = fopen(writeFilePath, "wb");
    if (file == NULL)
    {
        perror("Failed to open file for writeing");
        exit(EXIT_FAILURE);
    }

    size_t bytesWritten = fwrite(fileData, 1, *fileSize, file);
    if (bytesWritten != *fileSize)
    {
        perror("Failed to write data to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    free(writeFilePath);
}

// converts a relative path to an absolute path
char *getAbsolutePath(const char *relativePath)
{
    char *absolutePath = (char *)malloc(MAX_PATH_LENGTH);
    // Error handling for malloc
    if (!absolutePath)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    // converting relative to absolute path and error handling for _fullpath
    if (_fullpath(absolutePath, relativePath, MAX_PATH_LENGTH) == NULL)
    {
        perror("Error converting to absolute path");
        free(absolutePath);
        exit(EXIT_FAILURE);
    }

    // Return the absolute path if everything went well
    return absolutePath;
}

char *editFilePath(char *filePath, char encryptOrDecrypt)
{

    size_t length = strlen(filePath);
    char *extension = &filePath[length - 4];
    char *editedFilePath;

    switch (encryptOrDecrypt)
    {
    case 'e':
        if (strcmp(extension, ".enc") == 0)
        {
            printf("The File you are trying to encrypt is allready encrypted");
            exit(EXIT_FAILURE);
        }

        editedFilePath = (char *)malloc(length + 5);
        if (editedFilePath == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        strcpy(editedFilePath, filePath);
        strcat(editedFilePath, ".enc");
        break;
    case 'd':
        if (strcmp(extension, ".enc") != 0)
        {
            printf("The File you are trying to decrypt is not encrypted");
            exit(EXIT_FAILURE);
        }

        if (length < 4)
        {
            perror("File path to short. Can't remove extension");
            exit(EXIT_FAILURE);
        }

        editedFilePath = (char *)malloc(length + 1);
        if (editedFilePath == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        strcpy(editedFilePath, filePath);
        editedFilePath[length - 4] = '\0';
        break;
    default:
        perror("Unknown parameter for writeFileFromBinary(char encryptOrDecrypt)");
        exit(EXIT_FAILURE);
        break;
    }

    return editedFilePath;
}