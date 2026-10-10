// cl: /O2 /MD /EHsc
// Retail6CD510..6CD529: 25B thiscall three stack words and RET12.
// INT3 padding proves both bounds. Three raw32-bit inputs are stored at
// receiver offsets0/4/8 and the receiver is returned in EAX.
// BF1 575ba2b sweep proposes eight folded names for these bytes. None
// establishes a BF2 name. The old Vector3 claim was correctly retired:
// BF2 Vector3 belongs to the export-proven37B SSE owner423A0.
// This neutral prefix view claims neither a donor name nor the containing
// object's full extent nor a numeric interpretation for its three words.
class Rva006CD510WordTriple {
public:
 Rva006CD510WordTriple(unsigned int a,unsigned int b,unsigned int c);
 unsigned int word0,word4,word8;
};
Rva006CD510WordTriple::Rva006CD510WordTriple(unsigned int a,unsigned int b,unsigned int c)
 :word0(a),word4(b),word8(c) {}
