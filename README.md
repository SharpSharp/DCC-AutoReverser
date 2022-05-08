# DCC-AutoReverser
An Arduino sketch to sense for a train entering a reversing loop on a DCC model railway and then switch the track polarity when required.

Two current sensors are required, one for each rail in the reversing section. Two relay channels are also required to swicth each each.
The sketch can control more than one reversing section. The Arduinos Analog inputs limit on the number of reversers. The current sensors use analog pins. The 6 analog pins on an Uno allow 3 reversing sections, a Nano's 8 can control 4.

![Auto-Reverser-Diagram 001](https://user-images.githubusercontent.com/1519154/161913969-69074afe-064f-43a8-8b3f-f5866842c4ea.png)
