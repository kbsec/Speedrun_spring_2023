from crypt import methods
from flask import Blueprint, jsonify, request
from speedrun.db import db

import struct

password = struct.pack(">16s", b"1337ch0nkyboy").hex()

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


   
