import paho.mqtt.client as mqtt
from time import sleep
import serial

ser=serial.Serial('COM3',9600,timeout=1)
client=mqtt.Client()
access_token="Enter Access Token Here"
port=1883
broker_name='demo.thingsboard.io'
client.username_pw_set(access_token)
client.connect(broker_name,port,10)

while True:
    data=ser.readline()
    data=data.decode()
    if len(data)>0:
        humidity=data[0:2]
        temperature=data[6:8]
        msg='{"Humidity":"'+str(humidity)+'","Temperature":"'+str(temperature)+'"}'
        client.publish('v1/devices/me/telemetry',msg)
