from flask import Blueprint, request ,jsonify
from speedrun.db import db
from speedrun.opcodes import get_commands
from speedrun.models import Task,Implant, make_task

admin = Blueprint('admin', __name__)

    
def get_all_tasks():
    return  list(Task.query.all())

def get_all_implants():
    return list(Implant.query.all())


@admin.route("/admin/hello")
def hello_admin():
    return "Hello Admin!"

@admin.route("/admin/list/commands")
def list_commands():
    return jsonify(get_commands())


@admin.route("/admin/list/tasks")
def list_tasks():
    return jsonify(get_all_tasks())

@admin.route("/admin/create/task", methods = ["POST"])
def create_task():
    json_data = request.json
    try:
        t = make_task(**json_data)
        db.session.add(t)
        db.session.commit()
        return jsonify({"status": True, "msg":f"created {t.task_id}" })

    except Exception as e:
        print(Exception, e, "Failed to create task :(")
        #todo: better error handling/messaging 
        return jsonify({"status":False, "msg":"Failed to create task" })



@admin.route("/admin/list/implants")
def list_implantss():
    return jsonify(get_all_implants())




# get all 
#list(Implant.query.all())

# todo: don't let eveyrone have access to my admin itnerface 

# constatns for task
 
# create, list,  (task/implant)


