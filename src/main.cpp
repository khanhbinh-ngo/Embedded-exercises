/* Change these values based on your calibration values */
#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower D7
#define sensorPin A0

#include <DHT22.h>

//Constants
#define DHTPIN D6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT22 dht(DHTPIN); //// Initialize DHT sensor for normal 16mhz Arduino

float hum = 0;  //Stores humidity value
float temp = 0; //Stores temperature value
int moisture = 0;

#define waterPin D5 // ra tín hiệu điều khiển máy bơm
#define airPin D6 // ra tín hiệu điều khiển quạt

void setup() {
    pinMode(sensorPower, OUTPUT);
    digitalWrite(sensorPower, LOW);
    pinMode(waterPin, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    // Tính giá trị độ ẩm đất trung bình trong 3s
    int moisture_test = 6;
    while (moisture_test--){
      moisture += readSensor();
      delay(500);
    }
    float avg_moisture = moisture/6; 
    // Determine status of our soil
    if (avg_moisture < soilWet) {
      Serial.println("Status: Soil is too wet");
      digitalWrite(waterPin, LOW);  

    } else if (avg_moisture > soilDry) {
        Serial.println("Status: Soil is too dry - time to water!");
        digitalWrite(waterPin, HIGH); 
    }
    Serial.println();
    // tính giá trị nhiệt độ - độ ẩm không khí trong 3s
    int air_test = 6;
    while (air_test--){
      hum += dht.getHumidity();
      temp += dht.getTemperature();
      delay(500);
    }
    float avg_hum = hum/6;
    float avg_temp = temp/6;
    // mở quạt khi độ ẩm > 60% và tắt khi độ ẩm < 40%
    if (avg_hum > 60){
      digitalWrite(airPin, HIGH);
    } else if (avg_hum < 40){
      digitalWrite(airPin, LOW);
    }
    // nhiếu nhiệt độ > 32*c thì mở quạt + kiểm tra độ ẩm để mở bơm nước
    if (avg_temp > 32){
      digitalWrite(airPin, HIGH);
      if (avg_moisture > soilDry) digitalWrite(waterPin, HIGH); 
    }
    Serial.print("Humidity: ");
    Serial.print(avg_hum);
    Serial.print(" %, Temp: ");
    Serial.print(avg_temp);
    Serial.println(" Celsius");
}
//  This function returns the analog soil moisture measurement
int readSensor() {
    digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
    delay(10);                // Allow power to settle
    int val = analogRead(sensorPin);    // Read the analog value form sensor
    digitalWrite(sensorPower, LOW);        // Turn the sensor OFF
    return val;                // Return analog moisture value
}