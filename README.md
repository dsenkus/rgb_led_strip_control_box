RGB Led Strip Control Box
=========================

This is simple Arduino based RGB led strip project. The circuit is simple
enough so I will not bother drawing it's schematics. You can always contact me
if you have any questions. 

The initial idea was to create fully programmable RGB led strip controller
which would be used instead of cheap chinese ones. 

Circuit description
-------------------

It's simple Atmega328P-PU chip with 3 mosfets/transistors connected to PWN outputs. 
Circuit also contains DS1307 timer chip and IR receiver for remote controller.

Features
--------
* Highly configurable Pulse/Fade effects classes
* Multiple predefined colors
* Smooth transitions between colors
* Blink and fade effects for all colors
* Light alarm function (the light would gradually increase over 15-20 minutes at any specified time)
