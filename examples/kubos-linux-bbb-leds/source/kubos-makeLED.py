#!/usr/bin/env python
import subprocess
import argparse
import app_api
import sys

def on_command(logger,subcommand):

    logger.info("OnCommand logic" +  subcommand)

    try:
        cmd = ['/home/kubos/blinkleds/kubos-linux-makeLED' , subcommand]
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        o,e = proc.communicate()
        logger.info("LED FLASH " + o.decode('ascii'))
    except Exception as ex:
        logger.error("Something went wrong in LED blinker: " + str(ex) + str(e.decode('ascii')) + str(proc.returncode) + "\r\n")
        logger.error("LED ERROR ")
        sys.exit(1)

def main():
 
    logger = app_api.logging_setup("kubos-linux-makeLED")

    logger.info("Entering main LED logic BLINKER!!! ")

    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-c',
        '--config',
        nargs=1,
        help='Specifies the location of a non-default configuration file')

    parser.add_argument(
        '-s',
        '--subcommand',
        help='on, off, flash')

    args = parser.parse_args()

    if args.config is not None:
        global SERVICES
        SERVICES = app_api.Services(args.config[0])
    else:
        SERVICES = app_api.Services()     

    logger.info("Command to LED Blinker is " + str(args.subcommand))

    if args.subcommand == 'flash':
        on_command(logger,'flash')
    elif args.subcommand == 'off':
        on_command(logger,'off')
    elif args.subcommand == 'on':
        on_command(logger,'on')
    else:
        logger.error("Bad command to led blinker " + args.subcommand)

if __name__ == "__main__":
    main()
