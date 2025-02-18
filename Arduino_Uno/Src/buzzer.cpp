/**
 * @file buzzer.cpp
 * @brief Source file containing buzzer-related implementations and configurations
 * @details Controls buzzer functionality and stores musical melodies
 */

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/buzzer.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
 * @brief Current note being played by the buzzer
 * @details Stores the frequency value of the currently playing musical note
 */
int note = 0;

/**
 * @brief Melody array for Pink Panther theme
 * @details Contains frequency values for each note in the Pink Panther theme song
 */
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

/**
 * @brief Duration array for Pink Panther theme
 * @details Contains duration values corresponding to each note in melody_PinkPanther
 */
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

/**
 * @brief Melody array for Nokia ringtone
 * @details Contains frequency values for each note in the Nokia ringtone
 */
const int melody_Nokia[] = {
    NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
    NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
    NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
    NOTE_A4
};

/**
 * @brief Duration array for Nokia ringtone
 * @details Contains duration values corresponding to each note in melody_Nokia
 */
const int durations_Nokia[] = {
    8, 8, 4, 4,
    8, 8, 4, 4,
    8, 8, 4, 4,
    2
};

//------------------------------------------------------------------------------
// SUBWAY SURFERS
//------------------------------------------------------------------------------

/**
 * @brief Melody array for Subway Surfers theme
 * @details Contains frequency values for each note in the Subway Surfers theme
 */
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

/**
 * @brief Duration array for Subway Surfers theme
 * @details Contains duration values corresponding to each note in melody_SubwaySurfers
 */
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

/**
 * @brief Melody array for The Simpsons theme
 * @details Contains frequency values for each note in The Simpsons theme song
 */
const int melody_TheSimpsons[] = {
    NOTE_C4, NOTE_E4, NOTE_FS4, REST, NOTE_A4,
    NOTE_G4, NOTE_E4, NOTE_C4, NOTE_A3,
    NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, REST,
    NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, NOTE_AS3,
    NOTE_B3, REST
};

/**
 * @brief Duration array for The Simpsons theme
 * @details Contains duration values corresponding to each note in melody_TheSimpsons
 */
const int durations_TheSimpsons[] = {
    2, 4, 4, 32, 8,
    2, 4, 4, 8,
    8, 8, 8, 4, 2,
    8, 8, 8, 4, 2,
    2, 2
};

//------------------------------------------------------------------------------
// GLOBAL TABLES
//------------------------------------------------------------------------------

/**
 * @brief Size array for music tabs
 * @details Contains size information for each music tab
 */
int const size_tab[] = {sizeof(durations_PinkPanther) / sizeof(int), sizeof(durations_Nokia) / sizeof(int), sizeof(durations_SubwaySurfers) / sizeof(int), sizeof(durations_TheSimpsons) / sizeof(int)};

/**
 * @brief Duration array for music tabs
 * @details Contains duration values for each note in the music tabs
 */
int const durations_tab[] = {durations_PinkPanther,durations_Nokia,durations_SubwaySurfers, durations_TheSimpsons};

/**
 * @brief Melody array for music tabs
 * @details Contains frequency values for each note in the music tabs
 */
int const melody_tab[] = {melody_PinkPanther, melody_Nokia, melody_SubwaySurfers, melody_TheSimpsons};


//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================

/**
 * @brief Main buzzer control function
 * @details Handles the buzzer output and note playing functionality based on current mode
 */
void buzz(){
    
    if ( mode>=0 && mode < 8 ){
        
        int scaled_mode = mode%4; 
        
        if (note < size_tab[scaled_mode]) {
            
            int* tab_duration = (int*)durations_tab[scaled_mode];
            int* tab_melody = (int*)melody_tab[scaled_mode];
            
            //to calculate the note duration, take one second divided by the note type
            //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
            int duration = 1000 / tab_duration[note];
            tone(BUZZER_PIN, tab_melody[note], duration);
            
            //to distinguish the notes, set a minimum time between them
            //the note's duration + 20% seems to work well:
            int pauseBetweenNotes = duration * 1.20;
            delay(pauseBetweenNotes);
            
            //stop the tone playing:
            noTone(BUZZER_PIN);
            note++;
        }else{
            noTone(BUZZER_PIN);
            delay(100);
        }
    } else{
        delay(100);
    }
}
