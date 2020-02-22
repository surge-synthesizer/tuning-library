// -*-c++-*-

/*
** HEADER
** COPYRIGHT
** SHORT LICENSE
**
** DOCUMENTATION 
*/

#ifndef __INCLUDE_TUNINGS_H
#define __INCLUDE_TUNINGS_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <array>

namespace Tunings
{
    struct Tone
    {
        typedef enum Type
        {
            kToneCents,
            kToneRatio
        } Type;
        
        Type type;
        double cents;
        int ratio_d, ratio_n;
        std::string stringRep;
        double floatValue;
        
        Tone() : type(kToneRatio),
                 cents(0),
                 ratio_d(1),
                 ratio_n(1),
                 stringRep("1/1"),
                 floatValue(1.0)
            {
            }
    };
    
    struct Scale
    {
        std::string name;
        std::string description;
        std::string rawText;
        int count;
        std::vector<Tone> tones;

        Scale() : name("empty scale"),
                  description(""),
                  rawText(""),
                  count(0)
            {
            }

        bool isValid() const;
    };

    struct KeyboardMapping
    {
        bool isValid;
        int count;
        int firstMidi, lastMidi;
        int middleNote;
        int tuningConstantNote;
        double tuningFrequency, tuningPitch;
        int octaveDegrees;
        std::vector<int> keys; // rather than an 'x' we use a '-1' for skipped keys

        std::string rawText;
        std::string name;
        
        KeyboardMapping() : isValid(true),
                            count(0),
                            firstMidi(0),
                            lastMidi(127),
                            middleNote(60),
                            tuningConstantNote(60),
                            tuningFrequency(8.17579891564371 * 32.0),
                            tuningPitch(32.0),
                            octaveDegrees(12),
                            rawText( "" ),
                            name( "" )
            {
            }

    };
    
    Scale readSCLFile(std::string fname);
    Scale parseSCLData(const std::string &sclContents);
    Scale evenTemperament12NoteScale();
    
    KeyboardMapping readKBMFile(std::string fname);
    KeyboardMapping parseKBMData(const std::string &kbmContents);
    KeyboardMapping tuneA69To(double freq);
        

    /**
     * The Tuning class provides a frequency table given and is
     * constructable from a scale and mapping
     */
    class Tuning {
    public:
        constexpr static int N = 512;
        Tuning();
        Tuning( const Scale &s );
        Tuning( const KeyboardMapping &k );
        Tuning( const Scale &s, const KeyboardMapping &k );

        /**
         * Write comment on range<
         */
        double frequencyForMidiNote( int mn );
        double frequencyForMidiNoteScaledByC0( int mn );
        double logScaledFrequencyForMidiNote( int mn );

    private:
        std::array<double, N> ptable, lptable;
    };
    
} // namespace Tunings

#include "TuningsImpl.h"

#endif
