"""
ECE 405 - Summer 2021
BLE Connection, Data Reading, and Gesture Control
Date: June 27th, 2021
Mason Burt
Dexter Elmendorf, Keri Henschen, Spencer Smith
-------------
Code to connect to Arduino Nano RP2040 Connect set up as BLE peripheral and read data from it
With additional code for gesture control and updated gloves
Used Bleak example code on enabling notifications, link below
https://github.com/hbldh/bleak/blob/develop/examples/enable_notifications.py
"""

import asyncio
from bleak import BleakClient
import keyboard


positionList = [0] * 5  # declare a list of length 5 with placeholder values of 0
splayList = [0] * 5  # declare another list to hold the splay values
joystickList = [0] * 2
global spiderGesture
spiderGesture = 0
global pinchGesture
pinchGesture = 0
global grabGesture
grabGesture = 0
global peaceGesture
peaceGesture = 0
global buttonA
buttonA = 0
global buttonB
buttonB = 0
global i
i = 0  # list position variable
global spiderPressed
spiderPressed = 0
global spiderCounter
spiderCounter = 0
global peacePressed
peacePressed = 0
global peaceCounter
peaceCounter = 0
dataSpecifier = 0
# what data is coming in, 0 for position array, 1 for splay array, 2 for joystick
# 3 for button A, 4 for button B, 5-8 are for gesture booleans


CHARACTERISTIC_UUID = "40510001-4786-42e7-bd27-45257b2e988f"  # characteristic uuid you want to receive data from
ADDRESS = "84:cc:a8:2e:ec:16"  # Put mac address of arduino nano being used here


def notification_handler(sender, data):
    """Simple notification handler which prints the data received."""

    global i
    global dataSpecifier
    global buttonA
    global buttonB
    global spiderGesture
    global pinchGesture
    global grabGesture
    global peaceGesture
    global spiderPressed
    global spiderCounter
    global peaceCounter
    global peacePressed

    newdata = int.from_bytes(data, "little")  # convert bytearray to int

    if dataSpecifier == 0:  # check if the 5 incoming values are for position
        if i < 4:  # if up to 4 values have been read
            positionList[i] = newdata  # write data into array
            i = i + 1  # update pointer variable
        elif i == 4:  # if 4 values have been written
            positionList[i] = newdata  # write data into last array spot
            """f = open("output.txt", "a")  # save data array to txt document
            print('Position', file=f)
            print(positionList, file=f)
            f.close()"""
            print('Position')
            print(positionList)  # print data array to monitor for ease of testing
            i = 0  # reset pointer to first array spot
            # 1st, 3rd, 5th, etc data arrays saves finger position from thumb to pinky
            # 2nd, 4th, 6th, etc data arrays saves finger splay from thumb to pinky
            dataSpecifier = 1  # get ready for incoming 5 splay data points
    elif dataSpecifier == 1:  # check if the 5 incoming values are for splay
        if i < 4:  # if up to 4 values have been read
            splayList[i] = newdata  # write data into array
            i = i + 1  # update pointer variable
        elif i == 4:  # if 4 values have been written
            splayList[i] = newdata  # write data into last array spot
            """f = open("output.txt", "a")  # save data array to txt document
            print('Splay', file=f)
            print(splayList, file=f)
            f.close()"""
            print('Splay')
            print(splayList)  # print data array to monitor for ease of testing
            i = 0  # reset pointer to first array spot
            # 1st, 3rd, 5th, etc data arrays saves finger position from thumb to pinky
            # 2nd, 4th, 6th, etc data arrays saves finger splay from thumb to pinky
            dataSpecifier = 2  # set next data as joystick input
    elif dataSpecifier == 2:  # next values are joystick inputs
        if i == 0:
            joystickList[i] = newdata
            i = 1
        elif i == 1:
            joystickList[i] = newdata
            print('joystickList')
            print(joystickList)
            #   Normalizes the Analog Thumbstick Posn
            # xpos = int(joystickList[0] - 223)
            # ypos = int(joystickList[1] - 238)
            #   Moves the cursor based on thumb stick
            # mouse.move(xpos, ypos, absolute=False, duration=0.1)
            i = 0
            dataSpecifier = 3  # set next value as button A
    elif dataSpecifier == 3:  # next value is button A
        buttonA = newdata
        print('buttonA')
        print(buttonA)
        dataSpecifier = 4  # set next value as button B
    elif dataSpecifier == 4:  # next value is button B
        buttonB = newdata
        print('buttonB')
        print(buttonB)
        dataSpecifier = 5  # set next value as gesture 1
    elif dataSpecifier == 5:  # spider man gesture
        spiderGesture = newdata
        if spiderGesture == 1 and spiderPressed == 0:
            print('spiderGesture on')
            keyboard.press('LEFT_ARROW')  # 75 is scan code for left arrow
            spiderPressed = 1
            #time.sleep(5)  # wait 5 seconds to stop extra gesture readings
        elif spiderPressed == 1:
            if spiderCounter <= 30:
                spiderCounter = spiderCounter + 1
            elif spiderCounter > 30:
                spiderCounter = 0
                spiderPressed = 0
        dataSpecifier = 6
    elif dataSpecifier == 6:  # pinch gesture
        pinchGesture = newdata
        if pinchGesture == 1:
            print('pinchGesture on')
            # do x
        dataSpecifier = 7
    elif dataSpecifier == 7:  # grab gesture
        grabGesture = newdata
        if grabGesture == 1:
            print('grabGesture on')
            # do x
        dataSpecifier = 8
    elif dataSpecifier == 8:  # peace gesture
        peaceGesture = newdata
        if peaceGesture == 1 and peacePressed == 0:
            print('peaceGesture on')
            keyboard.send('RIGHT_ARROW')  # 77 is scan code for right arrow
            peacePressed = 1
            #time.sleep(5)  # wait 5 seconds to stop extra gesture readings
        elif peacePressed == 1:
            if peaceCounter <= 30:
                peaceCounter = peaceCounter + 1
            elif peaceCounter > 30:
                peaceCounter = 0
                peacePressed = 0
        dataSpecifier = 0  # reset data reader


async def run(address):
    async with BleakClient(address) as client:
        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        await asyncio.sleep(float('inf'))  # receive data infinitely until shut off
        await client.stop_notify(CHARACTERISTIC_UUID)


if __name__ == "__main__":
    f = open("output.txt", "w")  # purge any old readings from output file
    f.close()
    loop = asyncio.get_event_loop()
    loop.run_until_complete(run(ADDRESS))