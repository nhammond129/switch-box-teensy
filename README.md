# switch-box-teensy

Using a teensy LC and 4x HC165s
emulating a gamepad device

* Custom shiftIn function (`inShift32`) used since arduino-provided one seems to drop the first bit (clocking difference issue i think)


Rough schematic
----

D0..D7 for each HC165 is tied to a switch input. 3.3v for logical high and pulling down with 10k and[^1] 100k ohm resistors

![image](https://user-images.githubusercontent.com/2228057/157795084-ae7e29f5-5b62-4bdb-a68c-dcb28353325c.png)

Using
----

Use `USB Type: "Keyboard + Mouse + Joystick"`

![image](https://user-images.githubusercontent.com/2228057/157785393-04cdb5fe-4c3a-412a-a831-1fd90b5592cb.png)


[^1] mixed due to insufficient quantity on hand at the time...
