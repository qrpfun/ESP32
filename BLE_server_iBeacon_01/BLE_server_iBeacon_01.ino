#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
//const BLEUUID MY_UUID = BLEUUID("09a8f6f0-9a2f-43b2-bd7c-e753622b57d4");
const BLEUUID MY_UUID = BLEUUID("26410a28-2a4c-4d57-ae2f-67a4d96b1f83");

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  BLEBeacon myBeacon;
  //myBeacon.setManufacturerId(uint16_t (0x1AFF));
  myBeacon.setManufacturerId(uint16_t (0x4C00));
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
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}
