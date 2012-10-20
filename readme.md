# PRisme Music Player
This is a music player, it takes in a frequency and generates a square wave. It uses 8-bit timers (0 and 2) to output 2 channels. The output spectrum covers everything from 20Hz to 20kHz.

The Arduino function tone() cannot be made compatible with the PRisme as of version 1.0.1, so the frequency generator had to be made from groud up.

## Frequency Generator
The frequency generator goes through the available timer prescalers (see datasheet) and selects the first that allows the timer compare value to be under 255 since they are 8-bit timers. The new prescaler and compare value are set and the frequency is generated with an interrupt that toggles the output pin.

## Format
The music is stored as an array of frequencies, a _beats per minute_ variable sets the tempo and a _beats_ variable sets the division of a time signature.

The music is the stored this way:

    unsigned int music PROGMEM = {
        {G4, 0}, {FS4, 0}, {E4, 0}, {E4, 0},
        {FS4, A3}, {0, D4}, {0, FS4}, {0, D4},
        {0, B3}, {0, D4}, {0, FS4}, {0, D4}
    };

The first value of the music array element being the first track and the second is the second track, this ensures synchronization and a rather easily understandable format, but no flexibility and lots of overhead.

The example music is _Still Alive_, end credits music from Portal video game by Valve.

## Output
To output the sound one has to connect speakers to the board, follow the tone() function documentation hardware part for this. Basically just connect an 8ohm speaker in series with a 100ohm resistor to the output pin and ground.

*Warning*: you cannot output multiple sound tracks with a single speaker (connect multiple output pins to the speaker) with this setup, or you might short your output pin to ground and destroy the microcontroller. 