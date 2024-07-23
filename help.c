#include <stdio.h>

// print helo message with all possible commands
void printHelp()
{
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