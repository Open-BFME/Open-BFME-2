// cl: /O2 /MD /EHsc
// Native6CD500..6CD50E: 14B, INT3 padding on both sides, thiscall RET4.
// Copies the sole raw32-bit stack word into receiver offsets0 and4 and
// returns the receiver in EAX. This is a constructor-shaped prefix view;
// original type/name, full receiver extent and numeric interpretation
// are unknown. Boundary was found while checking adjacent6CD510 lead.
class Rva006CD500WordPair {
public:
 Rva006CD500WordPair(unsigned int word);
 unsigned int word0,word4;
};
Rva006CD500WordPair::Rva006CD500WordPair(unsigned int word)
 :word0(word),word4(word) {}
