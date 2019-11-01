from pyfcm import FCMNotification
import nexmo
import requests
from flask import Flask


app = Flask(__name__)

api_Key='AAAAGxytM_g:APA91bFVXd9gq_Tul0vs8OedTzw8rqMcCOxOGtLPv8Lq2X0zo4ObFV-S52ymVnUZM8nVyZhJcTxgQTi4U49X_y7zta8KwZskWgIIBOdFItskzQHByEllcNLhs4iC8_kB0SBVN4pLLhN3'


client = nexmo.Client(key='84c52e78', secret='7cDko6GTLSKT2U9M')
push_service = FCMNotification(api_key=api_Key)

registration_id= requests.get("https://smart-kitchen-aac83.firebaseio.com/9FbP47wyKDUREHziot5J4OcxyD72/device_id.json").json()
name= requests.get("https://smart-kitchen-aac83.firebaseio.com/9FbP47wyKDUREHziot5J4OcxyD72/name.json").json()
print(registration_id)
print(name)
al=0

def fire_alart(registration_id):
    message_title = "Fire Alert"
    message_body = "Hi "+name+", This is fire alarm!"
    result = push_service.notify_single_device(registration_id=registration_id, message_title=message_title, message_body=message_body)
    client.send_message({
    'from': 'Smart Kitchen',
    'to': '8801622284990',
    'text': message_body,
    })
    return print(result)

while True:
    temp=requests.get("https://smart-kitchen-aac83.firebaseio.com/9FbP47wyKDUREHziot5J4OcxyD72/temp.json").json()
    print("temp: ",temp)
    gas=requests.get("https://smart-kitchen-aac83.firebaseio.com/9FbP47wyKDUREHziot5J4OcxyD72/gas.json").json()
    print("gas: ",gas)

    if temp>40 and gas>30 and al==0:
        fire_alart(registration_id)
        al=1
    elif temp<40 or gas<30:
        al=0

if __name__ == "__main__":
    app.run(debug=True)
