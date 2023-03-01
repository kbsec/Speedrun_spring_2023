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
    Password: str = ""
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
    _struct_format = "<16sL"
    _sizeof = struct.calcsize(_struct_format)
    JobId:str =b""
    OpCode :int = -1
    szArgs:str = ""

    def sizeof(self):
        return self._sizeof

    def pack(self):
        return struct.pack(self._struct_format,
        bytes.fromhex(self.JobId), self.OpCode ) + struct.pack(f"<{len(self.szArgs) +1 }s", self.szArgs)

    def unpack(self, data:bytes):
        t = struct.unpack(self._struct_format, data[:self._sizeof])
        self.JobId = t[0].hex()
        self.OpCode = t[1]
        self.szArgs  = data[self._sizeof:].decode().strip("\0")

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
    _struct_format = "<16sq"
    _sizeof = struct.calcsize(_struct_format)
    JobID: str =""
    llOut: int = 0
    Out: bytes = b""


    def sizeof(self):
        return self._sizeof
    
    def pack(self):
        #assert( len(self.Out) == self.llOut)
        return struct.pack(self._struct_format,
        bytes.fromhex(self.JobID), self.llOut) + self.Out
        
    def unpack(self, data:bytes):
        t = struct.unpack(self._struct_format, data[:self._sizeof])
        self.JobID = t[0].hex()
        self.llOut = t[1]
        #assert( self.llOut == len(data[self._sizeof:]))
        self.Out = data[self._sizeof:]



@dataclass
class CheckinData:
    """
    typedef struct CheckinData{
        BYTE Guid[16];
        JobResponse *jobResponse;

    } CheckinData;
    """
    _struct_format = "<16s"
    _sizeof = struct.calcsize(_struct_format)
    Guid: str = ""
    jobResponse:JobResponse = JobResponse()

    def sizeof(self):
        return self._sizeof

    def pack(self):
        data = b""
        data += struct.pack(self._struct_format, bytes.fromhex(self.Guid))
        if self.jobResponse:
            data += self.jobResponse.pack()
        return data

    def unpack(self, data:bytes):
        
        t = struct.unpack(self._struct_format, data[:self._sizeof])
        self.Guid = t[0].hex()
        if len(data[self._sizeof:]) >=  JobResponse().sizeof():
            self.jobResponse.unpack(data[self._sizeof:])
        else:
            self.jobResponse = False
        #else:raise("Bad message recieved!")
        


        


    

