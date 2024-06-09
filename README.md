
HUFFMAN ENCODING IS A WAY OF ENCODING AND DECODING FILES SUCH THAT IT REDUCES THE FILE SIZE BY UPTO 65% 
IT RELIES ON BITWISE XOR/Forward and backward operations
It uses A Heap Search Tree to keep all the terminals as characters and all the edges as a bit number representing the character encoding
No two chars may have the same encoding, and this follows a greedy-method

Our project at heart follows Huffman Encoding but we added the implementation of Linked List for sequential data storage of file! 
This type of compression algorithm is completely lossless meaning the original file can be recreated at any time from the compressed file !
