#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <array>
#include <cstddef>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "bstream.h"
#include "pqueue.h"

class HuffmanNode {
 public:
  explicit HuffmanNode(char ch, size_t freq,
                       HuffmanNode *left = nullptr,
                       HuffmanNode *right = nullptr)
      : ch_(ch), freq_(freq), left_(left), right_(right) { }


  bool IsLeaf() {
    // Node is a leaf if it doesn't have any children
    return left_ == nullptr && right_ == nullptr;
  }

  bool operator < (const HuffmanNode &n) const {
    // In case of equality, make it deterministic based on character
    if (freq_ == n.freq_)
      return ch_ < n.ch_;
    // Otherwise compare frequencies
    return freq_ < n.freq_;
  }

  size_t freq() { return freq_; }
  size_t data() { return ch_; }
  HuffmanNode* left() { return left_; }
  HuffmanNode* right() { return right_; }

 private:
  char ch_;
  size_t freq_;
  HuffmanNode *left_, *right_;
};

class Huffman {
 public:
  static void Compress(std::ifstream &ifs, std::ofstream &ofs);

  static void Decompress(std::ifstream &ifs, std::ofstream &ofs);

 private:
  // Helper methods...
  // Preorder traversal for getting tree output
  static void PreorderRecur(HuffmanNode *hn, BinaryOutputStream &bos);

  // Preorder traversal for code table
  static void BuildTable(HuffmanNode *hn, std::string t[], std::string temp1);
};

// To be completed below
class HuffmanNodeComp {
 public:
  bool operator()(HuffmanNode *lhs, HuffmanNode *rhs) const {
    if ((*lhs).freq() == (*rhs).freq())
      return (*lhs).data() < (*rhs).data();
    return (*lhs).freq() < (*rhs).freq();
  }
};

void Huffman::Compress(std::ifstream&ifs, std::ofstream &ofs) {
  // Min Priority queue of HuffmanNode pointers
  PQueue<HuffmanNode*, HuffmanNodeComp> bytes;

  // placeholder letter for reading file
  char let;

  // Array of ints for checking frequency
  // of characters (indexed by ASCII values)
  int ind[128] = {0};

  // Read characters from file
  ifs >> std::noskipws;
  while (ifs >> let) {
    // Cast the character as int to compare
    int num = static_cast<int>(let);
    // Increase frequency of character by 1
    ind[num]++;
  }

  int total = 0;

  // Create min priority queue of Huffman leaf nodes
  for (int i = 0; i < 128; i++) {
    if (ind[i] != 0) {
      bytes.Push(new HuffmanNode(static_cast<char>(i), ind[i]));
      total += ind[i];
    }
  }

  // Create HuffmanNode tree
  while (bytes.Size() > 1) {
    // Pop top two nodes
    HuffmanNode* one = bytes.Top();
    bytes.Pop();
    HuffmanNode* two = bytes.Top();
    bytes.Pop();

    // Create Huffman internal node and push it
    HuffmanNode* internal = new HuffmanNode(0,
    one->freq() + two->freq(), one, two);
    bytes.Push(internal);
  }

  // Create BinaryOutputStream for input to PreorderRecur
  BinaryOutputStream b(ofs);

  // Root node pointer for traversal
  HuffmanNode* rt = (bytes.Top());

  // Pre-order traversal of Huffman tree to output the tree
  Huffman::PreorderRecur(rt, b);

  // Array of strings for code table
  std::string table[128] = {};
  // temporary string for traversing tree for code table
  std::string temp;

  // Give characters their code
  Huffman::BuildTable(rt, table, temp);

  // Put number of encoded characters
  b.PutInt(total);

  ifs.clear();
  ifs.seekg(0, std::ios::beg);

  while (ifs >> let) {
    for (int i = 0; i < 128; i++) {
      if (i == static_cast<int>(let)) {
        for (int j = 0; j < static_cast<int>((table[i]).length()); j++) {
          if (table[i][j] == '0') {
            b.PutBit(0);
          } else {
            b.PutBit(1);
          }
        }
      }
    }
  }
}

void Huffman::Decompress(std::ifstream &ifs, std::ofstream &ofs) {
  // Incomplete implementation commented out
  // to allow compilation of file
  /*
  HuffmanNode* root = nullptr;
  BinaryInputStream in(ifs);
  BinaryOutputStream out(ofs);
  RecursHuffTree(root, in, )
  // Next we get the int
  int size = static_cast<int>(in.GetInt());
  bool b;
  HuffmanNode* n = root;
  for (int i = 0; i < size; i++) {
    while(!n->IsLeaf()) {
      b = in.GetBit();
      if (b == 0) {
        n = n->left();
      }
      else if (b == 1) {
        n = n->right();
      }
      out.PutChar(n->data());
    }
  }
  */
}

/*
void Huffman::RecursHuffTree(HuffmanNode* root, BinaryInputStream in,
                             HuffmanNode* left, HuffmanNode* right) {

}
*/


void Huffman::PreorderRecur(HuffmanNode *hn, BinaryOutputStream &bos) {
  if (!hn)
    return;
  // BinaryOutputStream bos(os);
  // If it is leaf, then add 1 and binary number to string
  // If it is not leaf, then just add 0 to string for the file
  if (hn->IsLeaf()) {
    bos.PutBit(1);
    bos.PutChar(hn->data());
  } else {
    bos.PutBit(0);
  }
  PreorderRecur(hn->left(), bos);
  PreorderRecur(hn->right(), bos);
}

void Huffman::BuildTable(HuffmanNode *hn, std::string t[], std::string temp1) {
  if (!hn)
    return;

  if (hn->IsLeaf()) {
    // Give leaf node a code
    t[static_cast<int>(hn->data())] = temp1;
  }
  BuildTable(hn->left(), t, temp1 + "0");

  BuildTable(hn->right(), t, temp1 + "1");
}

#endif  // HUFFMAN_H_
