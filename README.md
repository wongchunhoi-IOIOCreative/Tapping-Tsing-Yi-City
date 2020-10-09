# tapping_TeensyCode_20200709_TsingYiCity
Tapping for Tsing Yi City

---

## Audio  Sample Playback 
### wav2sketch 
Notes

[Step by step instructions](https://forum.pjrc.com/threads/42401-Instructions-or-tutorials-for-using-wav2sketch?p=135069&viewfull=1#post135069) for wav2sketch running in Terminal on Macintosh.

[Old documentation](https://www.pjrc.com/teensy/td_libs_AudioPlayMemory.html) about wav2sketch is still available, including details about the data format.

[PJRC - Audio Play Memory](https://www.pjrc.com/teensy/td_libs_AudioPlayMemory.html)

[download the tool](https://github.com/PaulStoffregen/Audio/tree/master/extras/wav2sketch)

after it is converted to sketch file, each sample will contain a .cpp  and a .h file 
AudioSampleNewwindchime1

AudioSampleNewwindchime3

AudioSampleNewwindchime5

AudioSampleNewwindchime7


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

## LED Color [hardcode]

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

AudioSampleAteststring1 
