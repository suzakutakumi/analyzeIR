const int IN_P = 13;

void setup() {
  Serial.begin(115200);
  pinMode(IN_P, INPUT_PULLUP);
}

void loop() {
  unsigned long t;
  static unsigned long tt[2][320];
  static int cnt = 0;
  if (!digitalRead(IN_P)) {
    // ONの時間を記録
    t = micros();
    while (!digitalRead(IN_P));
    tt[0][cnt] = micros() - t;

    // OFFの時間を記録
    t = micros();
    while (digitalRead(IN_P)) {
      if (micros() - t >= 10000) {
        tt[1][cnt] = micros() - t;
        for(int i=0;i<cnt;i++){
          Serial.print("on:");
          Serial.print(tt[0][i]);
          Serial.print(",off:");
          Serial.println(tt[1][i]);
        }
        cnt=0;
        break;
      }
    }
    tt[1][cnt] = micros() - t;
    cnt++;
  }
}
