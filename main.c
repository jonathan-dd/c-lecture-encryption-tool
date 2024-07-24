/*
Authors: Silas Hausdörfer, Jonathan Dechow
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "encryption.h"
#include "conversion.h"
// #include "primegen.h"    // remove comment if needed


#define MAX_PATH_LENGTH 260

// Declare functions:
BOOL isAdmin();
void encrypt(char* filePath, char* encryptionType);
void decrypt(char* filePath, char* encryptionType);
unsigned char* readFileAsBinary(const char *filePath, size_t *fileSize);
void writeFileFromBinary(unsigned char* fileData, size_t* fileSize, char* filePath, char encryptOrDecrypt);
char* getAbsolutePath(const char* relativPath);
void printHelp();
char* editFilePath(char* filePath, char encryptOrDecrypt);


int main(int argc, char *argv[]){

    // We check for admin rights to make sure not anyone can just encrypt files on your system
    if(!isAdmin()){
        printf("This application requires adminisrative privileges.\nPlease use a terminal with admin privileges.");
        return 1;
    }

    // Check if the number of arguments the user has given is valid
    if(argc < 2){
        printf("Please provide at least one arguments\nIf you need help use the argument help");
        return 1;
    }else if (argc > 4)
    {
        printf("there is no command with more than three arguments\nIf you need help use the argument help");
        return 1;
    }
    

    //convert whatever path was given to an absolute path
    //Currently does't support Home directory relative paths
    const char* filePath = argv[2];
    char *absolutePath = getAbsolutePath(filePath);

    // Check which argument was given and execute whatever functionality was requested
    if (strcmp(argv[1], "help") == 0){
        printHelp();
    } 
    else if (strcmp(argv[1], "encrypt") == 0)
    {
        //Add check for encryption type
        encrypt(absolutePath, argv[3]);
    } 
    else if (strcmp(argv[1], "decrypt") == 0)
    {
        //Add check for encryption type
        decrypt(absolutePath, argv[3]);
    }
    else
    {
        printf("Unknown argument");
        return 1;
    }

    return 0;
}

//This function checks if the terminal has admin privileges
BOOL isAdmin() {
    BOOL isAdmin = FALSE;
    HANDLE token = NULL;
    DWORD tokenInfoLength = 0;
    TOKEN_ELEVATION elevation;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)){
        if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &tokenInfoLength)){
            isAdmin = elevation.TokenIsElevated;
        }
    }

    if (token){
        CloseHandle(token);
    }

    return isAdmin;
}

// Encrypt a file
void encrypt(char* filePath, char* encryptionType){
    size_t fileSize;
    unsigned char* fileData = readFileAsBinary(filePath, &fileSize);
    printf("Encryption process started");
    
    
        if(strcmp(encryptionType, "RSA") == 0)
        {
            printf("...RSA Algorithm initiated...\n");
            encrRSA(fileData);
        }
        else if (strcmp(encryptionType, "Caeser") == 0)
        {
            printf("...Caeser Algorithm initiated...\n");
            encrCaeser(fileData);
        }
        else
        {
            printf("A Algorithm with this name is not availible");
            exit;
        }

    

    writeFileFromBinary(fileData, &fileSize, filePath, 'e');
    free(fileData);

    // Delete unencrypted file
    if (remove(filePath) == 0){
        printf("Original file removed");
    }else{
        printf("Original file could not be deleted. Pleas delete the original file manualy\n");
    }
}

// Decrypt a file
void decrypt(char* filePath, char* encryptionType){
    size_t fileSize;
    unsigned char* fileData = readFileAsBinary(filePath, &fileSize);
    printf("Decryption process started");

    //Decryption code here

    writeFileFromBinary(fileData, &fileSize, filePath, 'd');
    free(fileData);

    // Delete encrypted file
    if (remove(filePath) == 0){
        printf("Encrypted file removed");
    }else{
        printf("Encrypted file could not be deleted. Pleas delete the encrypted file manualy\n");
    }
}

// Reads a file and returns it as binary
unsigned char* readFileAsBinary(const char* filePath, size_t *fileSize){

    // Open file as binary
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // determine the length by steping to the end of the file and rewinding to the start
    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    rewind(file);

    // Allocate momory to hold the contents of the file
    unsigned char *buffer = (unsigned char *)malloc(*fileSize);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    // Reaad the file into the buffer
    // bytesRead is just to make sure the right amount of data was read
    size_t bytesRead = fread(buffer, 1, *fileSize, file);
    if (bytesRead != *fileSize) {
        perror("Failed to read the file");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    return buffer;
}

void writeFileFromBinary(unsigned char* fileData, size_t *fileSize, char* filePath, char encryptOrDecrypt){ 

    // Change filepath depending on encryption or decryption opperation
    char* writeFilePath = editFilePath(filePath, encryptOrDecrypt);

    FILE* file = fopen(writeFilePath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writeing");
        exit(EXIT_FAILURE);
    }

    size_t bytesWritten = fwrite(fileData, 1, *fileSize, file);
    if (bytesWritten != *fileSize) {
        perror("Failed to write data to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    fclose(file);
    free(writeFilePath);
}

// converts a relative path to an absolute path
char* getAbsolutePath(const char* relativePath){
    char *absolutePath = (char *)malloc(MAX_PATH_LENGTH);
    //Error handling for malloc
    if(!absolutePath){
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    // converting relative to absolute path and error handling for _fullpath
    if (_fullpath(absolutePath, relativePath, MAX_PATH_LENGTH) == NULL){
        perror("Error converting to absolute path");
        free(absolutePath);
        exit(EXIT_FAILURE);
    }

    // Return the absolute path if everything went well
    return absolutePath;
}

char* editFilePath(char* filePath, char encryptOrDecrypt){

    size_t length = strlen(filePath);
    char* extension = &filePath[length - 4];
    char* editedFilePath;
    
    switch (encryptOrDecrypt)
    {
    case 'e':
        if (strcmp(extension, ".enc") == 0){
            printf("The File you are trying to encrypt is allready encrypted");
            exit(EXIT_FAILURE);
        }

        editedFilePath = (char *)malloc(length + 5);
        if(editedFilePath == NULL){
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        strcpy(editedFilePath, filePath);
        strcat(editedFilePath, ".enc");
        break;
    case 'd':
        if (strcmp(extension, ".enc") != 0){
            printf("The File you are trying to decrypt is not encrypted");
            exit(EXIT_FAILURE);
        }

        if (length < 4){
            perror("File path to short. Can't remove extension");
            exit(EXIT_FAILURE);
        }

        editedFilePath = (char *)malloc(length + 1);
        if(editedFilePath == NULL){
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

// print helo message with all possible commands
void printHelp(){
    printf("\n");
    printf("Help section\n");
    printf("------------\n");
    printf("Possible arguments:\n");
    printf("  help\n");
    printf("  encrypt <filepath> <algorithm>\n");
    printf("  decrypt <filepath> <algorithm>\n");
    printf("\n");
    printf("Algorithms:\n");
    printf("  RSA\n");
    printf("  Caeser\n");
}