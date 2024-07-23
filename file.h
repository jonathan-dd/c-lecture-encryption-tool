#ifndef FILE_H
#define FILE_H

unsigned char *readFileAsBinary(const char *filePath, size_t *fileSize);
void writeFileFromBinary(unsigned char *fileData, size_t *fileSize, char *filePath, char encryptOrDecrypt);
char *getAbsolutePath(const char *relativPath);
char *editFilePath(char *filePath, char encryptOrDecrypt);

#endif