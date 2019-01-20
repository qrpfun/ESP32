/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini       
    Usefull iBeacon reference: https://os.mbed.com/blog/entry/BLE-Beacons-URIBeacon-AltBeacons-iBeacon/
    
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEBeacon.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

const BLEUUID MY_UUID = BLEUUID("26410a28-2a4c-4d57-ae2f-67a4d96b1f83");

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEBeacon myBeacon;
    myBeacon.setManufacturerId(0x004c);
    myBeacon.setMajor(uint16_t (0x1234));
    myBeacon.setMinor(uint16_t (0x5678));
    myBeacon.setProximityUUID(MY_UUID);
    myBeacon.setSignalPower(uint8_t (0xC8));

    BLEAdvertisementData advertisementData;
    advertisementData.setFlags(ESP_BLE_ADV_FLAG_LIMIT_DISC | ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT);
    advertisementData.setManufacturerData(myBeacon.getData());

    BLEAdvertising* pAdvertising = pServer->getAdvertising();
    pAdvertising->setAdvertisementData(advertisementData);
    pAdvertising->setScanResponseData(advertisementData);
    pAdvertising->start();

    Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}
