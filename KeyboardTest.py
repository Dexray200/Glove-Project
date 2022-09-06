import keyboard

keyboard.add_hotkey('f', lambda: keyboard.send(77))  # 77 is scan code for right arrow
keyboard.add_hotkey('d', lambda: keyboard.send(75))  # 75 is scan code for left arrow
keyboard.wait()  # keeps code running
