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
void encrypt(char* filePath, char* encryptionType);
void decrypt(char* filePath, char* encryptionType);
unsigned char* readFileAsBinary(const char *filePath, size_t *fileSize);
void writeFileFromBinary(unsigned char* fileData, size_t* fileSize, char* filePath, char encryptOrDecrypt);
char* getAbsolutePath(const char* relativPath);
void printHelp();

int main(int argc, char *argv[]){

    // We check for admin rights to avoid needing a verification or password system
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

    //Encryption code here

    // File path has to me changed to 
    writeFileFromBinary(fileData, &fileSize, filePath, 'e');
    free(fileData);
}

// Decrypt a file
void decrypt(char* filePath, char* encryptionType){
    size_t fileSize;
    unsigned char* fileData = readFileAsBinary(filePath, &fileSize);

    //Decryption code here

    writeFileFromBinary(fileData, &fileSize, filePath, 'd');
    free(fileData);
}

// Reads a file and returns it as binary
unsigned char* readFileAsBinary(const char* filePath, size_t *fileSize){
    printf("File Path: %s\n", filePath);

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

void writeFileFromBinary(unsigned char* fileData, size_t *fileSize, char* writeFilePath, char encryptOrDecrypt){

    /*Add code to change writeFilePath depending on if it is a encrypt or decrypt operation
      Functionality should behave like this:
        First check if File given file is allready encrypted or not (can not encrypt an already encrypted file)
      Encrypt: "file/path/file.txt" -> "file/path/file.txt.enc"
      Decrypt: "file/path/file.txt.enc" -> "file/path/file.txt"
      
      Maybe create some helper functions like getFilenameFromPath()                                             */ 

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
    printf("  xor\n");
}