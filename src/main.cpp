// // Sensor pins
// #define sensorPower D7
// #define sensorPin A0

// void setup() {
//     pinMode(sensorPower, OUTPUT);
    
//     // Initially keep the sensor OFF
//     digitalWrite(sensorPower, LOW);
    
//     Serial.begin(9600);
// }

// void loop() {
//     //get the reading from the function below and print it
//     Serial.print("Analog output: ");
//     Serial.println(readSensor());
    
//     delay(1000);
// }

// //  This function returns the analog soil moisture measurement
// int readSensor() {
//     digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
//     delay(10);                // Allow power to settle
//     int val = analogRead(sensorPin);    // Read the analog value form sensor
//     digitalWrite(sensorPower, LOW);        // Turn the sensor OFF
//     return val;                // Return analog moisture value
// }

/* Change these values based on your calibration values */
#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower D7
#define sensorPin A0

#include <DHT22.h>

//Constants
#define DHTPIN D8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT22 dht(DHTPIN); //// Initialize DHT sensor for normal 16mhz Arduino

float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
    pinMode(sensorPower, OUTPUT);
    
    // Initially keep the sensor OFF
    digitalWrite(sensorPower, LOW);

    
    Serial.begin(9600);
}

void loop() {
    //get the reading from the function below and print it
    int moisture = readSensor();
    Serial.print("Analog Output: ");
    Serial.println(moisture);

    // Determine status of our soil
    if (moisture < soilWet) {
        Serial.println("Status: Soil is too wet");
    } else if (moisture >= soilWet && moisture < soilDry) {
        Serial.println("Status: Soil moisture is perfect");
    } else {
        Serial.println("Status: Soil is too dry - time to water!");
    }
    
    delay(500);    // Take a reading every second for testing
            // Normally you should take reading perhaps once or twice a day
    Serial.println();

    hum = dht.getHumidity();
    temp= dht.getTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(500); //Delay 2 sec.
}

//  This function returns the analog soil moisture measurement
int readSensor() {
    digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
    delay(10);                // Allow power to settle
    int val = analogRead(sensorPin);    // Read the analog value form sensor
    digitalWrite(sensorPower, LOW);        // Turn the sensor OFF
    return val;                // Return analog moisture value
}