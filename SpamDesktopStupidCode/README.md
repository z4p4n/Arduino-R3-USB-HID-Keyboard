Spam Desktop (stupid thing)
======

Idiot code for spamming desktop with cat or something else...

Prerequisites
------

mingw32 or mingw64 I guess.


How to compile
------

```
	windres.exe resource.rc -o resource.o
	gcc PwnedScreen.c -o PwnedScreen.o
	gcc PwnedScreen.o resource.o -o pwned.exe -luser32 -lgdi32
```


![alt tag](https://raw.githubusercontent.com/z4p4n/Arduino-R3-USB-HID-Keyboard/master/SpamDesktopStupidCode/pwned.bmp)
