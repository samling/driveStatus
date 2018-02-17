#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

#define INPUT_SIZE 300

char drive1_used_buffer[10] = "";
char drive1_total_buffer[10] = "";
char drive2_used_buffer[10] = "";
char drive2_total_buffer[10] = "";
char drive3_used_buffer[10] = "";
char drive3_total_buffer[10] = "";
char* network;
char* ip_addr;
char* drive1;
char* drive2;
char* drive3;
char* drive1_device;
char* drive2_device;
char* drive3_device;
char* drive1_mnt;
char* drive2_mnt;
char* drive3_mnt;
char* drive1_size_str;
char* drive2_size_str;
char* drive3_size_str;
float drive1_size;
float drive2_size;
float drive3_size;
char* drive1_used_str;
char* drive2_used_str;
char* drive3_used_str;
float drive1_used;
float drive2_used;
float drive3_used;
char* drive1_available;
char* drive2_available;
char* drive3_available;
char* drive1_pct_str;
char* drive2_pct_str;
char* drive3_pct_str;
float drive1_pct;
float drive2_pct;
float drive3_pct;

void setup()
{
	Serial.begin(9600);
	TFT_BL_ON;
	Tft.TFTinit();
}

void loop()
{
	while (Serial.available()) {
		char input[INPUT_SIZE + 1];
		byte size = Serial.readBytes(input, INPUT_SIZE);
		input[size] = 0;

		Serial.print("Total input is: ");
		Serial.print(input);
		Serial.println("\n");

		drive1 = strtok(input, "&");
		drive2 = strtok(NULL, "&");
		drive3 = strtok(NULL, "&");
		network = strtok(NULL, "&");

		delay(10);
		drive1_device = strtok(drive1, ":");
		drive1_mnt = strtok(NULL, ":");
		drive1_size_str = strtok(NULL, ":");
		drive1_size = atol(drive1_size_str)/1000000.00;
		drive1_used_str = strtok(NULL, ":");
		drive1_used = atol(drive1_used_str)/1000000.00;
		dtostrf(drive1_used, 0, 2, drive1_used_buffer);
		dtostrf(drive1_size, 0, 2, drive1_total_buffer);
		drive1_available = strtok(NULL, ":");
		drive1_pct_str = strtok(NULL, ":");
		drive1_pct_str[strlen(drive1_pct_str)-1] = 0;
		drive1_pct = atol(drive1_pct_str)/100.00;

		Serial.print("Device name for drive 1: ");
		Serial.print(drive1_device);
		Serial.println("\n");
		Serial.print("Mount point for drive 1: ");
		Serial.print(drive1_mnt);
		Serial.println("\n");
		Serial.print("Size of drive 1: ");
		Serial.print(drive1_size);
		Serial.println("\n");
		Serial.print("Used on drive 1: ");
		Serial.print(drive1_used);
		Serial.println("\n");
		Serial.print("Free on drive 1: ");
		Serial.print(drive1_available);
		Serial.println("\n");
		Serial.print("Percent used on drive 1: ");
		Serial.print(drive1_pct);
		Serial.println("\n");

		delay(10);
		drive2_device = strtok(drive2, ":");
		drive2_mnt = strtok(NULL, ":");
		drive2_size_str = strtok(NULL, ":");
		drive2_size = atol(drive2_size_str)/1000000.00;
		drive2_used_str = strtok(NULL, ":");
		drive2_used = atol(drive2_used_str)/1000000.00;
		dtostrf(drive2_used, 0, 2, drive2_used_buffer);
		dtostrf(drive2_size, 0, 2, drive2_total_buffer);
		drive2_available = strtok(NULL, ":");
		drive2_pct_str = strtok(NULL, ":");
		drive2_pct_str[strlen(drive2_pct_str)-1] = 0;
		drive2_pct = atol(drive2_pct_str)/100.00;

		Serial.print("Device name for drive 2: ");
		Serial.print(drive2_device);
		Serial.println("\n");
		Serial.print("Mount point for drive 2: ");
		Serial.print(drive2_mnt);
		Serial.println("\n");
		Serial.print("Size of drive 2: ");
		Serial.print(drive2_size);
		Serial.println("\n");
		Serial.print("Used on drive 2: ");
		Serial.print(drive2_used);
		Serial.println("\n");
		Serial.print("Free on drive 2: ");
		Serial.print(drive2_available);
		Serial.println("\n");
		Serial.print("Percent used on drive 2: ");
		Serial.print(drive2_pct);
		Serial.println("\n");

		delay(10);
		drive3_device = strtok(drive3, ":");
		drive3_mnt = strtok(NULL, ":");
		drive3_size_str = strtok(NULL, ":");
		drive3_size = atol(drive3_size_str)/1000000.00;
		drive3_used_str = strtok(NULL, ":");
		drive3_used = atol(drive3_used_str)/1000000.00;
		dtostrf(drive3_used, 0, 2, drive3_used_buffer);
		dtostrf(drive3_size, 0, 2, drive3_total_buffer);
		drive3_available = strtok(NULL, ":");
		drive3_pct_str = strtok(NULL, ":");
		drive3_pct_str[strlen(drive3_pct_str)-1] = 0;
		drive3_pct = atol(drive3_pct_str)/100.00;

		Serial.print("Device name for drive 3: ");
		Serial.print(drive3_device);
		Serial.println("\n");
		Serial.print("Mount point for drive 3: ");
		Serial.print(drive3_mnt);
		Serial.println("\n");
		Serial.print("Size of drive 3: ");
		Serial.print(drive3_size);
		Serial.println("\n");
		Serial.print("Used on drive 3: ");
		Serial.print(drive3_used);
		Serial.println("\n");
		Serial.print("Free on drive 3: ");
		Serial.print(drive3_available);
		Serial.println("\n");
		Serial.print("Percent used on drive 3: ");
		Serial.print(drive3_pct);
		Serial.println("\n");

		delay(10);
		ip_addr = strtok(network, ":");
		Serial.print("IP address: ");
		Serial.print(ip_addr);
		Serial.println("\n");

		delay(10);
		Tft.fillScreen();
	}

	if (drive1 != NULL) {
		Tft.drawString(drive1_mnt, 10, 10, 2, WHITE);
		Tft.drawRectangle(10,30,200,20,WHITE);
		Tft.fillRectangle(11,31,200.00*drive1_pct,19,GREEN);
		Tft.drawString(drive1_used_buffer, 10, 50, 2, WHITE);
		Tft.drawString("/", sizeof(drive1_used_buffer)*20, 50, 2, WHITE);
	}
	if (drive2 != NULL) {
		Tft.drawString(drive2_mnt, 10, 70, 2, WHITE);
		Tft.drawRectangle(10,90,200,20,WHITE);
		Tft.fillRectangle(11,91,200.00*drive2_pct,19,GREEN);
		Tft.drawString(drive2_used_buffer, 10, 110, 2, WHITE);
	}
	if (drive3 != NULL) {
		Tft.drawString(drive3_mnt, 10, 130, 2, WHITE);
		Tft.drawRectangle(10,150,200,20,WHITE);
		Tft.fillRectangle(11,151,200.00*drive3_pct,19,GREEN);
		Tft.drawString(drive3_used_buffer, 10, 170, 2, WHITE);
	}
	if (ip_addr != NULL) {
		Tft.drawString(ip_addr, 10, 300, 2, WHITE);
	}
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
