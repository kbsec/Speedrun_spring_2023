#include <windows.h>
#include <winhttp.h>
#include <stdio.h>

int main() {
    printf("Off we go!\n");
    // Initialize WinHTTP
    HINTERNET hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        printf("Error initializing WinHTTP: %d\n", GetLastError());
        return 1;
    }
    printf("Session initialized!\n");

    // Open a connection to example.com
    HINTERNET hConnect = WinHttpConnect(hSession, L"example.com", INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect) {
        printf("Error connecting to server: %d\n", GetLastError());
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Send an HTTP GET request for the root path
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (!hRequest) {
        printf("Error creating HTTP request: %d\n", GetLastError());
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }
    printf("Opened request!\n");

    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        printf("Error sending HTTP request: %d\n", GetLastError());
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }
    printf("Sent! request!\n");

    if (!WinHttpReceiveResponse(hRequest, NULL)) {
        printf("Error receiving HTTP response: %d\n", GetLastError());
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }
    printf("Recieved Response!\n");
    // Read the response into a buffer
    DWORD dwSize = 0;
    DWORD dwBytesRead = 0;
    
    // Current capacity of the buffer
    SIZE_T stBufferSize = 0;

    // Offset from the alloced buffer
    SIZE_T stOffset = 0;

    // Buffer
    LPBYTE lpBuffer = NULL;

    // Used to make sure we actually succeeded 
    LPBYTE lpBufferNext = NULL;

    do {
        dwSize = 0;
        if (!WinHttpQueryDataAvailable( hRequest, &dwSize)){
            printf("Error getting HTTP size: %lu\n", GetLastError());
            //goto cleanup;
        }
        // resize buffer if needed
        lpBufferNext = realloc(lpBuffer,stBufferSize + dwSize );
        if (!lpBufferNext){
            free(lpBuffer);
            goto cleanup;
        }
        lpBuffer = lpBufferNext;
        stBufferSize += dwSize;
        dwBytesRead = 0;
        if(!WinHttpReadData(
            hRequest, 
            lpBuffer + stOffset,
            dwSize,
            &dwBytesRead
        )){
            printf("ReadDataFailed: %lu\n", GetLastError());
            goto cleanup;
        }

        // we read data into the buffer: advance the offset
        stOffset += dwBytesRead;

    } while(dwSize !=0);
    
    if( stOffset >=  stBufferSize){
        // we need 1 more byte. unlucky 
        lpBufferNext = realloc(lpBuffer,stBufferSize + 1 );
        if (!lpBufferNext){
            free(lpBuffer);
            goto cleanup;
        }
        lpBuffer = lpBufferNext;

    }
    lpBuffer[stOffset] = '\0';
    printf("%s\n", lpBuffer);
    // Clean up
    free(lpBuffer);
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;

    cleanup:
        free(lpBuffer);
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 0;
}




