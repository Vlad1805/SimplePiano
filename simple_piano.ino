#include <avr/interrupt.h>

const int MI = 262;
const int FA = 294;
const int SOL = 330;
const int LA = 349;
const int SI = 392;
const int DO = 440;
const int RE = 493;

const int C_FREQ[] = {262, 196, 131, 98, 82, 65, 49}; // Guitar C frequencies
const int D_FREQ[] = {294, 220, 147, 110, 98, 73, 55}; // Guitar D frequencies
const int E_FREQ[] = {330, 247, 165, 123, 110, 82, 61}; // Guitar E frequencies
const int F_FREQ[] = {349, 262, 175, 131, 116, 87, 65}; // Guitar F frequencies
const int G_FREQ[] = {392, 294, 196, 147, 131, 98, 73}; // Guitar G frequencies
const int A_FREQ[] = {440, 330, 220, 165, 147, 110, 82}; // Guitar A frequencies
const int B_FREQ[] = {493, 370, 247, 185, 165, 123, 92}; // Guitar B frequencies

const int C = PINB3;
const int D = PINB2;
const int E = PINB1;
const int F = PINB0;
const int G = PIND7;
const int A = PIND6;
const int B = PIND5;
const int switchMode = PIND4;

const int Buzz = 12;
const int LED = PORTB5;

bool buttonReleased = false;
bool modeFreestyle = true;
bool modeSong = false;
bool mode
const int MAX_LENGTH = 3;
char note[MAX_LENGTH];

int song1[] = {5, 3, 5, 5, 3, 5,
5, 3, 3, 5 , 5, 3,
5, 5, 3, 3, 5, 3,
5, 5, 3, 3, 5, 3};
int songNote = 0;

void changeMod()
{
  if (modeFreestyle) {
    modeFreestyle = false;
    modeSong = true;
    songNote = 0;
    Serial.println("Mode Song");
  } else {
    modeFreestyle = true;
    modeSong = false;
    Serial.println("Mode Freestyle");
  }
}


void displaySongNote(int* song, int s)
{
  if (modeSong == false) {
    return;
  }
  if (songNote > s) {
    songNote = 0;
  }
  if (song[songNote] == 3) {
    Serial.println("Mi");
  }
  if (song[songNote] == 5) {
    Serial.println("Sol");
  }
  songNote++;
}

// Interrupt Service Routine (ISR) for Timer1
ISR(TIMER1_COMPA_vect) {
  // This code will be executed whenever Timer1 overflows (interrupt is triggered)
  int s = sizeof(song1) / sizeof(song1[0]);
  displaySongNote(song1, s);
}
void setup()
{
  Serial.begin(9600);
  cli();  // Disable interrupts
  DDRB |= (1 << DDB5);   // Set LED pin as OUTPUT using DDRB
  PORTB &= ~(1 << PORTB5);    // Set LED pin LOW using PORTB
  
  DDRD &= ~(C | D | E | F | G | A | B);  // Set input pins as INPUT using DDRD
  PORTB |= (1 << C | 1 << D | 1 << E | 1 << F);
  PORTD |= (1 << G | 1 << A | 1 << B);
  PORTD &= ~(1 << switchMode);
  // Set Buzz pin as OUTPUT using DDRB
  DDRB |= _BV(Buzz);

  // Set the Timer1 control registers
  TCCR1A = 0;               // Clear Timer1 control register A
  TCCR1B = 0;               // Clear Timer1 control register B
  TCNT1 = 0;                // Clear the counter

  // Set Timer1 to CTC (Clear Timer on Compare Match) mode
  TCCR1B |= (1 << WGM12);

  // Set the compare value (6-second interrupt interval)
  OCR1A = 37499;            // 16MHz / (prescaler * frequency) - 1 = 16000000 / (1024 * 0.15) - 1 = 37499

  // Enable Timer1 compare match interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Set the prescaler to 1024 (generates interrupts every 1 millisecond)
  TCCR1B |= (1 << CS12) | (1 << CS10);
  sei();  // Enable interrupts
}

void loop()
{
  noTone(Buzz);
  // Set Buzz pin HIGH using PORTB and led to low
  PORTB |= (1 << PORTB4);
  PORTB &= ~(1 << LED);
  // switch mode
  if (PIND & (1 << switchMode)) {
    changeMod();
    delay(1000);
  }
  // MI
  while((PINB & (1 << C)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz, MI);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "Mi", MAX_LENGTH);
  }

  // FA
  while((PINB & (1 << D)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz, FA);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "Fa", MAX_LENGTH);
  }

  // SOL
  while((PINB & (1 << E)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz,SOL);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "Sol", MAX_LENGTH);
  }

  // LA
  while((PINB & (1 << F)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz,LA);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "La", MAX_LENGTH);
  }

  // SI
  while((PIND & (1 << G)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz,SI);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "Si", MAX_LENGTH);
  }

  // DO
  while((PIND & (1 << A)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz,DO);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "Do", MAX_LENGTH);
  }

  // RE
  while((PIND & (1 << B)) == 0)
  {
    // Set Buzz pin HIGH using PORTB
    PORTB |= (1 << PORTB4);
    tone(Buzz,RE);
    PORTB |= (1 << LED);
    buttonReleased = true;
    strncpy(note, "Re", MAX_LENGTH);
  }

  if (buttonReleased && modeFreestyle) {
     buttonReleased = false;
     Serial.println(note);
     noTone(Buzz);
  // Set Buzz pin HIGH using PORTB and led to low
    PORTB |= (1 << PORTB4);
    PORTB &= ~(1 << LED);
     delay(100);
  }
}
