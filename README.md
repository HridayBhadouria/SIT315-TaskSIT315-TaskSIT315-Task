# SIT315 M1 Updated Submission

## Purpose

This repository contains my current working Arduino system and my updated submission evidence.

My system uses a PIR motion sensor, BH1750 light sensor, DHT22 temperature and humidity sensor, and LED. The LED turns on when motion is detected and the room is dark or hot.

## Video

My Panopto video demonstration is:

https://deakin.au.panopto.com/Panopto/Pages/Viewer.aspx?id=c46b076e-2e64-4ae6-a9b0-b4de006edf30

## Files

- `TaskM1.cpp` - current Arduino code.
- `Diagram_of_Board.png` - current wiring diagram.
- `Report_and_Reflection.docx` - report and reflection.
- `current_setup.png` - current hardware photo from the video.
- `code_uploaded.png` - code upload evidence from the video.
- `Video_Link.txt` - video link.

## Wiring

| Part | Connection |
|---|---|
| PIR sensor | OUT to D9, 3.3V, GND |
| DHT22 | DATA to D4, 5V, GND |
| BH1750 | SDA to A4, SCL to A5, 3.3V, GND |
| LED | D6 through a resistor, then GND |

All parts share GND.

## Libraries

- `Wire`
- `DHT`

## Serial Monitor evidence

The program prints a status line at 9600 baud. Before submitting, I will capture my own real Serial Monitor screenshot and save it as `System_Monitoring_Log.png`.

## Current scope

The current code uses `attachInterrupt()` for the PIR sensor. It does not claim to complete the QP3 multi-input pin-change-interrupt requirement.
