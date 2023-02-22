
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
    pass



# id, implant_id, username, hostname 
@dataclass
class Implant(db.Model):
    # todo: might be nice to have first seen, last seen, ..etc
    pass

     
    

CREATED = "CREATED"
TASKED = "TASKED"
COMPLETE = "COMPLETE"
ERROR = "ERROR"


# id, task_id, implant_id, opcode, args, status
@dataclass
class Task(db.Model):
    pass 
    
   
