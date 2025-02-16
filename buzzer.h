#include <pitches.h>


//------------------------------------------------------------------------------
// PINK PANTHER
//------------------------------------------------------------------------------


const int melody_PinkPanther[] = {
    REST, REST, REST, NOTE_DS4, 
    NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
    NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
    NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
    NOTE_E4, REST, REST, NOTE_DS4,
    
    NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
    NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
    NOTE_DS5,   
    NOTE_D5, REST, REST, NOTE_DS4, 
    NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
    NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
    
    NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
    NOTE_E4, REST,
    REST, NOTE_E5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4,
    NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4,   
    NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4
};

const int durations_PinkPanther[] = {
    2, 4, 8, 8, 
    4, 8, 8, 4, 8, 8,
    8, 8,  8, 8, 8, 8, 8, 8,   
    2, 16, 16, 16, 16, 
    2, 4, 8, 4,
    
    4, 8, 8, 4, 8, 8,
    8, 8,  8, 8, 8, 8, 8, 8,
    1,   
    2, 4, 8, 8, 
    4, 8, 8, 4, 8, 8,
    8, 8,  8, 8, 8, 8, 8, 8,   
    
    2, 16, 16, 16, 16, 
    4, 4,
    4, 8, 8, 8, 8, 8, 8,
    16, 8, 16, 8, 16, 8, 16, 8,   
    16, 16, 16, 16, 16, 2
};

//------------------------------------------------------------------------------
// NOKIA
//------------------------------------------------------------------------------

const int melody_Nokia[] = {
    NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
    NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
    NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
    NOTE_A4
};

const int durations_Nokia[] = {
    8, 8, 4, 4,
    8, 8, 4, 4,
    8, 8, 4, 4,
    2
};

//------------------------------------------------------------------------------
// SUBWAY SURFERS
//------------------------------------------------------------------------------

const int melody_SubwaySurfers[] = {
    NOTE_C4, REST, NOTE_G4, REST, NOTE_AS4, NOTE_C5, NOTE_AS4, REST, NOTE_F4, NOTE_DS4, REST,
    NOTE_C4, REST, NOTE_G4, REST, NOTE_AS4, NOTE_C5, NOTE_AS4, REST, NOTE_F4, NOTE_DS4, REST,
    NOTE_C4, REST, NOTE_G4, REST, NOTE_AS4, NOTE_C5, NOTE_AS4, REST, NOTE_F4, NOTE_DS4, REST,
    
    NOTE_C4, REST, NOTE_E4, REST, NOTE_G4, NOTE_A4, NOTE_AS4,
    NOTE_C5, REST, NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST,
    NOTE_AS4, REST, NOTE_AS4, NOTE_C5, REST, NOTE_AS4, NOTE_A4, REST,
    REST,
    NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST, NOTE_AS4, REST, NOTE_E5,
    REST,
    
    NOTE_C5, REST, NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST,
    NOTE_AS4, REST, NOTE_AS4, NOTE_C5, REST, NOTE_AS4, NOTE_A4, REST,
    REST,
    NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST, NOTE_AS4, REST, NOTE_E4,
    REST,
};

const int durations_SubwaySurfers[] = {
    4, 8, 4, 8, 4, 8, 8, 16, 8, 8, 16,
    4, 8, 4, 8, 4, 8, 8, 16, 8, 8, 16,
    4, 8, 4, 8, 4, 8, 8, 16, 8, 8, 16,
    
    4, 8, 4, 8, 4, 4, 4,
    8, 16, 8, 16, 8, 16, 8, 16,
    8, 16, 8, 8, 16, 8, 8, 16,
    4,
    8, 16, 8, 16, 8, 16, 8, 4, 8,
    4,
    
    8, 16, 8, 16, 8, 16, 8, 16,
    8, 16, 8, 8, 16, 8, 8, 16,
    4,
    8, 16, 8, 16, 8, 16, 8, 4, 8,
    1
};


//------------------------------------------------------------------------------
// THE SIMPSONS 
//------------------------------------------------------------------------------

const int melody_TheSimpsons[] = {
    NOTE_C4, NOTE_E4, NOTE_FS4, REST, NOTE_A4,
    NOTE_G4, NOTE_E4, NOTE_C4, NOTE_A3,
    NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, REST,
    NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, NOTE_AS3,
    NOTE_B3, REST
};

const int durations_TheSimpsons[] = {
    2, 4, 4, 32, 8,
    2, 4, 4, 8,
    8, 8, 8, 4, 2,
    8, 8, 8, 4, 2,
    2, 2
};

//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

int const size_tab[] = {sizeof(durations_PinkPanther) / sizeof(int), sizeof(durations_Nokia) / sizeof(int), sizeof(durations_SubwaySurfers) / sizeof(int), sizeof(durations_TheSimpsons) / sizeof(int)};
int const durations_tab[] = {durations_PinkPanther,durations_Nokia,durations_SubwaySurfers, durations_TheSimpsons};
int const melody_tab[] = {melody_PinkPanther, melody_Nokia, melody_SubwaySurfers, melody_TheSimpsons};