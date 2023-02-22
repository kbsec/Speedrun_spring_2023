#include "httpclient.h"
#include "execute.h"
#include "command.h"
#include "debug.h"

// TODO
// password, c2, port, register, checkin, ua, tls, max failure, sleep time 


// todo: opcodes

RegisterData registerData;
CheckinData checkinData;

void Register(RegisterData *rd){
    DEBUG_PRINTF("Implant Registering\n");
}



JobRequest* Checkin(CheckinData *chkin){
    DEBUG_PRINTF("Implant Checkin\n");
}


JobResponse* HandleExecute(JobRequest *jr){
    DEBUG_PRINTF("Handleing Execute Job \n");
    
}


int main(){
    DEBUG_PRINTF("Starting implant\n");
    return 0;
}