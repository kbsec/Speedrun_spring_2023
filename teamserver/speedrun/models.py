
from speedrun.db import db
import os 
from dataclasses import dataclass, asdict
import json


#Types
# db.Column(db.Integer, primary_key=True)
# db.Column(db.String)
# interhit db.Model

@dataclass
class TestDB(db.Model):
    id  = db.Column(db.Integer, primary_key=True)
    foo: str = db.Column(db.String)
    bar: str = db.Column(db.String)
    _ignore_me = "i am ignoted! "
    def toJSON(self):
        return asdict(self)


def random_id(n=16):
    """
    Generates a random n-byte ID
    """
    return os.urandom(n)


# id, implant_id, username, hostname 
@dataclass
class Implant(db.Model):
    # todo: might be nice to have first seen, last seen, ..etc
    id  = db.Column(db.Integer, primary_key=True)
    implant_id: str  = db.Column(db.String)
    username: str = db.Column(db.String)
    hostname: str = db.Column(db.String)


 
    

CREATED = "CREATED"
TASKED = "TASKED"
COMPLETE = "COMPLETE"
ERROR = "ERROR"


# id, task_id, implant_id, opcode, args, status
@dataclass
class Task(db.Model):
    id  = db.Column(db.Integer, primary_key=True)
    task_id: str  = db.Column(db.String)
    implant_id: str  = db.Column(db.String)
    opcode : int = db.Column(db.Integer)
    args : str = db.Column(db.String)
    status: str = db.Column(db.String)
    
   

## crud operations 
## maybe move into own file 

def random_id(n=16):
    """
    Generates a random n-byte ID
    """
    return os.urandom(n)


def make_task(implant_id: str, opcode:int, args:str)->Task:
    #todo ensure the implant id exists!!
    #todo: use logggin instead of print!
    #todo: add validation!
    t = Task(
        implant_id = implant_id, 
        task_id = random_id().hex(),
        opcode = opcode, 
        args = args, 
        status = CREATED
    )
    print(f"New task created for {t.implant_id} :{t.task_id} " )
    return t

def make_implant(implant_id: str, username:str, hostname: str):
    im =Implant(implant_id = implant_id, username = username, hostname=hostname)
    return im