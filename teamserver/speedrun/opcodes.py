# add OPcode
# name, int, descr

Registered_Opcodes = {}


class Opcode:
    def __init__(self, name:str, opcode:int, descr:str):
        self.name = name
        self.opcode = opcode
        self.descr = descr
        if self.opcode in Registered_Opcodes:
            raise("Opcode already in use")
        Registered_Opcodes[self.opcode] = self

    def toJSON(self):
        return {
            "name": self.name, 
            "opcode": self.opcode,
            "descr": self.descr
        }


OP_QUIT  = Opcode("quit", 0, "Tell the implant to exit")
OP_EXECUTE = Opcode("execute", 1, "Tell the implant to excute a command: example usage: execute whoami")


def get_commands():
    return [i.toJSON() for i in Registered_Opcodes.values()]
