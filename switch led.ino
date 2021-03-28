
  // put your setup code here, to run once:
unsigned long current_val_ms;
unsigned long task_20ms=0;
unsigned long task_500ms;
#define TASK_20MS_ACTIVE 120
#define TASK_500MS_ACTIVE 500
int switch_state =0;
int ledstate=0;

void setup()
 {
  
pinMode(7,INPUT_PULLUP);
pinMode(10,OUTPUT);
 }
 void loop()
 {
   current_val_ms = millis();

  //20 ms task

if((current_val_ms - task_20ms) >= TASK_20MS_ACTIVE)
{
  task_20ms = current_val_ms;
if(digitalRead(7) == LOW)
{
  switch_state++;
}
}
//500 ms task
if((current_val_ms-task_500ms)>=TASK_500MS_ACTIVE)
{
  task_500ms= current_val_ms;
  if(switch_state)
  {
    ledstate= ledstate^1;
    digitalWrite(10,ledstate);
    (switch_state--);
  }
  else
  {
    digitalWrite(10,LOW);
  }
}
}


