/******************************************************************
* Created by: Otávio Martins
* Created on: Fev 2024
* version: 1.0  
* Esp32 S3 Dev Module
* Ublox Neo 7M GPS Module
*
* This code is a simple example of how to use the Ublox Neo 7M GPS 
* Module with the Esp32 S3 Dev Module and gps data from NMEA protocol 
*******************************************************************/

#include <Arduino.h>

#define NUM_SENTENCAS 3

// --- / --- Function Declarations ---
String seqRetData(String *SEQ, uint8_t pos);                 // GPS Returns the isolated data from the sequence based on the requested position
bool gpsSetData();                                           // GPS Sets GPS data with processed sentences
void gpsTask(void *pvParameters);                            // Task function to continuously collect GPS sentences
bool nmea0183_checksum(const char *nmea_data);               // Verifies if the checksum of an NMEA0183 sentence is correct
// -----------------------------

// --- GPS Data Structure ---
typedef struct
{
  float     lat;  
  float     lon; 
  uint8_t   fix; 
  uint8_t   sat; 
  float     hdop;
  float     alt; 
  float     vel; 
  float     bea;  
  char      hor[7];
  char      date[7]; 
  char      isfix[2];
  bool      isnew = false;   
  bool      isvalid = false; 
}  Datagps;

// --- Global Variables ---

Datagps gps;  // GPS Data

String sentenca[NUM_SENTENCAS] = {"$GPGGA", "$GPVTG", "$GPRMC"};
String sentData[NUM_SENTENCAS];                               // Data for each sentence
bool sentencaValida[NUM_SENTENCAS] = {false, false, false};   // Flag to validate if the sentence was received and is correct

// --------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  delay(100);
  Serial.println("NMEA GPS Sentence Example v1.0");  

  xTaskCreate(gpsTask, "GPS Task", 2048, NULL, 1, NULL);   // Adjust stack size as needed

  // Set to get new data
  gps.isnew = false;
  gps.isvalid = false;
}

void loop() {
  
  // Get GPS data from NMEA sentences
  gpsSetData();
  delay(1000);
}

// --- Task function to continuously collect GPS sentences ---
void gpsTask(void *pvParameters) {
  char buffer[512];             // Buffer for serial reading
  int bufferIndex = 0;          // Buffer index
  String tempBuffer = "";       // Accumulator for serial data
  String currentSentence = "";  // Current sentence being read


  // Initialize with sentences not validated
  for (int i = 0; i < 3; i++) {
    sentencaValida[i] = false;
  }

  while (true) {
    // If there is data available on the serial
    if (Serial2.available() > 0) {
      // Continuous reading of serial data
      while (Serial2.available()) {
        char incomingByte = Serial2.read();  // Reads the next byte
        tempBuffer += incomingByte;   // Accumulates the read bytes
        // If we find the end of a sentence, like '\n'
        if (incomingByte == '\n') {          
          // Serial.println(tempBuffer);
          // For each requested sentence, check if it was found in the buffer
          for (int i = 0; i < 3; i++) {
            // Check if the sentence was found
            if (tempBuffer.startsWith(sentenca[i]) && !sentencaValida[i]) {
              // Stores the validated sentence
              if (nmea0183_checksum(tempBuffer.c_str())) {
                sentData[i] = tempBuffer;  // Stores the complete sentence
                sentencaValida[i] = true;  // Marks as valid
                Serial.print("Sentença " + sentenca[i] + " válida recebida: " + tempBuffer);
              } else {
                Serial.println("Erro de checksum na sentença: " + sentenca[i]);
              }
            }
          }
          tempBuffer = "";  // Clears the buffer after processing
        }
      }
    }
    
    // Check if all sentences were received
    bool allValid = true;
    for (int i = 0; i < 3; i++) {
      if (!sentencaValida[i]) {
        allValid = false;
        break;
      }
    }

    // If all sentences are valid, restart reading
    if (allValid) {
      // Serial.println("Todas as sentenças válidas foram recebidas!");
      gps.isnew = true;
      // Reset variables if necessary
      for (int i = 0; i < 3; i++) {
        sentencaValida[i] = false;
      }
    }
    
    vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to avoid processor overload
  }
} // --- END Task function to continuously collect GPS sentences ---

// --------------------------------------------------------------------------
// --- Function to read and process GPS data ---

