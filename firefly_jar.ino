#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>

#define THRESHOLD 100
#define LOWTHRESH  20

#define NUM_LEDS 32
#define DATA_PIN 2

int cap_out = 1;
int cap_in = 0;

CapacitiveSensor capsense = CapacitiveSensor(cap_out, cap_in); 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

bool enabled = false;
bool hysteresis = false;

void setup() {
  pinMode(cap_in, INPUT);
  pinMode(cap_out, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int readIn = capsense.capacitiveSensor(10);
  if(readIn > THRESHOLD && !hysteresis)
  {
    enabled = !enabled;
    hysteresis = true;
  }
  else if(readIn < LOWTHRESH)
  {
    hysteresis = false;
  }
  
  if(enabled)
  {
    cycleFireFly();
  }
}

#define NUMFLIES 10

struct ffly
{
  float pos;
  uint8_t peak;
  uint8_t dir;
  uint8_t life;
};

ffly fireflies[NUMFLIES];

uint8_t leds[NUM_LEDS] = {0};

void cycleFireFly()
{
  spawnFlies(); //randomly add new fireflies
  
  for(int i = 0; i < sizeof(fireflies); i ++)
  {
  }
}

void spawnFlies()
{
  if(random(20) == 10) //5% chance
  {
    for(int i = 0; i < sizeof(fireflies); i ++)
    {
      if(fireflies[i].life == 0)
      {
        fireflies[i].life = random(2,5);
        fireflies[i].peak = fireflies[i].life/2;
        fireflies[i].pos = random(1, NUM_LEDS);
        fireflies[i].dir = random(0,2);
      }
    }
  }
}
