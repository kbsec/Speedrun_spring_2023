import struct 
from dataclasses import dataclass



@dataclass
class RegisterData:
    '''
    <16s16s256s256s
    typedef struct RegisterData {
        CHAR Password[16];
        BYTE Guid[16];
        CHAR szUsername[256];
        CHAR szHostname[256];
    } RegisterData;
    '''
    # little endian, 16s, 16b 256s 256s 
    _struct_format = "<16s16s256s256s"
    _sizeof = sizeof = struct.calcsize(_struct_format)
    Password: bytes = ""
    Guid:str = ""
    szUsername: str = ""
    szHostname: str = ""
   
    def sizeof(self):
        return self._sizeof

    def pack(self):
        return struct.pack(self._struct_format, 
        bytes.fromhex(self.Password), 
        self.Guid, 
        self.szHostname.encode(), 
        self.szHostname.encode()
        )

    def unpack(self, data:bytes):
        t = struct.unpack(self._struct_format, data)
        self.Password = t[0].hex()
        self.Guid = t[1].hex()
        self.szUsername = t[2].decode().strip("\0")
        self.szHostname = t[3].decode().strip("\0")
        

@dataclass
class JobRequest:
    """
    <16sL
    typedef struct JobRequest{
        BYTE JobID[16];
        DWORD OpCode; // opcode
        CHAR szArgs[];
    } JobRequest;
    """
    pass




@dataclass
class JobResponse:
    """
    <16sq
    typedef struct JobResponse{
        BYTE JobID[16];
        LONGLONG llOut;
        BYTE Out[];
    } JobResponse;
    """
    pass

@dataclass
class CheckinData:
    """
    typedef struct CheckinData{
        BYTE Guid[16];
        JobResponse *jobResponse;

    } CheckinData;
    """
    pass


        


    

