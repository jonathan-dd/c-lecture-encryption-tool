/*
Authors: Silas Hausdörfer, Jonathan Dechow
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//This function checks if the terminal the is use has admin privileges
BOOL IsAdmin() {
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

int main(){

    // We check for admin rights to avoid needing a verification or password system
    if(!IsAdmin()){
        printf("This application requires adminisrative privileges.\n Please use a terminal with admin privileges.");
        return 1;
    }

    //main encryption/decryption code starts here



    return 0;
}