from flask import Blueprint, request ,jsonify
from speedrun.db import db



admin = Blueprint('admin', __name__)

@admin.route("/admin/hello")
def hello_admin():
    return "Hello Admin!"

# get all 
#list(Implant.query.all())

# todo: don't let eveyrone have access to my admin itnerface 

# constatns for task
 
# create, list,  (task/implant)


