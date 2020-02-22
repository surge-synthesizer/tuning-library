#include <iostream>
#include <iomanip>
#include "Tunings.h"

using namespace Tunings;

int main( int argc, char **argv )
{
    if( argc == 1 )
    {
        std::cout << "Usage: " << argv[0] << " scl-file [kbm-file]\n\n"
                  << "Will show the frequency mapping across the midi keyboard for the scl/kbm combo" << std::endl;
        exit(1);
    }

    auto s = readSCLFile(argv[1]);
    KeyboardMapping k;
    
    if( argc == 3 )
    {
        k = readKBMFile(argv[2] );
    }

    Tuning t(s, k);
    for( int i=0; i<128; ++i )
    {
        std::cout << i << ", " << t.frequencyForMidiNote(i) << ", " << t.frequencyForMidiNoteScaledByC0(i) << ", " << t.logScaledFrequencyForMidiNote(i) << std::endl;
    }
    
}
