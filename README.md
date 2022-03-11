# switch-box-teensy

Using a teensy LC and 4x HC165s
emulating a gamepad device

* Custom shiftIn function (`inShift32`) used since arduino-provided one seems to drop the first bit (clocking difference issue i think)

Using
----

Use `USB Type: "Keyboard + Mouse + Joystick"`

![image](https://user-images.githubusercontent.com/2228057/157785393-04cdb5fe-4c3a-412a-a831-1fd90b5592cb.png)
