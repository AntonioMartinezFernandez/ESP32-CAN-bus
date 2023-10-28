#include <Arduino.h>
#include <CAN.h>
#include <CAN-test.h>

#define TX_GPIO_NUM 15 // Connects to CAN module CTX pin
#define RX_GPIO_NUM 14 // Connects to CAN module CRX pin

//! Stablish CAN functionalities
const bool SENDER_ENABLED = true;
const bool RECEIVER_ENABLED = true;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(1000);

  // Set pinout
  CAN.setPins(RX_GPIO_NUM, TX_GPIO_NUM);

  // Start CAN bus at 500kbps
  if (!CAN.begin(500E3))
  {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }
  else
  {
    Serial.println("CAN Initialized");
  }

  if (RECEIVER_ENABLED)
  {
    // Register the receive callback
    CAN.onReceive(onReceiveCallback);
  }
}

void loop()
{
  if (SENDER_ENABLED)
  {
    sender();
    delay(2500);
  }
}
