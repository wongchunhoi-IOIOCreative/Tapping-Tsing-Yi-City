 //#define FASTLED_ALLOW_INTERRUPTS 0

#include <EEPROM.h>
//#include "FastLED.h"
#include <FastLED.h>
#include <NXPMotionSense.h>
#include <Wire.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//Audio Sample coverted file
// to change your file name here:
//#include "AudioSampleAteststring1.h"
//#include "AudioSampleS16bitmonow.h"
//#include "AudioSampleS50p16bit2w.h"
//#include "AudioSampleS11025wa.h"
//#include "AudioSampleWindhime.h"
//#include "AudioSampleWindhimel.h"
//#include "AudioSampleNewwindchime7.h"
//#include "AudioSampleNewwindchime1.h"
//#include "AudioSampleNewwindchime5.h"
//#include "AudioSampleNewwindchime3.h"

#include "AudioSampleShimmer.h"
#include "AudioSampleShimmer4.h"




//prop shield Amplifier
#define PROP_AMP_ENABLE    5
//#define FLASH_CHIP_SELECT  6


unsigned int address = 0;
byte mode;
String TIME;
boolean iniStatus = false;
int frame = 0;
//================= LIGHT ========================
// How many leds in your strip?
#define NUM_LEDS 4

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
//#define CLOCK_PIN 13
//elapsedMillis Timer;
// Define the array of leds
boolean LightSwitchMode = false;
CRGB leds[NUM_LEDS];
float lightPow;
int lightBrightness;
//boolean red = false;

//================= Audio ========================

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=146,187
AudioSynthWaveform       waveform3;      //xy=148,234
AudioSynthWaveform       waveform1;      //xy=151,129
AudioSynthNoiseWhite     noise1;         //xy=156,457
AudioSynthWaveformSine   sine1;          //xy=160,345
AudioSynthWaveformSine   sine2;          //xy=161,408
AudioPlayMemory          playMem1;       //xy=197,523
AudioSynthWaveformSineModulated sine_fm1;       //xy=307,127
AudioEffectMultiply      multiply1;      //xy=328,201
AudioSynthWaveform       waveform5;      //xy=338,308
AudioSynthWaveform       waveform4;      //xy=341,258
AudioFilterStateVariable filter2;        //xy=375,516
AudioFilterStateVariable filter1;        //xy=377,438
AudioFilterStateVariable filter3;        //xy=459,124
AudioFilterStateVariable filter5;        //xy=485,301
AudioFilterStateVariable filter4;        //xy=492,219
AudioMixer4              mixer1;         //xy=600,403
AudioEffectEnvelope      envelope1;      //xy=627,122
AudioMixer4              mixer4;         //xy=635,224
AudioEffectEnvelope      envelope2;      //xy=774,220
AudioMixer4              mixer3;         //xy=805,345
AudioMixer4              mixer2;         //xy=940,206
AudioEffectReverb        reverb1;        //xy=1043,431
AudioMixer4              MasterMixer;         //xy=1198,347
AudioOutputAnalog        dac1;           //xy=1369,347
AudioConnection          patchCord1(waveform2, 0, multiply1, 0);
AudioConnection          patchCord2(waveform3, 0, multiply1, 1);
AudioConnection          patchCord3(waveform1, sine_fm1);
AudioConnection          patchCord4(noise1, 0, filter1, 0);
AudioConnection          patchCord5(sine1, 0, mixer1, 0);
AudioConnection          patchCord6(sine2, 0, mixer1, 1);
AudioConnection          patchCord7(playMem1, 0, filter2, 0);
AudioConnection          patchCord8(sine_fm1, 0, filter3, 0);
AudioConnection          patchCord9(multiply1, 0, filter4, 0);
AudioConnection          patchCord10(waveform5, 0, filter5, 0);
AudioConnection          patchCord11(waveform4, 0, filter4, 1);
AudioConnection          patchCord12(filter2, 0, mixer1, 3);
AudioConnection          patchCord13(filter1, 0, mixer1, 2);
AudioConnection          patchCord14(filter3, 0, envelope1, 0);
AudioConnection          patchCord15(filter5, 0, mixer4, 1);
AudioConnection          patchCord16(filter4, 0, mixer4, 0);    //ring mod synth's low pass (0) , band pass(1) , high pass)
AudioConnection          patchCord17(mixer1, 0, mixer3, 1);
AudioConnection          patchCord18(envelope1, 0, mixer2, 0);
AudioConnection          patchCord19(mixer4, envelope2);
AudioConnection          patchCord20(envelope2, 0, mixer2, 1);
AudioConnection          patchCord21(mixer3, reverb1);
AudioConnection          patchCord22(mixer3, 0, MasterMixer, 0);
AudioConnection          patchCord23(mixer2, 0, mixer3, 0);
AudioConnection          patchCord24(reverb1, 0, MasterMixer, 1);
AudioConnection          patchCord25(MasterMixer, dac1);
// GUItool: end automatically generated code