// --- Verifies if the checksum of an NMEA0183 sentence is correct ---
bool nmea0183_checksum(const char *nmea_data) {
  uint8_t crc = 0;
  
  // Ignores the '$' at the beginning and calculates the checksum
  int i = 1;
  for (i = 1; nmea_data[i] != '*' && nmea_data[i] != '\0'; i++) {
    crc ^= (uint8_t)nmea_data[i];
  }

  // Gets the checksum value of the sentence after the '*' character
  if (nmea_data[i] != '*') {return false;}
  int checksum = strtol(&nmea_data[i + 1], NULL, 16);

  // Verifies if the calculated checksum matches the sentence checksum
  return crc == checksum;
} // --- END Verifies if the checksum of an NMEA0183 sentence is correct ---

// --- Sets GPS data with processed sentences ---
bool gpsSetData()
{
  // Verify if new GPS data is available
  if (!gps.isnew) {return false;}
  gps.isnew = false;

  String dat;
  float val;

  /// GGA Sequence-------------------------------------

  if (sentData[0] == "") {return false;}

  // Checks if it is fixed (6th position)
  dat = seqRetData(&sentData[0], 6);
  gps.fix =  dat.toInt();
  // Gets Latitude
  dat = seqRetData(&sentData[0], 2);
  val = dat.toFloat();
  dat = seqRetData(&sentData[0], 3);
  if(dat=="S") {val = val*(-1);}
  gps.lat = val*0.01;
  
  // Gets Longitude
  dat = seqRetData(&sentData[0], 4);
  val = dat.toFloat();
  dat = seqRetData(&sentData[0], 5);
  if(dat=="W") {val = val*(-1);}
  gps.lon = val*0.01;  
  
  // Gets Altitude
  dat = seqRetData(&sentData[0], 9);
  gps.alt = dat.toFloat();

  // Gets number of satellites
  dat = seqRetData(&sentData[0], 7);
  gps.sat = dat.toInt();

  // Gets HDOP
  dat = seqRetData(&sentData[0], 8);
  gps.hdop = dat.toFloat();

   // VTG Sequence-------------------------------------

  // Gets speed in km/h
  dat = seqRetData(&sentData[1], 7);
  gps.vel = dat.toFloat(); 

  // RMC Sequence-------------------------------------

  // Gets UTC time
  dat = seqRetData(&sentData[2], 1); 
  dat.toCharArray(gps.hor, sizeof(gps.hor));

   // Gets date
  dat = seqRetData(&sentData[2], 9);
  dat.toCharArray(gps.date, sizeof(gps.date));

  // Gets if it is fixed
  gps.isfix[0] = (seqRetData(&sentData[2], 2) == "A") ? 'S' : 'N';

  // Gets bearing (direction in degrees)
  dat = seqRetData(&sentData[2], 8);
  gps.bea = dat.toFloat();

  // Verifies if the coordinate is valid based on fix, HDOP, and number of satellites
  if (gps.isfix[0] == 'S' && gps.hdop <= 3 && gps.sat >= 4) {gps.isvalid = true;} else {gps.isvalid = false;}

  // Prints collected data
  Serial.println("------------------------------");
  Serial.print("Lat: ");
  Serial.print(gps.lat,6);
  Serial.print("    Lon: ");
  Serial.println(gps.lon,6);
  Serial.print("Alt: ");
  Serial.println(gps.alt,1);
  Serial.print("Fix: ");
  Serial.println(gps.fix);
  Serial.print("Sat: ");
  Serial.println(gps.sat);
  Serial.print("Hdop: ");
  Serial.println(gps.hdop);  
  Serial.print("isFix: ");
  Serial.println(gps.isfix);
  Serial.print("isValid: ");
  Serial.println(gps.isvalid ? 'S' : 'N');
  Serial.print("Bea: ");
  Serial.println(gps.bea);
  Serial.print("Vel: ");
  Serial.println(gps.vel);
  Serial.print("Hor: ");
  Serial.println(gps.hor);
  Serial.print("Date: ");
  Serial.println(gps.date);

  Serial.println("------------------------------");

  return true;  
} // --- END Sets GPS data with processed sentences ---

// --- Returns the isolated data from the sequence based on the requested position ---
String seqRetData(String *SEQ, uint8_t pos)
{
  String res = "", str = *SEQ;
  uint8_t i, ini = 0;
  uint8_t fim = str.length();

   // Counts the commas in the sequence until the desired position is found
  for (i = 0;i < pos;i++)
  {
    ini = str.indexOf(',', ini+1);
  }
  // Positioned, isolates the byte
  ini++; // Advances one position to get the data
  while (ini <= fim)
  {
    if (str[ini] == ',') {break;}
    res += str[ini];
    ini++;
  }
  return res;
} // --- END Returns the isolated data from the sequence based on the requested position ---

