/**
 * @file buzzer.h
 * @brief Header file containing buzzer-related declarations and configurations
 */

 #pragma once

 //=============================================================================
 //                       INCLUDE LIBRARIES AND HEADER FILES
 //=============================================================================
 
 #include <pitches.h>
 #include "utils.h"
 #include "strip_led.h"
 
 //=============================================================================
 //                                   MACROS
 //=============================================================================
 
 /**
  * @brief The pin number for the buzzer
  * @details Digital pin used for buzzer output
  */
 #define BUZZER_PIN  2
 
 //=============================================================================
 //                             VARIABLE DECLARATIONS
 //=============================================================================
 
 /**
  * @brief Current note being played by the buzzer
  * @details Stores the frequency value of the currently playing musical note
  */
 extern int note;
 
 //------------------------------------------------------------------------------
 // PINK PANTHER
 //------------------------------------------------------------------------------
 
 /**
  * @brief Melody array for Pink Panther theme
  * @details Contains frequency values for each note in the Pink Panther theme song
  */
 extern const int melody_PinkPanther[];
 
 /**
  * @brief Duration array for Pink Panther theme
  * @details Contains duration values corresponding to each note in melody_PinkPanther
  */
 extern const int durations_PinkPanther[]; 
 
 //------------------------------------------------------------------------------
 // NOKIA
 //------------------------------------------------------------------------------
 
 /**
  * @brief Melody array for Nokia ringtone
  * @details Contains frequency values for each note in the Nokia ringtone
  */
 extern const int melody_Nokia[];
 
 /**
  * @brief Duration array for Nokia ringtone
  * @details Contains duration values corresponding to each note in melody_Nokia
  */
 extern const int durations_Nokia[];
 
 //------------------------------------------------------------------------------
 // SUBWAY SURFERS
 //------------------------------------------------------------------------------
 
 /**
  * @brief Melody array for Subway Surfers theme
  * @details Contains frequency values for each note in the Subway Surfers theme
  */
 extern const int melody_SubwaySurfers[];
 
 /**
  * @brief Duration array for Subway Surfers theme
  * @details Contains duration values corresponding to each note in melody_SubwaySurfers
  */
 extern const int durations_SubwaySurfers[];
 
 //------------------------------------------------------------------------------
 // THE SIMPSONS 
 //------------------------------------------------------------------------------
 
 /**
  * @brief Melody array for The Simpsons theme
  * @details Contains frequency values for each note in The Simpsons theme song
  */
 extern const int melody_TheSimpsons[];
 
 /**
  * @brief Duration array for The Simpsons theme
  * @details Contains duration values corresponding to each note in melody_TheSimpsons
  */
 extern const int durations_TheSimpsons[];
 
 //------------------------------------------------------------------------------
 // MUSIC TABS
 //------------------------------------------------------------------------------
 
 /**
  * @brief Array containing the sizes of all the music tracks
  */
 extern int const size_tab[];
 
 /**
  * @brief Array containing the addresses of the duration array for each music track
  */
 extern int const durations_tab[];
 
 /**
  * @brief Array containing the addresses of the melody array for each music track
  */
 extern int const melody_tab[];
 
 //=============================================================================
 //                           ROUTINE PROTOTYPES
 //=============================================================================
 
 /**
  * @brief Main buzzer control function
  * @details Handles the buzzer output and note playing functionality
  */
 extern void buzz();
 