//synth part
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

//sampling playing
bool SamplePlaying = false;  


// FM synth EDITING

int toneFMMod;
int toneFMSine;

// EFFECT
//  1 flanger
//#define FLANGE_DELAY_LENGTH (12*AUDIO_BLOCK_SAMPLES)
//short l_delayline[FLANGE_DELAY_LENGTH];
//int s_idx = 3*FLANGE_DELAY_LENGTH/4;
//int s_depth = FLANGE_DELAY_LENGTH/8;
//double s_freq = .0625;

//  2 Reverb
float reverbRoomSize = 0.1 ;
float reverbDamping = 0.1;

/* === EFFECT FLANGER end ===*/

int count = 0 ;
int VolumeKnob;
int sampleTriThreshold = 10;



/*

  int tone1 = 931;
  int tone2 = 932;
  int tone3 = 933;

  float tone1Amp = 0.9;
  float tone2Amp = 0.9;
  float tone3Amp = 0.9;
*/

//369.99 466.16 622.25 554.37 739.99 830.61 932.33



//================ Motion ========================
NXPMotionSense imu;
NXPSensorFusion filter;

int intensityThreshold = 30;
boolean smoothEnable = true;
const int numSmooth = 5;
float smooth[numSmooth];
int datIndex = 0;
int total = 0;
float average = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial.begin(9600);


  //---- light swtich mode ------  (comment if always ON)
  if (LightSwitchMode) {

    mode = EEPROM.read(address);
    if (mode == 1) {
      TIME = "lightOn";
      EEPROM.write(address, 0);
    } else if (mode != 1) {
      TIME = "lightOff";
      EEPROM.write(address, 1);
    }

  } else {
    TIME = "lightOn" ;
  }
  /*---end of light set up--*/




  //intitialize smooth
  for (int thisDat = 0; thisDat < numSmooth; thisDat++) {
    smooth[thisDat] = 0;
  }

  // Initialize IMU and filter
  imu.begin();
  filter.begin(100);

  //initialize LED
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,13, RGB>(leds, NUM_LEDS);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);  // enable access to LEDs

  // Turn on amp
  AudioMemory(20);
  dac1.analogReference(EXTERNAL); // much louder! if external
  delay(50);             // time for DAC voltage stable
  pinMode(PROP_AMP_ENABLE, OUTPUT);
  digitalWrite(PROP_AMP_ENABLE, HIGH); // turn on the amplifier
  delay(10);             // allow time to wake up

  //initiatizing Audio effect rack
  //flange1.begin(l_delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  //      freeverb1.roomsize(reverbRoomSize);
  //      freeverb1.damping(reverbDamping);
  reverb1.reverbTime(0.1);




  delay(2000);      // sanity check delay



//audio master volume

