# Blink LEDS with Kubos Linux

This is a demo program which blinks the LEDS on the BBB 

Example run:

/home/kubos/blinkleds # ./kubos-linux-makeLED
Usage is makeLEDC and one of:
   on, off, flash or status
 e.g. makeLED flash

/home/kubos/blinkleds # ./kubos-linux-makeLED -r on
Starting the makeLED program
The current LED Path is: /sys/class/leds/beaglebone:green:usr3
The current LED Path is: /sys/class/leds/beaglebone:green:usr2
The current LED Path is: /sys/class/leds/beaglebone:green:mmc0
Turning the LEDs on
Finished the makeLED Program

/home/kubos/blinkleds # ./kubos-linux-makeLED -r off
Starting the makeLED program
The current LED Path is: /sys/class/leds/beaglebone:green:usr3
The current LED Path is: /sys/class/leds/beaglebone:green:usr2
The current LED Path is: /sys/class/leds/beaglebone:green:mmc0
Turning the LEDs off
Finished the makeLED Program


Included is a Kubos mission application service wrapper in python to call this C program.

Register the program with http://172.16.0.100:8000/graphiql

mutation {
  register(path: "/home/kubos/blinkleds") {
    success,
    errors,
    entry {
      app {
        uuid
        name
        path
      }
    }
  }
}


You can now execute and cause the OnCommand callback of your mission application to run.  If you want to pass arguments to your mission application use the following format:

startApp(uuid: "0206ddb9-0afb-4689-b9c7-83f48de9cfc1", runLevel: "OnCommand"  args: "-soff")

Do not add a space between S and off.  This is a nuance with Kubos handling of argument passing.  We can deal with it for now.  As it stands now the args terminate with empty space.
