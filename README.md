# WAV Decoder

Very basic WAV file decoder that parses format information and gets to the data portion of the file.

Skips over extraneous chunks like LIST and INFO.


## Building and Running

``` sh
make
./main < input.wav
Sample rate: 16000
Channels: 1
Bits per samples: 16
Samples: 31872
```

WAV data is read from `stdin` and information is printed to `stdout`.
