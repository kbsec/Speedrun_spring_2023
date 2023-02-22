#include "httpclient.h"
//#include <windows.h>
#include <stdio.h>
int main(){


    char postData[] = "Hello world!\n";
    size_t stPostData = sizeof(postData);
    SIZE_T stOut = 0;
    LPBYTE data =  HTTPRequest(
    L"GET", 
    L"example.com", 
    L"/", 
    443,
    L"Test", 
    NULL, 
    0, 
    &stOut, 
    TRUE
    ) ;
    printf("%s\n",data);
    free(data);
    data = NULL;

    printf("Round 2");
    
    data =  HTTPRequest(
    L"POST", 
    L"localhost", 
    L"/", 
    1234,
    L"Test", 
    postData, 
    stPostData, 
    &stOut, 
    FALSE
    ) ;
    printf("Round 2: %s\n",data);
    free(data);
 
    printf("Done!: %llu\n", stOut);
    return 0;
}