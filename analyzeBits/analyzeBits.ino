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
      // OFFの時間が10ms以上なら読み取り終わり
      if (micros() - t >= 10000) {
        // ビット値を入れる配列を用意
        unsigned long long bits[8];
        for(int i=0;i<8;i++)bits[i]=0;

        // bitsにビット情報を入れる
        for (int i = 0; i < cnt-1; i++) {
          if(i%64!=0){
            bits[i/64] <<= 1;
          }
          bits[i/64] |= (tt[1][i+1] >= 1000 ? 1 : 0);
        }

        // bitsを16進数で表示
        for(int i=0;i<=(cnt-2)/64;i++){
          Serial.print(bits[i],HEX);
        }
        Serial.println();
        cnt = -1;
        break;
      }
    }
    // cntが-1ならifを抜ける
    if(cnt==-1){
      cnt=0;
      return;
    }
    tt[1][cnt] = micros() - t;
    cnt++;
  }
}
