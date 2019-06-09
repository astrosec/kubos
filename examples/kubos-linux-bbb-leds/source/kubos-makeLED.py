#!/usr/bin/env python
import subprocess
import argparse
import app_api
import sys


#SERVICES = app_api.Services()

def on_boot(logger):

    logger.info("OnBoot logic")

def on_stop(logger):

    logger.info("OnStop logic")
    try:
        cmd = ['/home/kubos/blinkleds/kubos-linux-makeLED' , "-r", "off"]
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        o,e = proc.communicate()
        logger.info("LED STOP " + o.decode('ascii'))
    except Exception as ex:
        logger.error("Something went wrong in LED blinker: " + str(ex) + str(e.decode('ascii')) + str(proc.returncode) + "\r\n")
        logger.error("LED ERROR ")
        sys.exit(1)

def on_command(logger,subcommand):

    logger.info("OnCommand logic" +  str(subcommand))
    try:
        cmd = ['/home/kubos/blinkleds/kubos-linux-makeLED' , '-r', str(subcommand)]
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
    theargs = str(sys.argv[1:])
    theargs.replace("--","")
    logger.info("args are " + theargs)

    if "--" in sys.argv: sys.argv.remove("--")

    parser = argparse.ArgumentParser(theargs)

    parser.add_argument('--run', '-r')
    parser.add_argument('--subcommand', '-s')

    args = parser.parse_args()

    logger.info("args are " + str(args))

    if args.run == 'OnBoot':
        on_boot(logger)
    elif args.run == 'OnCommand':
        on_command(logger,args.subcommand)
    else:
        logger.error("Unknown run level specified")
        sys.exit(1)

if __name__ == "__main__":
    main()
