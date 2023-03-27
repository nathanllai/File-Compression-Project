#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include "huffman.h"

int main(int argc, char *argv[]) {
  // Check for correct arguments entered
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <zapfile> <outputfile>" << '\n';
    exit(1);
  }
  std::ifstream in(argv[1], std::ios::in | std::ios::binary);
  std::ofstream out(argv[2], std::ios::out | std::ios::trunc);
  if (!in.is_open()) {
    std::cerr << "Error: cannot open zap file " << argv[1] << '\n';
    exit(1);
  } else if (!out.is_open()) {
    std::cerr << "Error: cannot open input file " << argv[2] << '\n';
    exit(1);
  } else {
    // Compresses input file
    Huffman::Decompress(in, out);
    in.close();
    out.close();
  }

  return 0;
}
