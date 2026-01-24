#include "Arduino.h"
#include "B31DGMonitor.h"

B31DGCyclicExecutiveMonitor::B31DGCyclicExecutiveMonitor()
{
   this->timeStart = micros();
}

unsigned long B31DGCyclicExecutiveMonitor::getTimeStart()
{
    return this->timeStart; 
}
    
void B31DGCyclicExecutiveMonitor::startMonitoring()
{
    timeStart = micros();
    this->isActive = true;
    // find the next deadlines
    for (int i=0; i< NUMBER_TASKS; i++) {
      this->timeRelease[i] = timeStart;
      this->counterJobs[i] = 0;
      this->taskViolations[i]= 0;
      this->timeNextDeadlines[i] =  timeStart + this->taskRateRequirements[i];
    }
}

void B31DGCyclicExecutiveMonitor::jobStarted(int taskNumber)
{
  if (!this->isActive) return;
  
  taskNumber--;

  unsigned long now = micros();

  if ( (now - this->timeStart) > TEST_TIME) {
    this->printSummary();
    exit(0);
  }


  if (now < this->timeRelease[taskNumber]) {
    taskViolations[taskNumber]++;
  } 
}

void B31DGCyclicExecutiveMonitor::jobEnded(int taskNumber)
{
  if (!this->isActive) return;
  
  unsigned long now = micros();

  taskNumber--;

  this->counterJobs[taskNumber]++;

  if (now > this->timeNextDeadlines[taskNumber]) {
    this->taskViolations[taskNumber]++; 
  }

  this->timeRelease[taskNumber] = this->timeNextDeadlines[taskNumber];
  this->timeNextDeadlines[taskNumber] += this->taskRateRequirements[taskNumber];
  
}


void B31DGCyclicExecutiveMonitor::printSummary()
{
    Serial.println("PERFORMANCE SUMMARY");
    for (int i=0; i< NUMBER_TASKS; i++) {
      Serial.print("Task #");
      Serial.print((i+1));
      Serial.print("  ");
      Serial.print(taskViolations[i]);
      Serial.print("/");
      Serial.print(this->counterJobs[i]);
      Serial.println(" violations");
    }

}

