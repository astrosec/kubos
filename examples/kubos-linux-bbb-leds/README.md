# Blink LEDS with Kubos Linux

To register the app you must navigate to http://172.16.0.100:8000/graphql and add the following line to the left hand query pane

For Kubos v1.13 and earlier
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

For Kubos v1.14 and later
mutation {
  register(path: "/home/kubos/blinkleds") {
    success,
    errors,
    entry {
      app {
        name: "blinkleds"
        executable: "/home/kubos/blinkleds/kubos-makeLED.py"
      }
    }
  }
}


If successfully registered you will see this output on the right hand results pane for version 1.13:
{
  "data": {
    "register": {
      "success": true,
      "errors": "",
      "entry": {
        "app": {
          "uuid": "1d6daa1b-a58e-4a0a-bdee-817be4e52d92",
          "name": "kubos-linux-makeLED",
          "path": "/home/system/kubos/apps/1d6daa1b-a58e-4a0a-bdee-817be4e52d92/1.0/kubos-linux-makeLED"
        }
      }
    }
  }
}

For  Kubos v1.14
{
  "data": {
    "register": {
      "success": true,
      "errors": "",
      "entry": {
        "app": {
          "name": "kubos-makeLED",
          "executable": "/home/system/kubos/apps/kubos-makeLED/1.14/kubos-makeLED.py"
        }
      }
    }
  }
}
Each time you register a mission application (even the same one) a different UUID is created.  Using the UUID returned from the registration, the execute request should look like this:



For Kubos v1.13
mutation {
  startApp(uuid: "1d6daa1b-a58e-4a0a-bdee-817be4e52d92", runLevel: "OnCommand") {
    success,
    pid
  }
}

For Kubos v1.14 and later

mutation {
  startApp(name: "kubos-makeLED", runLevel: "OnCommand" args: "-sflash") {
    success,
    pid
  }
}


So using the above execute request template above you can now execute and cause the OnCommand callback of your mission application to run.  If you want to pass arguments to your mission application use the following format:

For Kubos v1.13
startApp(uuid: "0206ddb9-0afb-4689-b9c7-83f48de9cfc1", runLevel: "OnCommand"  args: "-soff")

For Kubos v1.14
mutation {
  startApp(name: "kubos-makeLED", runLevel: "OnCommand" args: "-soff") {
    success,
    pid
  }
}

Note: v1.14 removes the UUID field and replaces it with mission application name.  In this case it's kubos-makeLED

In the above case -soff has been passed.  Spaces are important due to a nuance in how Kubos passes the arguments.  You should also note that 
'-r' is automatically added by GraphQL; if you run your mission application by hand you must add -r OnCommand.


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
