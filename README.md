This project is intended to be a starting point for those wanting to prepare a MCU based webserver which acquires web related files from an sdcard. For an easy compilation of the codes you can use Eclipse IDE after installation of ARM plugin and setting up the environment.
In the project, FRDM64 platform which encompasses anMK64FN1M0VLL12 CPU and FatFs and lwIP libraries were used. The libraries are modified to get a smooth connection between the file system manipulation layer (FatFs) and TCIP/HTTP layer (lwIP). A precompiled binary file which can be directly flashed to the MCU is also provided, so you can see how the program works without diving inside the coding. :)

Usage:
-Flash the binary to the MCU.
-Prepare an SD card which is formatted to the FAT file system.
-Create a directory on the root fs with name "/webpage".
-Put all relevant web files inside this directory.
-Set your home network IP range to 192.168.1.XXX.
-Connect your board to the network and on your web browser enter 192.168.1.250.
-Then you will see your webpage.

Under the "webpage" folder you can find an example webpage setting which includes a video and plays it on the web browser.
Moreover, the program writes runtime details on the com port (115200bps) attached to the debugger on the board.
So you can observe the traficking between your board and web browser.

By the way, if you like the western genre you can directly watch the video inside the directory:)
The original video was downloaded from here https://www.youtube.com/watch?v=enuOArEfqGo. Thanks to the Danish National Symphony Orchestra for such a nice performance.

