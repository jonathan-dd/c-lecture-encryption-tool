/*
Authors: Silas Hausdörfer, Jonathan Dechow
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "encryption.h"
#include "conversion.h"
#include "help.h"
#include "file.h"
// #include "primegen.h"    // remove comment if needed

// Declare functions:
BOOL isAdmin();
void encrypt(char *filePath, char *encryptionType);
void decrypt(char *filePath, char *encryptionType);

int main(int argc, char *argv[])
{

    // We check for admin rights to make sure not anyone can just encrypt files on your system
    if (!isAdmin())
    {
        printf("This application requires adminisrative privileges.\nPlease use a terminal with admin privileges.");
        return 1;
    }

    // Check if the number of arguments the user has given is valid
    if (argc < 2)
    {
        printf("Please provide at least one arguments\nIf you need help use the argument help");
        return 1;
    }
    else if (argc > 4)
    {
        printf("there is no command with more than three arguments\nIf you need help use the argument help");
        return 1;
    }

    // convert whatever path was given to an absolute path
    // Currently does't support Home directory relative paths
    const char *filePath = argv[2];
    char *absolutePath = getAbsolutePath(filePath);

    // Check which argument was given and execute whatever functionality was requested
    if (strcmp(argv[1], "help") == 0)
    {
        printHelp();
    }
    else if (strcmp(argv[1], "encrypt") == 0)
    {
        // Add check for encryption type
        encrypt(absolutePath, argv[3]);
    }
    else if (strcmp(argv[1], "decrypt") == 0)
    {
        // Add check for encryption type
        decrypt(absolutePath, argv[3]);
    }
    else
    {
        printf("Unknown argument");
        return 1;
    }

    return 0;
}

// This function checks if the terminal has admin privileges
BOOL isAdmin()
{
    BOOL isAdmin = FALSE;
    HANDLE token = NULL;
    DWORD tokenInfoLength = 0;
    TOKEN_ELEVATION elevation;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
    {
        if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &tokenInfoLength))
        {
            isAdmin = elevation.TokenIsElevated;
        }
    }

    if (token)
    {
        CloseHandle(token);
    }

    return isAdmin;
}

// Encrypt a file
void encrypt(char *filePath, char *encryptionType)
{
    size_t fileSize;
    unsigned char *fileData = readFileAsBinary(filePath, &fileSize);
    printf("Encryption process started");

    // Encryption code here

    writeFileFromBinary(fileData, &fileSize, filePath, 'e');
    free(fileData);

    // Delete unencrypted file
    if (remove(filePath) == 0)
    {
        printf("Original file removed");
    }
    else
    {
        printf("Original file could not be deleted. Pleas delete the original file manualy\n");
    }
}

// Decrypt a file
void decrypt(char *filePath, char *encryptionType)
{
    size_t fileSize;
    unsigned char *fileData = readFileAsBinary(filePath, &fileSize);
    printf("Decryption process started");

    // Decryption code here

    writeFileFromBinary(fileData, &fileSize, filePath, 'd');
    free(fileData);

    // Delete encrypted file
    if (remove(filePath) == 0)
    {
        printf("Encrypted file removed");
    }
    else
    {
        printf("Encrypted file could not be deleted. Pleas delete the encrypted file manualy\n");
    }
}