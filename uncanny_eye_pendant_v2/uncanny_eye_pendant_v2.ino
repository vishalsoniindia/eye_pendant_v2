/*
   The Code is Written By Vishal Soni (Youtube: ElectroDonut)
   esp32 Board Version: 3.3.0
   TFT_espi Version : 2.5.43
*/

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

#include "images/eye_v2.h"
#include "images/intro.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();                   // Create an instance of TFT_eSPI
TFT_eSprite gif_sprite = TFT_eSprite(&tft);  // Sprite object for displaying frames

uint8_t frame_delay = 100;  //frame delay in milliseconds

void setup() {
  tft.begin();
  tft.setRotation(0);         // Set the display rotation
  tft.fillScreen(TFT_WHITE);  // Clear the screen

  Serial.begin(115200);
  Serial.println("### SETUP ###");

  // Initialize the sprite
  gif_sprite.createSprite(240, 240);
  gif_sprite.setSwapBytes(true);  // Ensure byte order matches the format

  //play intro on every wake
  playGif(intro_allArray, intro_allArray_LEN, frame_delay);
}

void loop() {
  playGif(eye_allArray, eye_allArray_LEN, frame_delay);  // Play the GIF
}

//______________________________ FUNCTIONS _________________________________________

void playGif(const uint16_t* frames[], int numFrames, uint8_t frameDelay) {
  for (int i = 0; i < numFrames; i++) {
    // Clear the sprite (optional, but can prevent artifacts)
    gif_sprite.fillSprite(TFT_BLACK);

    // Push the current frame to the sprite
    gif_sprite.pushImage(0, 0, 240, 240, frames[i]);

    // Push the sprite to the display
    gif_sprite.pushSprite(0, 0);

    // Delay to control the animation speed
    delay(frameDelay);
  }
}


