#include <LSM303.h>
#include <Wire.h>

LSM303 c;
LSM303::vector pos;
LSM303::vector vel;
long lastTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  c.init();
  c.enableDefault();
  initData();
}

void loop() {
  c.read();
  long thisTime = micros();
  float dt = (float)(thisTime-lastTime);
  updateData(dt);
  printData();
}

void initData(){
  pos.x = 0;
  pos.y = 0;
  pos.z = 0;
  vel.x = 0;
  vel.y = 0;
  vel.z = 0;
}

void updateData(float dt){
  pos.x += .5 *(c.a.x) * dt *dt + vel.x * dt;
  pos.y += .5 *(c.a.y) * dt *dt + vel.y * dt;
  pos.z += .5 *(c.a.z) * dt *dt + vel.z * dt;
  vel.x += (c.a.x)*dt;
  vel.y += (c.a.y)*dt;
  vel.z += (c.a.z)*dt;
}

void printData(){
  Serial.print("V: ");
  Serial.print(vel.x);
  Serial.print(" ");
  Serial.print(vel.y);
  Serial.print(" ");
  Serial.print(vel.z);
  Serial.print(" ");
  Serial.print("P: ");
  Serial.print(pos.x);
  Serial.print(" ");
  Serial.print(pos.y);
  Serial.print(" ");
  Serial.print(pos.z);
  Serial.print(" ");
  Serial.println();
}
