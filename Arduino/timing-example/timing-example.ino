void setup() {
  // put your setup code here, to run once:
  on_time_short_MIN = 8000;
  on_time_short_MAX = 15000;

  on_time_med_MIN = 30000:
  on_time_med_MAX = 60000;

  on_time_long_MIN = 120000; // 2 minutes
  on_time_long_MAX = 480000; // 8 minutes

  off_time_short_MIN = 8000;
  off_time_short_MAX = 20000;

  off_time_med_MIN = 40000:
  off_time_med_MAX = 80000;

  off_time_long_MIN = 180000; // 3 minutes
  off_time_long_MAX = 900000; // 15 minutes

  rand_wait_MIN = 4000;
  rand_wait_MAX = 16000;
  rand_wait_Chance = 5; // 5%
  
  on_time_Millis = millis();
  off_time_Millis = millis();
}

void loop() {
  category = random(0,100);
  if category < 15 {
    // on_time_short
  }
  else if category >= 15 && category <= 80 {
    // on_time_medium
  }
  else {
    // on_time_long
  }
  // put your main code here, to run repeatedly:
  currentMillis = millis(); 
  
}
