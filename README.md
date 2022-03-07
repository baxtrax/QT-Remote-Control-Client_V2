# QT Remote Control Client V2

This is socket application that is ment to be paired with its QT counter-part [here](https://github.com/baxtrax/QT-Remote-Control-Server_V2). The raspberrypi will communicate with a client via UDP socket and then send movement data over serial to a respective arduino sheild. A sheild was used due to ease of use. The sheild chosen was a iteration of the Arduino Leonardo board. This allows for multiple UART interfaces which will benefitical later on in the project for interfaceing gyros and other sensors.

The previous version of this software was controlling stepper motors, this iteration is controlled 4 DC motors with encoders.

This software is one tiny part of the main robot. There are L298N drivers, a USB Wifi adaptar, a Power Distribution Board, and other electronics that makes the whole robot possible.

## Details

This section will show current features of the application. There will not be any pictures because it is a purely console based application

### Features
* Moves each wheel using PWM and direction pins.
* More currently being developed!

~~More details of how parts of this program work and why design decisions where made can be found on this repositorys respective wiki.~~ (Not started yet)

## Built With

* [Python 3.7](https://www.python.org/downloads/release/python-370/) - The main programming language used
* [Raspberry Pi B3+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/) - Current Embedded Systems running the server

## Authors

* **Bradley G** - *Original Creator* - [Baxtrax](https://github.com/baxtrax)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
