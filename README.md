# Thumb Ping Pong. 
A portable 2-player ping pong game, played with your thumbs! Made with FreeRTOS.

![IMG_3209](https://user-images.githubusercontent.com/87585163/164989261-2fc0a729-637f-413a-a766-4ecf5befb7f3.jpg)

## About the project: 
Thumb Ping Pong is a portable ping pong game made with simple LED's and buttons. In my iteration, I interfaced an Arduino and STM32 with SPI. 

There are FreeRTOS tasks which are all the same priority, so they simultaneously check for sent and received data, as well as control the flow of the game.
In essence, it is a multithreaded system. 

The main code for the STM32 board can be found in STM32_Configs->Core->Src->main.c
However the whole STM32 project needs to be flashed on to the board to make it work. 

The main code for the can be found in Arduino_Configs-> Arduino_Configs.ino
