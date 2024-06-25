/*
Authors: Silas Hausdörfer, Jonathan Dechow
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_PATH_LENGTH 260

// Declare functions:
BOOL isAdmin();
void encrypt();
void decrypt();
void rsaencr();
unsigned char* readFileAsBinary();
char* getAbsolutePath(const char* relativPath);

int main(int argc, char *argv[]){

    // We check for admin rights to avoid needing a verification or password system
    // !!!Not final maybe it is unnecesary
    if(!isAdmin()){
        printf("This application requires adminisrative privileges.\nPlease use a terminal with admin privileges.");
        return 1;
    }

    // Check if the number of arguments the user has given is valid
    if(argc != 3){
        printf("Please provide two arguments\nIf you need help use the argument help");
        return 1;
    }

    //convert whatever path was given to an absolute path
    //Currently does't support Home directory relative paths
    const char* filePath = argv[2];
    char *absolutePath = getAbsolutePath(filePath);

    // Check which argument was given and execute whatever functionality was requested
    if (strcmp(argv[1], "help") == 0){
        printf("Help section\n------------\n");
        printf("Possible arguments:\n  help\n  encrypt <filepath>\n  decrypt <filepath>");
    } else if (strcmp(argv[1], "encrypt") == 0)
    {
        encrypt(absolutePath);
    } else if (strcmp(argv[1], "decrypt") == 0)
    {
        decrypt();
    }else{
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
void encrypt(char* filePath){
    char* fileData = readFileAsBinary(filePath);

}

// Decrypt a file
void decrypt(){

}

// Function to convert binary string to decimal number to use RSA encryption method: https://medium.com/hackernoon/how-does-rsa-work-f44918df914b
unsigned int binaryToDecimal(const char *binaryStr) {
    unsigned int decimalNumber = 0;
    while (*binaryStr) {
        decimalNumber = (decimalNumber << 1) | (*binaryStr++ - '0');
    }
    return decimalNumber; 
}

// Function to convert decimal number to binary string 
void decimalToBinary(unsigned int decimal, char *binaryStr) {
    int index = 0;
    for (int i = 31; i >= 0; i--) {
        binaryStr[index++] = (decimal & (1 << i)) ? '1' : '0';
    }
    binaryStr[index] = '\0';

    // Remove leading zeros
    int start = 0;
    while (binaryStr[start] == '0' && start < 31) {
        start++;
    }
    memmove(binaryStr, binaryStr + start, 32 - start + 1);
}

// Reads a file and returns it as binary
unsigned char* readFileAsBinary(const char* filePath){
    printf("File Path: %s\n", filePath);

    // not yet implemented

    return NULL;
}

// converts a relative path to an absolute path
char* getAbsolutePath(const char* relativePath){
    char *absolutePath = (char *)malloc(MAX_PATH_LENGTH);
    //Error handling for malloc
    if(!absolutePath){
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    // converting relative to absolute path and error handling for _fullpath
    if (_fullpath(absolutePath, relativePath, MAX_PATH_LENGTH) == NULL){
        fprintf(stderr, "Error converting to absolute path\n");
        free(absolutePath);
        exit(EXIT_FAILURE);
    }

    // Return the absolute path if everything went well
    return absolutePath;
}

void rsaencr() // muss hier was noch in die Klammer rein?
{
    
}