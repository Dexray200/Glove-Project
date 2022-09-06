"""
ECE 405 - Summer 2021
BLE Connection and Data Reading
Date: June 13th, 2021
Mason Burt
Dexter Elmendorf, Keri Henschen, Spencer Smith
-------------
Code to connect to Arduino Nano RP2040 Connect set up as BLE peripheral and read data from it
Used Bleak example code on enabling notifications, link below
https://github.com/hbldh/bleak/blob/develop/examples/enable_notifications.py
"""

import asyncio
from bleak import BleakClient
import mouse
import keyboard


positionList = [0] * 5  # declare a list of length 5 with placeholder values of 0
splayList = [0] * 5  # declare another list to hold the splay values
global i
i = 0  # list position variable
global listType
listType = 0  # position or splay array pointer, 0 for position, 1 for splay


CHARACTERISTIC_UUID = "40510001-4786-42e7-bd27-45257b2e988f"  # characteristic uuid you want to receive data from
ADDRESS = "84:cc:a8:2f:c6:c2"  # Put mac address of arduino nano being used here


def notification_handler(sender, data):
    """Simple notification handler which prints the data received."""
    newdata = data.decode('UTF-8')  # convert bytearray to string
    print(newdata)


async def run(address):
    async with BleakClient(address) as client:
        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        await asyncio.sleep(float('inf'))  # receive data infinitely until shut off
        await client.stop_notify(CHARACTERISTIC_UUID)


if __name__ == "__main__":

    loop = asyncio.get_event_loop()
    loop.run_until_complete(run(ADDRESS))
