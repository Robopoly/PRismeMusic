/*
 Title:        PRisme Music Player
 Description:  Makes the PRisme sing a song. In this example
               Still Alive from Portal.
 Author:       Karl Kangur <karl.kangur@gmail.com>
 Version:      1.0
 Website:      http://robopoly.ch
*/

#include <avr/pgmspace.h>
#include <util/delay.h>
#include "pitch.h"

// output pins (speakers)
#define SPK PC(2)
#define SPK2 PA(0)

// musis tempo
#define BPM 120
#define BEATS 4
#define DELAY BPM * 1000 / 60 / BEATS

// based on this: http://www.steamgames.com/v/img/whatsnew/StillAlive.pdf
// and this: http://www.batsocks.co.uk/downloads/tms_StillAlive_003.ino
const unsigned int melody[][2] PROGMEM = {
{G4, 0}, {FS4, 0}, {E4, 0}, {E4, 0}, // 0
{FS4, A3}, {0, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4},
{0, A3}, {0, D4}, {0, FS4}, {A3, D4},
{G4, B3}, {FS4, D4}, {E4, FS4}, {E4, D4}, // 4
{E4, A3}, {FS4, D4}, {0, FS4}, {0, D4},
{D4, B3}, {D4, D4}, {E4, FS4}, {A3, D4},
{A3, A3}, {A3, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {A3, D4}, // 8
{E4, B3}, {E4, E4}, {FS4, G4}, {G4, E4},
{G4, B3}, {G4, E4}, {E4, G4}, {CS4, E4},
{CS4, A3}, {D4, CS4}, {D4, G4}, {D4, CS4},
{E4, A3}, {E4, CS4}, {A3, G4}, {A3, CS4}, // 12
{A3, A3}, {FS4, D4}, {FS4, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4},
{0, A3}, {0, D4}, {0, FS4}, {0, D4},
{G4, B3}, {FS4, D4}, {E4, FS4}, {E4, D4}, // 16
{FS4, A3}, {0, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4},
{0, A3}, {0, D4}, {0, FS4}, {A3, D4},
{G4, B3}, {FS4, D4}, {E4, FS4}, {E4, D4}, // 20
{0, A3}, {0, D4}, {FS4, FS4}, {D4, D4},
{0, B3}, {0, D4}, {E4, FS4}, {A3, D4},
{A3, A3}, {0, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4}, // 24
{E4, B3}, {E4, E4}, {FS4, G4}, {G4, E4},
{G4, B3}, {G4, E4}, {E4, G4}, {CS4, E4},
{CS4, A3}, {CS4, CS4}, {D4, G4}, {E4, CS4},
{0, A3}, {A3, E4}, {D4, G4}, {E4, CS4}, // 28
{F4, AS3}, {E4, D4}, {D4, F4}, {C4, A4},
{0, 0}, {0, 0}, {A3, 0}, {AS3, 0},
{C4, 0}, {C4, 0}, {F4, 0}, {F4, 0},
{E4, 0}, {D4, 0}, {D4, 0}, {C4, 0}, // 32
{D4, 0}, {C4, 0}, {C4, 0}, {C4, 0},
{C4, 0}, {C4, 0}, {A3, 0}, {AS3, 0},
{C4, 0}, {C4, 0}, {F4, 0}, {F4, 0},
{G4, 0}, {F4, 0}, {E4, 0}, {D4, 0}, // 36
{D4, 0}, {E4, 0}, {F4, 0}, {F4, 0},
{F4, 0}, {F4, 0}, {G4, 0}, {A4, 0},
{AS4, 0}, {AS4, 0}, {A4, 0}, {A4, 0},
{G4, 0}, {G4, 0}, {F4, 0}, {G4, 0}, // 40
{A4, 0}, {A4, 0}, {G4, 0}, {G4, 0},
{F4, 0}, {F4, 0}, {D4, 0}, {C4, 0},
{D4, 0}, {F4, 0}, {F4, 0}, {E4, 0},
{E4, 0}, {E4, 0}, {FS4, 0}, {FS4, 0}, // 44
{FS4, D4}, {FS4, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3}, // 48
{0, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {A3, D4},
{G4, B3}, {FS4, 0}, {E4, 0}, {E4, B3}, // 52
{E4, D4}, {FS4, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {0, D4},
{G4, B3}, {FS4, 0}, {E4, 0}, {E4, B3}, // 56
{E4, D4}, {E4, D4}, {D4, FS4}, {D4, D4},
{D4, B3}, {E4, 0}, {E4, 0}, {A3, B3},
{A3, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3}, // 60
{E4, E4}, {E4, 0}, {FS4, E4}, {G4, E4},
{G4, E4}, {G4, FS4}, {E4, FS4}, {E4, G4},
{CS4, A3}, {CS4, 0}, {D4, A3}, {E4, A3},
{E4, A3}, {E4, B3}, {A3, B3}, {A3, CS4}, // 64
{A3, D4}, {FS4, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {A3, D4},
{G4, B3}, {FS4, 0}, {E4, 0}, {E4, B3}, // 68
{FS4, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {A3, D4},
{G4, B3}, {FS4, 0}, {E4, 0}, {E4, B3}, // 72
{0, D4}, {0, 0}, {FS4, 0}, {D4, D4},
{0, B3}, {0, 0}, {E4, 0}, {A3, B3},
{A3, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3}, // 76
{E4, E4}, {E4, 0}, {FS4, E4}, {G4, E4},
{G4, E4}, {G4, FS4}, {E4, FS4}, {E4, G4},
{CS4, A3}, {CS4, 0}, {D4, A3}, {E4, A3},
{0, A3}, {A3, B3}, {D4, B3}, {E4, CS4}, // 80
{F4, AS3}, {E4, 0}, {D4, AS3}, {C4, AS3},
{0, AS3}, {0, AS3}, {A3, AS3}, {AS3, AS3},
{C4, F4}, {C4, 0}, {F4, F4}, {F4, 0},
{E4, C4}, {D4, 0}, {D4, C4}, {C4, 0}, // 84
{D4, AS3}, {C4, 0}, {C4, AS3}, {C4, 0},
{C4, F4}, {C4, 0}, {A3, F4}, {AS3, 0},
{C4, F4}, {C4, 0}, {F4, F4}, {F4, 0},
{G4, C4}, {F4, 0}, {E4, C4}, {D4, 0}, // 88
{D4, AS3}, {E4, 0}, {F4, AS3}, {F4, 0},
{F4, F4}, {F4, 0}, {G4, F4}, {A4, 0},
{AS4, AS3}, {AS4, AS3}, {A4, AS3}, {A4, AS3},
{G4, C4}, {G4, C4}, {F4, C4}, {G4, C4}, // 92
{A4, F4}, {A4, F4}, {G4, F4}, {F4, F4},
{F4, D4}, {F4, D4}, {D4, D4}, {C4, D4},
{D4, AS3}, {F4, 0}, {F4, F4}, {E4, 0},
{E4, A3}, {E4, 0}, {FS4, E4}, {FS4, 0}, // 96
{FS4, D4}, {FS4, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3}, // 100
{0, D4}, {0, 0}, {0, 0}, {0, D4},
{0, B3}, {0, 0}, {0, 0}, {0, B3},
{0, D4}, {0, 0}, {0, 0}, {0, D4},
{G4, B3}, {FS4, 0}, {E4, 0}, {E4, B3}, // 104
{FS4, A3}, {FS4, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4},
{0, A3}, {0, D4}, {0, FS4}, {A3, D4},
{G4, B3}, {FS4, D4}, {E4, FS4}, {E4, D4}, // 108
{0, A3}, {0, D4}, {FS4, FS4}, {D4, D4},
{0, B3}, {0, D4}, {E4, FS4}, {A3, D4},
{A3, A3}, {0, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4}, // 112
{E4, B3}, {E4, E4}, {FS4, G4}, {G4, E4},
{G4, B3}, {G4, E4}, {E4, G4}, {E4, E4},
{CS4, A3}, {CS4, E4}, {D4, G4}, {E4, CS4},
{E4, A3}, {E4, E4}, {A3, G4}, {A3, CS4}, // 116
{E4, A3}, {FS4, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4},
{0, A3}, {0, D4}, {0, FS4}, {0, D4},
{B4, B3}, {A4, D4}, {G4, FS4}, {G4, D4}, // 120
{A4, A3}, {0, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4},
{0, A3}, {0, D4}, {0, FS4}, {0, D4},
{B4, B3}, {A4, D4}, {G4, FS4}, {G4, D4}, // 124
{0, A3}, {0, D4}, {A4, FS4}, {FS4, D4},
{0, B3}, {0, D4}, {G4, FS4}, {D4, D4},
{D4, A3}, {0, D4}, {0, FS4}, {0, D4},
{0, B3}, {0, D4}, {0, FS4}, {0, D4}, // 128
{E4, B3}, {E4, E4}, {FS4, G4}, {G4, E4},
{G4, B3}, {G4, E4}, {E4, G4}, {E4, E4},
{CS4, A3}, {CS4, CS4}, {D4, G4}, {E4, CS4},
{0, A3}, {A3, CS4}, {D4, G4}, {E4, CS4}, // 132
{F4, AS3}, {E4, D4}, {D4, G4}, {C4, F4},
{0, 0}, {0, 0}, {A3, 0}, {AS3, 0},
{C4, 0}, {C4, 0}, {F4, 0}, {F4, 0},
{E4, 0}, {D4, 0}, {D4, 0}, {C4, 0}, // 136
{D4, 0}, {C4, 0}, {C4, 0}, {C4, 0},
{C4, 0}, {C4, 0}, {A3, 0}, {AS3, 0},
{C4, 0}, {C4, 0}, {F4, 0}, {F4, 0},
{G4, 0}, {F4, 0}, {E4, 0}, {D4, 0}, // 140
{D4, 0}, {E4, 0}, {F4, 0}, {F4, 0},
{F4, 0}, {F4, 0}, {G4, 0}, {A4, 0},
{AS4, 0}, {AS4, 0}, {A4, 0}, {G4, 0},
{G4, 0}, {G4, 0}, {F4, 0}, {G4, 0}, // 144
{A4, 0}, {A4, 0}, {G4, 0}, {F4, 0},
{F4, 0}, {F4, 0}, {D4, 0}, {C4, 0},
{D4, 0}, {F4, 0}, {F4, 0}, {E4, 0},
{E4, 0}, {E4, 0}, {FS4, 0}, {FS4, 0}, // 148
{FS4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {0, 0}, {A4, 0}, {A4, 0},
{B4, 0}, {A4, 0}, {FS4, 0}, {D4, 0},
{D4, 0}, {E4, 0}, {FS4, 0}, {A4, 0}, // 152
{A4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {A4, 0}, {A4, 0}, {A4, 0},
{B4, 0}, {A4, 0}, {FS4, 0}, {D4, 0},
{D4, 0}, {G4, 0}, {A4, 0}, {A4, 0}, // 156
{A4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {A4, 0}, {A4, 0}, {A4, 0},
{B4, 0}, {A4, 0}, {FS4, 0}, {D4, 0},
{D4, 0}, {G4, 0}, {A4, 0}, {A4, 0}, // 160
{A4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {0, 0}, {A4, 0}, {A4, 0},
{B4, 0}, {A4, 0}, {FS4, 0}, {D4, 0},
{D4, 0}, {G4, 0}, {A4, 0}, {A4, 0}, // 164
{A4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {A4, 0}, {A4, 0}, {A4, 0},
{B4, 0}, {A4, 0}, {FS4, 0}, {D4, 0},
{D4, 0}, {G4, 0}, {A4, 0}, {A4, 0}, // 168
{A4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {G4, 0}, {A4, 0}, {A4, 0},
{A4, 0}, {0, 0}, {0, 0}, {0, 0},
{0, 0}, {G4, 0}, {FS4, 0}, {FS4, 0}, // 172
{FS4, 0}, {0, 0}, {0, 0}, {0, 0}
};

void sound()
{
  const unsigned int prescalers0[] = {1, 8, 64, 256, 1024};
  const unsigned int prescalers2[] = {1, 8, 32, 64, 128, 256, 1024};
  
  unsigned char prescaler;
  unsigned int ocr, freq, i, j, length;
  
  length = sizeof(melody)/sizeof(int)/2;
  for(i = 0; i < length; i++)
  {
    freq = pgm_read_word(&(melody[i][0]));
    // limit output frequency to between 20Hz and 20kHz
    if(freq < 20 || freq > 20000)
    {
      TCCR2 = 0;
      digitalWrite(SPK, LOW);
    }
    else
    {
      // scan through prescalars to find the best fit (ocr <= 255)
      for(j = 0; j < 7; j++)
      {
        ocr = F_CPU / freq / 2 / prescalers2[j] - 1;
        prescaler = j + 1;
        // a suitable prescaler was found
        if(ocr <= 255)
        {
          break;
        }
      }
      // set CTC mode and prescaler
      TCCR2 = (1 << WGM21)|(prescaler << CS20);
      // define pwm value
      OCR2 = ocr;
      // enable interrupt on compare
      TIMSK |= (1 << OCIE2);
    }
    
    freq = pgm_read_word(&(melody[i][1]));
    if(freq < 20 || freq > 20000)
    {
      TIMSK &= ~(1 << OCIE0);
      digitalWrite(SPK2, LOW);
    }
    else
    {
      // scan through prescalars to find the best fit (ocr <= 255)
      for(j = 0; j < 5; j++)
      {
        ocr = F_CPU / freq / 2 / prescalers0[j] - 1;
        prescaler = j + 1;
        // a suitable prescaler was found
        if(ocr <= 255)
        {
          break;
        }
      }
      // set CTC mode and prescaler
      TCCR0 = (1 << WGM01)|(prescaler << CS00);
      // define pwm value
      OCR0 = ocr;
      // enable interrupt on compare
      TIMSK |= (1 << OCIE0);
    }
    
    _delay_ms((unsigned int)DELAY);
  }
}

// toggle line with pwm
ISR(TIMER0_COMP_vect)
{
  digitalWrite(SPK2, !digitalRead(SPK2));
}

ISR(TIMER2_COMP_vect)
{
  digitalWrite(SPK, !digitalRead(SPK));
}

void setup()
{
  pinMode(SPK, OUTPUT);
  pinMode(SPK2, OUTPUT);
}

void loop()
{
  sound();
}

