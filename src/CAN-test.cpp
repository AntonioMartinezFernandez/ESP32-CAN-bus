#include <CAN.h>

void sender()
{
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet...");

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();

  Serial.println("done");

  delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet...");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("done");
}

void onReceiveCallback(int packetSize)
{
  // Received a packet
  Serial.print("Received ");

  if (CAN.packetExtended())
  {
    Serial.print("extended ");
  }

  if (CAN.packetRtr())
  {
    // Remote Transmission Request, packet contains no data
    Serial.print("RTR ");
  }

  Serial.print("Packet with id 0x");
  Serial.print(CAN.packetId(), HEX);

  if (CAN.packetRtr())
  {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  }
  else
  {
    Serial.print(" and length ");
    Serial.println(packetSize);

    // Only print packet data for non-RTR packets
    while (CAN.available())
    {
      Serial.print((char)CAN.read());
    }
    Serial.println();
  }

  Serial.println();
}