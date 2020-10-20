# tapping_TeensyCode_TsingYiCity
 Tapping for Tsing Yi City

updated 2020-10-20

---
## quick Change Sound part 
``` cpp
float baseVol = 0.2;
boolean noiseEnable = false;
float noiseAmp = 0.5;
boolean blipEnable =  false;
boolean toneEnable = false;
boolean samplePlayerMode = false;  //<-  using
bool FmSynth = false;   //<-Using;  
bool RingModSynth = true;    // <-- Using
int tone1 = 659 ;   //739
int tone2 = 880;    //932
int tone3 = 0;
float tone1Amp = 0.05;
float tone2Amp = 0.05;
float tone3Amp = 0.2;
```
# Volumen Adjustment
## Base Volume
``` cpp
float baseVol = 0.2;

```

## Volume modulated by Intensity
  ``` cpp
  vol = baseVol + floatMap(intensity, 0, intensityThreshold, 0.0, 1 - baseVol);
  ```
  
  
### Sample Playing Mode Volume
``` cpp
float SamplePlayingVol = 0.2; //Sample Playing Mode Volume
```

### FM synth mode volume
``` cpp
...
...
mixer2.gain(0, 1);  //<---mixer 2 (channel 0 , gain (0.0 -1.0)

```

### RM synth mode volume
``` cpp
...
...
  mixer2.gain(1, 1);  // <--mixer 2 (channel 0 , gain (0.0 -1.0)

```

### Boost the AMP with external reference voltage
``` cpp
dac1.analogReference(INTERNAL); // much louder Volume ! if external

```


## Audio  Sample Playback 
### wav2sketch 
Notes

[Step by step instructions](https://forum.pjrc.com/threads/42401-Instructions-or-tutorials-for-using-wav2sketch?p=135069&viewfull=1#post135069) for wav2sketch running in Terminal on Macintosh.

[Old documentation](https://www.pjrc.com/teensy/td_libs_AudioPlayMemory.html) about wav2sketch is still available, including details about the data format.

[PJRC - Audio Play Memory](https://www.pjrc.com/teensy/td_libs_AudioPlayMemory.html)

[download the tool](https://github.com/PaulStoffregen/Audio/tree/master/extras/wav2sketch)

after it is converted to sketch file, each sample will contain a .cpp  and a .h file 
AudioSampleShimmer
AudioSampleShimmer4


## on the code

``` cpp
  // Sample playing 
  // --- Filter of the sampler ----
  filter2.frequency(8600);    
  filter2.resonance(4.7);
  int retriggerTime = 700;

  if (samplePlayerMode == true) {
   // mixer1.gain(3, vol);
    //trigger the sample if swing
     if (playMem1.isPlaying() == false) { 
      
        if (intensity >= sampleTriThreshold) { 
          playMem1.play(AudioSampleNewwindchime1);  
          mixer1.gain(3, 1);
          AudioInterrupts();

        }
     } else if (playMem1.isPlaying() == true) {
         if ( (intensity >= sampleTriThreshold ) && (playMem1.positionMillis() >retriggerTime) ) { 
               mixer1.gain(3, 1);
               playMem1.play(AudioSampleNewwindchime1);
//            count++;
//            if (count % 2 == 0 )  { 
//               playMem1.play(AudioSampleNewwindchime3);
//            delay(10);
//            } else { 
//              playMem1.play(AudioSampleNewwindchime1);
//            }

         }
     }    
  }
---
```




# LED Color [hardcode]
## [CONFIRMED.  Purple to blue

``` cpp
 /* === *** Confirmed Tsing Yi City Color    Purple to Blue  *** === */

  
    blueLEDVal = random(200, 240) + lightPow / 255 * 60;
    if (blueLEDVal >= 254) {
      blueLEDVal = 254;
    }

    GreenLEDVal = random(5, 10); // + lightPow / 255 * 100;
    if (GreenLEDVal >= 254) {
      GreenLEDVal = 254;
    }

    for (int n = 0; n < NUM_LEDS; n++) {
      leds[n].red =  random(190, 250) - lightPow / 255 * 200;
      leds[n].green = GreenLEDVal;
      leds[n].blue = blueLEDVal;
    }
    
    
```
---
----
------ Archive

### Amber (Test on 2020-07-09)
``` cpp
 for (int n = 0; n < NUM_LEDS; n++) {
      leds[n].red = random(10, 80) + 170;
      leds[n].green = 30;
      leds[n].blue = 0;
```
### Green / Blue 
``` cpp
/* original tapping green / blue */ 
    int blueLEDVal;
    int GreenLEDVal;

    blueLEDVal = 50 + lightPow;
    if (blueLEDVal >= 254) { 
      blueLEDVal=254;
    }
    
    GreenLEDVal = random(50, 80) + lightPow;
    if (GreenLEDVal >= 254) { 
      GreenLEDVal=254;
    }

   if (n%2 == 0 ) { 
     leds[n].red = lightPow*0.1;
     leds[n].green = GreenLEDVal;
     leds[n].blue = lightPow*0.1;
   } else {
     leds[n].red = lightPow*0.1;
     leds[n].green = lightPow*0.1;
     leds[n].blue = blueLEDVal;
   }
   ```


