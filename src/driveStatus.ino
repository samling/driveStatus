#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

#define INPUT_SIZE 500

char drive1_used_buffer[10] = "";
char drive1_total_buffer[10] = "";
char drive1_concat_buffer[20] = "";

char drive2_used_buffer[10] = "";
char drive2_total_buffer[10] = "";
char drive2_concat_buffer[20] = "";

char drive3_used_buffer[10] = "";
char drive3_total_buffer[10] = "";
char drive3_concat_buffer[20] = "";

char* network;
char* ip_addr;

char* drive1;
char* drive1_device;
char* drive1_mnt;
char* drive1_size_str;
float drive1_size;
char* drive1_used_str;
float drive1_used;
char* drive1_available;
char* drive1_pct_str;
float drive1_pct;

char* drive2;
char* drive2_device;
char* drive2_mnt;
char* drive2_size_str;
float drive2_size;
char* drive2_used_str;
float drive2_used;
char* drive2_available;
char* drive2_pct_str;
float drive2_pct;

char* drive3;
char* drive3_device;
char* drive3_mnt;
char* drive3_size_str;
float drive3_size;
char* drive3_used_str;
float drive3_used;
char* drive3_available;
char* drive3_pct_str;
float drive3_pct;

void setup()
{
	Serial.begin(115200);
	TFT_BL_ON;
	Tft.TFTinit();
	Tft.setDisplayDirect(DOWN2UP);
}

void loop()
{
	while (Serial.available()) {
		char input[INPUT_SIZE + 1];
		byte size = Serial.readBytes(input, INPUT_SIZE);
		input[size] = 0;

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

		delay(10);
		ip_addr = strtok(network, ":");

		delay(10);
		Tft.fillScreen();
	}

	if (drive1 != NULL) {
		Tft.drawString(drive1_mnt, 10, 310, 2, WHITE);
		Tft.drawRectangle(30,10,5,300,WHITE);
		Tft.fillRectangle(31,309,4,200.00*drive1_pct,GREEN);
		sprintf(drive1_concat_buffer, "%s / %s", drive1_used_buffer, drive1_total_buffer);
		Tft.drawString(drive1_concat_buffer, 45, 310, 2, WHITE);
	}
	if (drive2 != NULL) {
		Tft.drawString(drive2_mnt, 90, 310, 2, WHITE);
		Tft.drawRectangle(110,10,5,300,WHITE);
		Tft.fillRectangle(111,309,4,200.00*drive2_pct,GREEN);
		sprintf(drive2_concat_buffer, "%s / %s", drive2_used_buffer, drive2_total_buffer);
		Tft.drawString(drive2_concat_buffer, 125, 310, 2, WHITE);
	}
	if (drive3 != NULL) {
		Tft.drawString(drive3_mnt, 170, 310, 2, WHITE);
		Tft.drawRectangle(190,10,5,300,WHITE);
		Tft.fillRectangle(191,309,4,200.00*drive3_pct,GREEN);
		sprintf(drive3_concat_buffer, "%s / %s", drive3_used_buffer, drive3_total_buffer);
		Tft.drawString(drive3_concat_buffer, 205, 310, 2, WHITE);
	}
	if (ip_addr != NULL) {
		//Tft.drawString(ip_addr, 10, 300, 2, WHITE);
	}
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
