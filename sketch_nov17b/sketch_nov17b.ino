/*
Measuring AC Current Using ACS712 - www.nn-digital.com 
*/ 
const int analogIn = A0;
int mVperAmp = 185; // 185 = ACS712 5A, 100 = ACS712 20A, 66 = ACS712-30A
int ACSoffset = 2500; 
double Voltage = 0;

float amplitude_current;               //amplitude current
float effective_value;       //effective current 

void setup() 
{
     Serial.begin(9600);
     pinMode(analogIn, INPUT);
}

void loop() 
{
     int sensor_max;
     sensor_max = getMaxValue();

     Serial.print("Sensor_max = ");
     Serial.println(sensor_max);

     Voltage = (sensor_max / 1023) * 5000; // Voltage ( mV )
     amplitude_current = ((Voltage - ACSoffset) / mVperAmp); 
     effective_value = amplitude_current / 1.414;

     Serial.print("Current Max (A) : ");
     Serial.println(amplitude_current,6);//6 number after the decimal point
     Serial.print("Current RMS (A) : ");
     Serial.println(effective_value,6);
     Serial.println();
}

/*
Function: Sampling 5000ms and get the maximum value from A0 pin
*/
int getMaxValue()
{
     int sensorValue;             //value read from the sensor
     int sensorMax = 0;
     uint32_t start_time = millis();
     while((millis()-start_time) < 1000)
     {
         sensorValue = analogRead(analogIn);
         if (sensorValue > sensorMax) 
         {
             //record the maximum sensor value
             sensorMax = sensorValue;
         }
     }
     return sensorMax;
}
