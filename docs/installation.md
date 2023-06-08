


### SDCC Full Install

### For Linux users

To install Extract the binary kit to a temporary directory.

This will create a new directory called 'sdcc-4.3.0' in the temporary directory.

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

Even if the default search paths look into /usr/local, sdcc is fully
relocatable. Try `sdcc --print-search-dirs` if you have problems with header
or library files. See sdccman.pdf for more detailed information.
