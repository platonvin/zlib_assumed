#include <iostream>
#include <chrono>
#include <vector>
#include "zlib.h"

using namespace std;

int main() {
  // Define data size in bytes
  const size_t data_size = 1024 * 1024 * 100; // 100 MB

  // Generate random data
  vector<char> data(data_size);
  for (char& c : data) {
    c = rand() % 256; // random byte
  }

  // Create compressed buffer
  size_t compressed_size = compressBound(data_size);
  vector<char> compressed_data(compressed_size);

  // Start timer
  auto start = chrono::high_resolution_clock::now();

  // Compression
  int ret = compress2((Bytef*)compressed_data.data(), (uLongf *)&compressed_size,
                     (const Bytef*)data.data(), data_size, Z_BEST_COMPRESSION);

  // Stop timer and calculate elapsed time
  auto end = chrono::high_resolution_clock::now();
  double elapsed_time_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  if (ret != Z_OK) {
    cerr << "Compression failed with error code: " << ret << endl;
    return 1;
  }

  // Print results
  cout << "Original data size: " << data_size << " bytes" << endl;
  cout << "Compressed data size: " << compressed_size << " bytes" << endl;
  cout << "Compression ratio: " << (double)data_size / compressed_size << endl;
  cout << "Compression time: " << elapsed_time_ms << " milliseconds" << endl;

  return 0;
}