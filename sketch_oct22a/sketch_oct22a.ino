#include<OneWire.h>
#include<DallasTemperature.h>
#define BUS 3
OneWire onewire(BUS);
DallasTemperature sensors(&onewire);
void setup() {
  //6.8k (DS18b20数字输出引脚需要接4.7k-10k上拉电阻)
  //针脚定义 面朝印字面，左为GND,右为VCC,中间为数字输出引脚（接4.7-10k上拉电阻）
  Serial.begin(9600);
  sensors.begin();
  sensors.setWaitForConversion(false);
}

unsigned long previousMillis = 0; //毫秒时间记录
const long interval = 1000;       //时间间隔
void loop() {
   //以下段落相当于每秒读取前次温度，并发起新一次温度转换
  unsigned long currentMillis = millis();         //读取当前时间
  if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
  {
    previousMillis = currentMillis; //更新时间记录

    float tempC = sensors.getTempCByIndex(0); //获取索引号0的传感器摄氏温度数据
   
      Serial.print("\n当前温度是： ");
      Serial.print(tempC);
      Serial.println(" ℃");
    

    Serial.println("发起温度转换");
    sensors.requestTemperatures(); //发起新的温度转换
  }
  delay(20);
}
