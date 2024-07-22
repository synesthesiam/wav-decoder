#include <algorithm>
#include <cstdio>
#include <iostream>

#include "wav_decoder.h"

int main() {

  const std::size_t buffer_size = wav_decoder::min_buffer_size;
  uint8_t buffer[buffer_size];
  wav_decoder::WAVDecoder decoder(buffer);

  std::size_t bytes_to_read = decoder.bytes_needed();

  wav_decoder::WAVDecoderResult result = wav_decoder::WAV_DECODER_SUCCESS_NEXT;
  while (result == wav_decoder::WAV_DECODER_SUCCESS_NEXT) {
    std::size_t bytes_read =
        fread(buffer, 1, std::min(buffer_size, bytes_to_read), stdin);

    if (bytes_read == 0) {
      break;
    }

    bytes_to_read -= bytes_read;

    if (bytes_to_read > 0) {
      continue;
    }

    result = decoder.next();
    if (result == wav_decoder::WAV_DECODER_SUCCESS_IN_DATA) {
      break;
    }

    bytes_to_read = decoder.bytes_needed();
  }

  if (result == wav_decoder::WAV_DECODER_SUCCESS_IN_DATA) {
    std::cout << "Sample rate: " << decoder.sample_rate() << std::endl;
    std::cout << "Channels: " << decoder.num_channels() << std::endl;
    std::cout << "Bits per samples: " << decoder.bits_per_sample() << std::endl;

    std::size_t num_samples =
        decoder.chunk_bytes_left() /
        (decoder.num_channels() * (decoder.bits_per_sample() / 8));
    std::cout << "Samples: " << num_samples << std::endl;
  } else {
    std::cerr << "Unexpected error: " << result << std::endl;
    return 1;
  }

  return 0;
}
