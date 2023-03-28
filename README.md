# File-Compression-Project
File Compression Assignment for ECS 36C. 

The purpose of the zap program is to compress files like how zipping a file works. The same applies to how the unzap file is similar to decompressing files with unzipping a file. 

The zap program works by pushing characters of the inputted file into a priority queue while putting the encoded sequence of characters into a Huffman tree of a binary output stream. This is done while also keeping track of each character. 

The unzap program decompresses the compressed file by traversing through the Huffman tree to read the order of the characters and place them in an output file.

By: Xinyi Li and Nathan Lai
