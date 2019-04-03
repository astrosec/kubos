/** Simple On-board LED flashing program - written in C by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            
*
* April 3 2019
* Frank Pound Modified by AstroSec for testing with Kubos
* TODO: Shrink the dumb code with iterators/loops over the 4 LEDS
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define LED1_PATH "/sys/class/leds/beaglebone:green:usr3"
#define LED2_PATH "/sys/class/leds/beaglebone:green:usr2"
#define LED3_PATH "/sys/class/leds/beaglebone:green:mmc0"
#define LED4_PATH "/sys/class/leds/beaglebone:green:heartbeat"



void writeLED(char filename[], char value[], char ledPath[]);
void removeTrigger();

int main(int argc, char* argv[]){
   if(argc!=3){
	printf("Usage is makeLEDC and one of:\n");
        printf("   on, off, flash or status\n");
	printf(" e.g. makeLED flash\n");
        return 2;
   }

   if(strcmp(argv[1],"-r")!=0){
	printf("Usage is makeLEDC and one of:\n");
        printf("   on, off, flash or status\n");
	printf(" e.g. makeLED flash\n");
        return 2;
   }

   printf("Starting the makeLED program\n");
   printf("The current LED Path is: " LED1_PATH "\n");
   printf("The current LED Path is: " LED2_PATH "\n");
   printf("The current LED Path is: " LED3_PATH "\n");


   // select whether command is on, off, flash or status
   if(strcmp(argv[2],"on")==0){
        printf("Turning the LEDs on\n");
	removeTrigger();
        writeLED("/brightness", "1", LED1_PATH);
        writeLED("/brightness", "1", LED2_PATH);
        writeLED("/brightness", "1", LED3_PATH);
   }
   else if (strcmp(argv[2],"off")==0){
        printf("Turning the LEDs off\n");
	removeTrigger();
        writeLED("/brightness", "0", LED1_PATH);
        writeLED("/brightness", "0", LED2_PATH);
        writeLED("/brightness", "0", LED3_PATH);
   }
   else if (strcmp(argv[2],"flash")==0){
        printf("Flashing the LEDS\n");
        writeLED("/trigger", "timer", LED1_PATH);
        writeLED("/delay_on", "50", LED1_PATH);
        writeLED("/delay_off", "50", LED1_PATH);

        writeLED("/trigger", "timer", LED2_PATH);
        writeLED("/delay_on", "50", LED2_PATH);
        writeLED("/delay_off", "50", LED2_PATH);

        writeLED("/trigger", "timer", LED3_PATH);
        writeLED("/delay_on", "50", LED3_PATH);
        writeLED("/delay_off", "50", LED3_PATH);

        writeLED("/trigger", "timer", LED4_PATH);
        writeLED("/delay_on", "50", LED4_PATH);
        writeLED("/delay_off", "50", LED4_PATH);

   }
   else if (strcmp(argv[2],"status")==0){
      FILE* fp;   // see writeLED function below for description
      char  fullFileName[100];  
      char line[80];
      sprintf(fullFileName, LED1_PATH "/trigger"); 
      fp = fopen(fullFileName, "rt"); //reading text this time
      while (fgets(line, 80, fp) != NULL){
         printf("%s", line);
      }
      fclose(fp);  

      sprintf(fullFileName, LED2_PATH "/trigger"); 
      fp = fopen(fullFileName, "rt"); //reading text this time
      while (fgets(line, 80, fp) != NULL){
         printf("%s", line);
      }
      fclose(fp);  

      sprintf(fullFileName, LED3_PATH "/trigger"); 
      fp = fopen(fullFileName, "rt"); //reading text this time
      while (fgets(line, 80, fp) != NULL){
         printf("%s", line);
      }
      fclose(fp);  

      sprintf(fullFileName, LED4_PATH "/trigger"); 
      fp = fopen(fullFileName, "rt"); //reading text this time
      while (fgets(line, 80, fp) != NULL){
         printf("%s", line);
      }
      fclose(fp);  
   }
   else{
	printf("Command: %s Is an invalid command!\n",argv[2]);
   }
   printf("Finished the makeLED Program\n");
   return 0;
}

void writeLED(char filename[], char value[], char ledPath[]){
   FILE* fp;   // create a file pointer fp
   char  fullFileName[100];  // to store the path and filename
   sprintf(fullFileName, "%s%s",ledPath, filename); // write path and filename
   fp = fopen(fullFileName, "w+"); // open file for writing
   fprintf(fp, "%s", value);  // send the value to the file
   fclose(fp);  // close the file using the file pointer
}

void removeTrigger(){
  writeLED("/trigger", "none", LED1_PATH);
  writeLED("/trigger", "none", LED2_PATH);
  writeLED("/trigger", "none", LED3_PATH);
  writeLED("/trigger", "none", LED4_PATH);
}
