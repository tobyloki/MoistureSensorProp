#include "Countimer.h"

const int cloudRelay = 11;
const int resetSoilRelay = 12;

Countimer tCloudOn;
Countimer tCloudOff;
Countimer tResetSoilOffset;
Countimer tResetSoilOn;
Countimer tResetSoilOff;

void setup()
{
	Serial.begin(9600);
  Serial.println("Started...");

  pinMode(cloudRelay, OUTPUT);
  pinMode(resetSoilRelay, OUTPUT);

  // digitalWrite(resetSoilRelay, HIGH);

  // run every 3 min
  tCloudOn.setCounter(0, 5, 0, tResetSoilOffset.COUNT_DOWN, turnOnCloud);
  tCloudOn.setInterval(tCloudOnCountdown, 1000);

  // run 1 min after triggered by tCloudOn
  tCloudOff.setCounter(0, 1, 0, tResetSoilOffset.COUNT_DOWN, turnOffCloud);
  tCloudOff.setInterval(tCloudOffCountdown, 1000);

  // run 1 min after program start
	tResetSoilOffset.setCounter(0, 1, 0, tResetSoilOffset.COUNT_DOWN, tResetSoilOffsetComplete);
	tResetSoilOffset.setInterval(tResetSoilOffsetCountdown, 1000);

  // run after triggered by tResetSoilOffset, and then every 3 min
	tResetSoilOn.setCounter(0, 1, 0, tResetSoilOffset.COUNT_DOWN, turnOnResetSoil);
	tResetSoilOn.setInterval(tResetSoilOnCountdown, 1000);

  // run 20 seconds after triggered by tResetSoilOn
  tResetSoilOff.setCounter(0, 0, 10, tResetSoilOffset.COUNT_DOWN, turnOffResetSoil);
  tResetSoilOff.setInterval(tResetSoilOffCountdown, 1000);

  tResetSoilOffset.restart();

  turnOnCloud();
}

void loop()
{
  tCloudOn.run();
  tCloudOff.run();
	tResetSoilOffset.run();
	tResetSoilOn.run();
  tResetSoilOff.run();
}

// tCloudOn
void tCloudOnCountdown()
{
	Serial.print("tCloudOn countdown: ");
	Serial.println(tCloudOn.getCurrentTime());
}

void turnOnCloud()
{
	Serial.println("Cloud turned on");
  digitalWrite(cloudRelay, HIGH);
  tCloudOn.restart();
  tCloudOff.restart();
}

// tCloudOff
void tCloudOffCountdown()
{
	Serial.print("tCloudOff countdown: ");
	Serial.println(tCloudOff.getCurrentTime());
}

void turnOffCloud()
{
	Serial.println("Cloud turned off");
  digitalWrite(cloudRelay, LOW);
}

// tResetSoilOffset
void tResetSoilOffsetCountdown()
{
	Serial.print("tResetSoilOffset countdown: ");
	Serial.println(tResetSoilOffset.getCurrentTime());
}

void tResetSoilOffsetComplete()
{
  Serial.println("tResetSoilOffset done. Started tResetSoilOn...");
  turnOnResetSoil();
}

// tResetSoilOn
void tResetSoilOnCountdown()
{
	Serial.print("tResetSoilOn countdown: ");
	Serial.println(tResetSoilOn.getCurrentTime());
}

void turnOnResetSoil()
{
	Serial.println("Reset soil turned on");
  digitalWrite(resetSoilRelay, HIGH);
  tResetSoilOn.restart();
  tResetSoilOff.restart();
}

// tResetSoilOff
void tResetSoilOffCountdown()
{   
	Serial.print("tResetSoilOff countdown: ");
	Serial.println(tResetSoilOff.getCurrentTime());
}

void turnOffResetSoil()
{
	Serial.println("Reset soil turned off");
  digitalWrite(resetSoilRelay, LOW);
}



