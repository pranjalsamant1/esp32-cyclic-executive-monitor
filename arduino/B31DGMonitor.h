
#ifndef B31DGMonitor_h
#define B31DGMonitor_h

#include "Arduino.h"

#define NUMBER_TASKS 5
#define TEST_TIME 10000000

class B31DGCyclicExecutiveMonitor {

private:

    boolean isActive = false;

    unsigned long timeStart = 0;  
    unsigned long timeRelease[NUMBER_TASKS];
    unsigned long timeNextDeadlines[NUMBER_TASKS];

    unsigned long counterJobs[NUMBER_TASKS];
    unsigned long taskViolations[NUMBER_TASKS];

    unsigned long taskRateRequirements[NUMBER_TASKS] = 
         {    4000,  // 1 - digital output signal
             20000,  // 2 - frequency monitor, minimum frequency 333Hz 
              8000,  // 3 - frequency monitor, minimum frequency 500Hz
             20000,  // 4 - sample and filter analog input, and ouput error code
            100000,  // 5 - log to serial port
         };
     
    void printSummary();              

public:
    B31DGCyclicExecutiveMonitor();// declare one global instance of this class in your program
    void jobStarted(int task);    // Call this method whenever your program starts executing an instance of task #task
    void jobEnded(int task);      // Call this method whenever your program completed the execution of an instance of task #task
    void startMonitoring();   // Call this method once, i.e. in the setup/main function of your program, to activate the monitoring    
    unsigned long getTimeStart(); // Call this method to know at what time (micros) startMonitoring was called
};


#endif

