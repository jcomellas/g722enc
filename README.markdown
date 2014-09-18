G722 and G722.1 Encoders for FreeSWITCH
=======================================

These encoders convert 16 bit, linear PCM, 16 kHz, mono WAV files into raw G722
and G722.1 files that can be used with [FreeSWITCH](http://www.freeswitch.org/) to play audios and avoid
transcoding. For this to happen you will need to enable the [mod_native_file](http://wiki.freeswitch.org/wiki/Mod_native_file)
module in [FreeSWITCH](http://www.freeswitch.org/) and use the ``G722`` and ``G7221`` file extensions.


Requirements
------------

You need to install the following three libraries to be able to compile the
encoders:

### libsndfile and libtiff

    sudo apt-get install libsndfile-dev libtiff-dev

### libspandsp
From within the FreeSWITCH directory run the following commands:

    ./bootstrap.sh
    cd libs/spandsp
    ./configure
    make
    sudo make install
    sudo ldconfig

### libg722_1
After running the previous commands and going back to the FreeSWITCH directory run:

    cd libs/libg722_1
    ./configure
    make
    sudo make install
    sudo ldconfig


Compiling
---------

In order to compile the encoders run:

    make
    sudo make install


Usage
-----

The encoders have the following syntax:

    g722enc <WAV file> <G722 file>

and:

    g7221enc <WAV file> <G7221 file>

