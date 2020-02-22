#define CATCH_CONFIG_MAIN
#include "catch2.hpp"

#include "Tunings.h"
#include <iomanip>

/*
** ToDo
** more scl parse
** any kbm parse
** tuning scl > 12 < 12
** tuning with constant scl and multiple kbm
** tuning with non-contiguous kbm
** tuning with non-monotonic kbm
** tuning with non-monotonic scl
** few known tunings across the whole spectrun
*/

std::string testFile(std::string fn) {
    return std::string( "tests/data/" ) + fn;
}

TEST_CASE( "Loading .scl files" )
{
    SECTION( "Load a 12 tone standard tuning" )
    {
        auto s = Tunings::readSCLFile( testFile( "12-intune.scl" ) );
        REQUIRE( s.count == 12 );
        // FIXME - write a lot more here obviously
    }
}

TEST_CASE( "Loading .scl data" )
{
}

TEST_CASE( "Identity Tuning Tests" )
{
    SECTION( "12-intune tunes properly" )
    {
        auto s = Tunings::readSCLFile( testFile( "12-intune.scl" ) );
        REQUIRE( s.count == 12 );
        Tunings::Tuning t( s );
        REQUIRE( t.frequencyForMidiNote( 69 ) == Approx( 440.0 ).margin( 1e-10 ) );
        REQUIRE( t.frequencyForMidiNoteScaledByMidi0( 60 ) == 32.0 );
        REQUIRE( t.logScaledFrequencyForMidiNote( 60 ) == 5.0 );
    }

    SECTION( "12-intune doubles properly" )
    {
        auto s = Tunings::readSCLFile( testFile( "12-intune.scl" ) );
        Tunings::Tuning t( s );
        for( int i=0; i<12; ++i )
        {
            int note = - 12 * 4 + i;
            auto sc = t.frequencyForMidiNoteScaledByMidi0( note );
            auto lc = t.logScaledFrequencyForMidiNote( note );
            while( note < 200 )
            {
                note += 12;
                auto nlc = t.logScaledFrequencyForMidiNote( note );
                auto nsc = t.frequencyForMidiNoteScaledByMidi0( note );
                REQUIRE( nsc == Approx( sc * 2 ).margin(1e-8) );
                REQUIRE( nlc == Approx(lc + 1).margin(1e-8) );
                sc = nsc;
                lc = nlc;
            }
        }
    }

    SECTION( "Scaling is constant" )
    {
        auto s = Tunings::readSCLFile( testFile( "12-intune.scl" ) );
        Tunings::Tuning t( s );
        auto f60 = t.frequencyForMidiNote( 60 );
        auto fs60 = t.frequencyForMidiNoteScaledByMidi0( 60 );
        for( int i=-200; i<200; ++i )
        {
            auto f = t.frequencyForMidiNote( i );
            auto fs = t.frequencyForMidiNoteScaledByMidi0( i );
            REQUIRE( f/fs == f60/fs60 );
        }
    }
}

TEST_CASE( "Simple Keyboard Remapping Tunes A69" )
{
    SECTION( "A440" )
    {
        auto k = Tunings::tuneA69To( 440.0 );
        Tunings::Tuning t(k);
        REQUIRE( t.frequencyForMidiNote( 69 ) == Approx( 440.0 ).margin( 1e-10 ) );
        REQUIRE( t.frequencyForMidiNote( 60 ) == Approx( 261.625565301 ).margin( 1e-10 ) );
    }

    SECTION( "A432" )
    {
        auto k = Tunings::tuneA69To( 432.0 );
        Tunings::Tuning t(k);
        REQUIRE( t.frequencyForMidiNote( 69 ) == Approx( 432.0 ).margin( 1e-10 ) );
        REQUIRE( t.frequencyForMidiNote( 60 ) == Approx( 261.625565301  * 432 / 440).margin( 1e-10 ) );
    }

    SECTION( "Random As Scale Consistently" )
    {
        Tunings::Tuning ut;
        
        for( int i=0; i<100; ++i )
        {
            auto fr = 400 + 80.0 * rand() / RAND_MAX;
            
            auto k = Tunings::tuneA69To( fr );
            Tunings::Tuning t(k);
            REQUIRE( t.frequencyForMidiNote( 69 ) == Approx( fr ).margin( 1e-10 ) );
            REQUIRE( t.frequencyForMidiNote( 60 ) == Approx( 261.625565301  * fr / 440).margin( 1e-10 ) );

            double ldiff = t.logScaledFrequencyForMidiNote(69) - ut.logScaledFrequencyForMidiNote(69);
            double ratio = t.frequencyForMidiNote(69) / ut.frequencyForMidiNote(69);

            for( int j=-200; j<200; ++j )
            {
                REQUIRE( t.logScaledFrequencyForMidiNote(j) - ut.logScaledFrequencyForMidiNote(j) == Approx( ldiff ).margin( 1e-8 ) );
                REQUIRE( t.frequencyForMidiNote(69) / ut.frequencyForMidiNote(69) == Approx( ratio ).margin( 1e-8 ) );
            }
        }

    }
}