MasterMixer.gain(0,1);
MasterMixer.gain(1,0);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (iniStatus == false) {
    // Serial.println(TIME);
    //========light check===========
    if (TIME == "lightOff") {
      for (int n = 0; n < NUM_LEDS; n++) {

        leds[n].red = 0;
        leds[n].green = 0;
        leds[n].blue = 0;

        FastLED.show();
        delay(100);
      }
    }
    //=============end=============
    iniStatus = true;
  }

  //================= Volume knob ==================
  //  VolumeKnob = analogRead(11);
  // Serial.print("volume knob is: ");
  //Serial.println(VolumeKnob);

  //================= MOTION =======================
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch;
  uint8_t hue, val;
  long freq;
  float vol;
  float intensity;
  // Read motion sensors and filter the results

  imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);
  filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
  //  roll = filter.getRoll();
  //  pitch = filter.getPitch();
  //Serial.println("pingping");
  /*

    Serial.print("roll:");
    Serial.println(roll);

    Serial.print("pitch:");
    Serial.println(pitch);
  */
  intensity = sqrt(sq(sqrt(sq(gx) + sq(gy))) + sq(gz));

  if (smoothEnable == true) {
    total = total - smooth[datIndex];
    smooth[datIndex] = intensity;
    total = total + smooth[datIndex];
    datIndex = datIndex + 1;

    if (datIndex >= numSmooth) {
      datIndex = 0;
    }

    average = total / numSmooth;
    intensity = average;
  }
  if (intensity < 0) {
    intensity = 0;
  }

  //================= LIGHT ========================
  if (TIME == "lightOn") {
    lightPow = floatMap(intensity, 0, intensityThreshold, 0, 255);
    Serial.print("lightPwe: " );
    Serial.print(lightPow);

    int blueLEDVal;
    int GreenLEDVal;

    /*  ===LED Set 1:  near Cyan == */
    /*
        blueLEDVal = random(140,150) + lightPow*0.8;
        if (blueLEDVal >= 254) {
          blueLEDVal=254;
        }

        GreenLEDVal = random(140, 145) + lightPow*0.7;
        if (GreenLEDVal >= 254) {
          GreenLEDVal=254;
        }


        for (int n = 0; n < NUM_LEDS; n++) {
            leds[n].red = random(30,55);
          leds[n].green = GreenLEDVal;
          leds[n].blue = blueLEDVal;
        }
    */
    /* ==== LED Set 1 END ==== */


    /*  ===LED Set 2:  Bo Blue == */
    /*
      blueLEDVal = random(100,111)+lightPow;
        if (blueLEDVal >= 254) {
          blueLEDVal=254;
        }

        GreenLEDVal = random(30, 40) + lightPow*0.4;
        if (GreenLEDVal >= 254) {
          GreenLEDVal=254;
        }


        for (int n = 0; n < NUM_LEDS; n++) {
            leds[n].red = 0;
          leds[n].green = GreenLEDVal;
          leds[n].blue = blueLEDVal;
        }

    */
    /* ==== END LED Set 2 Bo Blue  END ==== */


    /* === LED from Set 1 change to Set 2 === */
    /*
        blueLEDVal = random(140,160) - lightPow/255 * 40;
        if (blueLEDVal >= 254) {
          blueLEDVal=254;
        }

        GreenLEDVal = random(140, 145) -lightPow/255 * 100;
        if (GreenLEDVal >= 254) {
          GreenLEDVal=254;
        }


        for (int n = 0; n < NUM_LEDS; n++) {
          leds[n].red =  random(0,30);;//55-lightPow/255*30;
          leds[n].green = GreenLEDVal;
          leds[n].blue = blueLEDVal;
        }
    */
    /* ===END Led from set 1 to set 2 === */


    /* === LED from Set 2 change to Set 1 === */

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



    /* ===END Led from set2 to set 1 === */


    /* ======OLD LED PATCH =====*/

    /* original tapping green / blue */
    //    if (n%2 == 0 ) {
    //      leds[n].red = lightPow*0.1;
    //      leds[n].green = GreenLEDVal;
    //      leds[n].blue = lightPow*0.1;
    //    } else {
    //      leds[n].red = lightPow*0.1;
    //      leds[n].green = lightPow*0.1;
    //      leds[n].blue = blueLEDVal;
    //    }
    //   }



    /* All white*/
    /*
          leds[n].red = 254 ;
          leds[n].green = 254;
          leds[n].blue = 254;
    */

    /*morphing white light */
    /*
        leds[n].red = 255;
        leds[n].green = 160 + random (0,80);
        leds[n].blue = 200;
        //Serial.println(intensity);

        //leds[n]
        lightBrightness = 255-lightPow;
        if (lightBrightness<=0) {
          lightBrightness = 0;
        }
    */

    lightBrightness = 250;
    FastLED.setBrightness(lightBrightness);
    FastLED.show();
    //delay(10);


  }
  //================= Audio ========================


  freq = floatMap(intensity, 0, intensityThreshold, 932, 422);  //622

  vol = baseVol + floatMap(intensity, 0, intensityThreshold, 0.0, 1 - baseVol);

  if (vol > 1) {
    vol = 1;
  }
  // Set frequency and volume for sound
  vol = sin(vol * PI / 2);
  //vol = log(vol)/4 + 1;
  if (vol <= 0) {
    vol = 0;
  }

  //Serial.println(intensity);
  // Serial.print(frame);
  Serial.print("intensity : ");
  Serial.print(intensity);
  Serial.print(" , Vol : ");
  Serial.println(vol);
  // frame++;
  if (toneEnable == true) {
    mixer1.gain(0, vol);
    mixer1.gain(1, vol);
    //mixer1.gain(2, vol);
    sine1.frequency(tone1 + intensity / 255 * 400);
    sine1.amplitude(tone1Amp);
    sine2.frequency(tone2);
    sine2.amplitude(tone2Amp);
    //sine3.frequency(tone3);
    //sine3.amplitude(tone3Amp);
  }
  if (blipEnable == true) {
    mixer1.gain(0, vol * 0.1);
    mixer1.gain(1, vol * 0.1);
    //mixer1.gain(0, vol*0.7 );
    //mixer1.gain(1, vol *0.7);
    //mixer1.gain(2, vol * 0.3);
    sine1.frequency(freq);
    sine1.amplitude(0.5);
    sine2.frequency(freq + intensity * 0.7);
    sine2.amplitude(0.3);
    //  sine3.frequency(freq - intensity * 0.3);
    //sine3.amplitude(1);
  }

  if (noiseEnable == true) {
    mixer1.gain(2, vol);
    filter1.frequency(7000 + intensity * 50);
    filter1.resonance(0.7);
    //filter1.frequency(20000);
    noise1.amplitude(noiseAmp);
  }

  // Sample playing
  filter2.frequency(800);
  filter2.resonance(1.0);
  int retriggerTime = 1500;

  if (samplePlayerMode == true) {
    // mixer1.gain(3, vol);

    //trigger the sample if swing
    if (playMem1.isPlaying() == false) {

      if (intensity >= sampleTriThreshold) {
        playMem1.play(AudioSampleShimmer);  //AudioSampleAteststring1 . AudioSampleS11025wa
        mixer1.gain(3, 0.2);    //0.3
        AudioInterrupts();

      }
    } else if (playMem1.isPlaying() == true) {
      if ( (intensity >= sampleTriThreshold ) && (playMem1.positionMillis() > retriggerTime) ) {
        mixer1.gain(3, 0.2);   //0.3
        playMem1.play(AudioSampleShimmer4);
        //            count++;

        //            if (count % 2 == 0 )  {
        //               playMem1.play(AudioSampleNewwindchime3);
        //            delay(10);
        //            } else {
        //              playMem1.play(AudioSampleNewwindchime1);
        //            }



      }
    }

    //
    //    if (playMem1.isPlaying() == false) {
    //      //playMem1.play(AudioSampleAteststring1);
    //      //playMem1.play(AudioSampleS16bitmonow);
    //      //playMem1.play(AudioSampleS50p16bit2w);
    //      playMem1.play(AudioSampleS11025wa);
    //    }



  }

  /*  FN Synth    */
  if (FmSynth == true) {
    
    int FMTone = 1;   //1 = A5    , 2 = G6  , 3 = ? 
    int FMFilterFreq = 1000;

    //FM Tone A5
    if (FMTone == 1) { 
    toneFMMod = 1380;
    toneFMSine = 1000 + intensity / 1000;
    }

    //FM Tone G6
    if (FMTone == 2) { 
    toneFMMod = 1705;
    toneFMSine = 387 + intensity / 1000;
    FMFilterFreq = 6000;
    }

      if (FMTone == 3) { 
    toneFMMod = 1583;
    toneFMSine = 300 + intensity / 1000;
    FMFilterFreq = 6000;
    }

    
    waveform1.begin(WAVEFORM_SINE);
    
    //Mod OSC
    
    waveform1.frequency (toneFMMod);
    waveform1.amplitude(1);

    //FM Sine
    
    sine_fm1.frequency(toneFMSine);
    sine_fm1.amplitude(1);

    //FM synth Filter
    filter3.frequency(FMFilterFreq);
    filter3.resonance(0.7);

    //FM Synth Envelope
      envelope1.attack(130);
      envelope1.release(1200);
    if ((intensity >= sampleTriThreshold) && (!envelope1.isActive() )) {

      envelope1.noteOn();
      delay(10);
      envelope1.noteOff();
      delay(31);

    }

    mixer2.gain(0, 1);
  }
  /* FM Synth END */


  /* ===Ring Mod Synth ===*/ 
  /* === for Ring Mod Frequency Calculation : https://www.mxichaelnorris.info/theory/fmcalculator == */
  
  if (RingModSynth == true) {

  int RMTone = 3;   // 1=A5   , 2=E5   ,3=G5
  float RMBendFreq ; 
  float RMFreq1 ;
  float RMFreq2;
  float RMFilterCutOff ; 
  float RMWave1Amp ;
  float RMWave2Amp ;

  // A5  dominiant: 880Hz
  if (RMTone == 1 ) { 
     RMBendFreq = intensity / 255 * 30;
     RMFreq1 = 114 - RMBendFreq;
     RMFreq2 = 994;
     
     RMFilterCutOff = 600;
     RMWave1Amp = 0.5;
     RMWave2Amp = 0.5;
  }

  //E5 Dominat 659Hz
    if (RMTone == 2 ) { 
     RMBendFreq = intensity / 255 * 30;
     RMFreq1 = 110 - RMBendFreq;
     RMFreq2 = 769;
     RMFilterCutOff = 400;
     RMWave1Amp = 0.5;
     RMWave2Amp = 0.5;
  }
  // G5 Dominat 783Hz
     if (RMTone == 3 ) { 
     RMBendFreq = intensity / 255 * 30;
     RMFreq1 = 98 - RMBendFreq;
     RMFreq2 = 685;
     RMFilterCutOff = 350   ;
      RMWave1Amp = 0.5;
     RMWave2Amp = 0.5;
  }
  
    
    
    //OSC 1
    
    
    waveform2.begin(WAVEFORM_SINE);
    waveform2.frequency(RMFreq1); // waveform2.frequency(123-intensity/255*60);
    waveform2.amplitude(RMWave1Amp);   //0.7
    //OSC 2
    waveform3.begin(WAVEFORM_SQUARE);
    waveform3.frequency(RMFreq2);   //987
    waveform3.amplitude(RMWave2Amp);   //0.7

    //Sub Osc
    waveform5.begin(WAVEFORM_SINE);
    waveform5.frequency(246);
    waveform5.amplitude(0);  //1
    filter5.frequency(300);
    filter5.resonance(0.7);
    mixer4.gain(1, 0);  //Sub OSC mix level


    //RIng Mod synth Filter
    filter4.frequency(RMFilterCutOff);   //600
    filter4.resonance(0.7);

    //Ring Mod LFO
    waveform4.begin(0.4, 3, WAVEFORM_TRIANGLE);
    mixer4.gain(0, 1); // Ring Mod OSC (1&2) Sum Level    //original 0.7

    envelope2.attack(30);

    envelope2.release(2200);

    if ((intensity >= sampleTriThreshold) && (!envelope2.isActive() )) {
      envelope2.noteOn();
      delay(31);   //delay(31)  more than the attack time
      envelope2.noteOff();
      delay(10);
    }

    mixer2.gain(1, 1);
  }

  /* ======= Ring Mod Synt END ====== */






  //Master Volume
  mixer3.gain(0, 1);   //sub group 1  (FM and Ring Mod)
  mixer3.gain(1, 1) ;  // sub group 2 (tone blip noise Sample MODE)

  mixer4.gain(0, 1);   //sub groups
  mixer4.gain(1, 0); //reverb send return

  delay(20);

}




// Function to map a flaot number
float floatMap(float x,
               float inMin,
               float inMax,
               float outMin,
               float outMax) {

  // Set bounds
  if ( x < inMin ) x = inMin;
  if ( x > inMax ) x = inMax;

  return (x - inMin) * (outMax - outMin) /
         (inMax - inMin) + outMin;
}
