
### Build Instructions

Create `SDCCDIR` environment variable, that points into the folder where you installed SDCC, `SDCCDIR=/usr` in most cases.

  See [#sdcc-full-install](SDCC Full Install) for a more explicite way of installing SDCC which may be needed depending on distro. 

Compile [GBDK](https://github.com/gbdk-2020/gbdk-2020/) 

Compile [ZGB](https://github.com/Zal0/ZGB) and set `ZGB_PATH`



### Running

To run the game rom you will need to use a Game Boy Advance emulator ([mGBA](https://mgba.io/) for example)

```bash
 cd your_game_build_directory
 mgba game/game.gba
```



## Additional Instructions 

### SDCC Full Install 

### For Windows Users

You can use LCC and can skip installation, if you want you can download and run from [here](https://sdcc.sourceforge.net/snap.php#Windows). 


### For Linux users

You can download the latest version of [SDCC here at their release page](https://sdcc.sourceforge.net/snap.php#Linux). 

To install Extract the binary kit to a temporary directory. This will create a new directory called 'sdcc-4.3.0' in the temporary directory.

```bash
  cd ~
  mkdir tmp
  cd tmp
  tar xjf path/to/binary/kit/sdcc-4.3.0-i386-unknown-linux2.5.tar.bz2
```

Change to the sdcc directory and copy all files to /usr/local

```bash
    cd sdcc-4.3.0
    cp -r * /usr/local
```

  * This will install sdcc binaries into `/usr/local/bin/`
  * header files into:                    `/usr/local/share/sdcc/include/`
  * non-free header files into:           `/usr/local/share/sdcc/non-free/include/`
  * library files into:                   `/usr/local/share/sdcc/lib/`
  * non-free library files into:          `/usr/local/share/sdcc/non-free/lib/`
  * and documentation into:               `/usr/local/share/sdcc/doc/`


You can test the install by entering:

```bash
    /usr/local/bin/sdcc -v
```

This should return sdcc's version number.

Even if the default search paths look into /usr/local, sdcc is fully relocatable. Try `sdcc --print-search-dirs` if you have problems with header or library files. See sdccman.pdf for more detailed information.

Now when you can set `SDCCDIR=/usr/local` and be moving on to the next step of installing and building GBDK. 
