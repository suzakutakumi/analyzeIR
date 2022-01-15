const int OUT_P=23;
const int T=425;

char *code[] = {"80080002FDFF0033CC49B6C83706F900FF00FF00FF00FF00FFCA358B7400FF00FF",
                "80080002FDFF0033CC49B6C83706F900FF00FF00FF00FF00FFCA35837C00FF00FF"
               };

void Wait(unsigned long t, int HL) {
  unsigned long tt = micros(),wt;
  while (micros() - tt <= t) {
    digitalWrite(OUT_P, HL);
    wt=micros();
    while(micros()-wt<=8);
    digitalWrite(OUT_P, LOW);
    delayMicroseconds(12);
    wt=micros();
    while(micros()-wt<=8);
  }
}

void Send(char *str) {
  int x, i, j = 0, cnt = 0, xx[256];
  // コード解析
  while (str[cnt] != '\0') {
    if ('0' <= str[cnt] && str[cnt] <= '9') {
      xx[cnt] = str[cnt] - '0';
    } else {
      xx[cnt] = str[cnt] - 'A' + 10;
    }
    cnt++;
  }
  
  //リーダー部
  Wait(8 * T, HIGH);
  Wait(4 * T, LOW);
  //本体データ
  for (j = 0; j < cnt; j++) {
    for (i = 3; i >= 0; i--) {
      Wait(T, HIGH);
      Wait(((xx[j] >> i) & 0b1) * 2 * T + T, LOW);
    }
  }
  Wait(T, HIGH);
  digitalWrite(OUT_P, LOW);
}

void setup()
{
  Serial.begin(115200);
  pinMode(OUT_P,OUTPUT);
}

void loop()
{
  if(Serial.available()>0){
    char c=Serial.read();
    if(c=='O'){
      Send(code[0]);
    }else if(c=='N'){
      Send(code[1]);
    }
  }
  delay(1);
}
