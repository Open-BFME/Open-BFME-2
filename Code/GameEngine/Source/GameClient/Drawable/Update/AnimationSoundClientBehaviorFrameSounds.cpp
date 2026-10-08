// Ghidra004C9E5D+55, called by animation-sound processing004CA328.
// Clean BF1 9cbfb551fe20 AnimationSoundInfoCtor.cpp establishes key/reference/frame
// and required/excluded-condition semantics. Target key is an integer identifier;
// masks are19 words each (76B), versus BF1 ten; offsets0/4/8/C/58/A4 are target facts.
// The prefix shares the independently verified Rva002390CB cleanup (owner+4 release).
// Inheritance is a C++ prefix/lifetime view, not a claim about the original class.
// Default intrusive-reference construction after key initialization preserves native store order.
// Original record owner remains unknown; keep its constructor address-derived.
// cl: /O1 /G7 /arch:SSE /MD /EHsc
struct Rva0042526Member {unsigned words[19];Rva0042526Member() throw();};
struct AudioKeyRef {void*p;
// ?AudioKeyRef::AudioKeyRef present-unmatched
__forceinline AudioKeyRef():p(0){}};
class Rva002390CB {public:
 // ?Rva002390CB::Rva002390CB present-unmatched
 __forceinline Rva002390CB(const int *p):key(*p),audio(){}
 ~Rva002390CB();
 int key;AudioKeyRef audio;
};
class Rva004C9E5D:public Rva002390CB {public:
 Rva004C9E5D(const int*,float);
 float frame;Rva0042526Member required,excluded;bool anyConditions;
};
Rva004C9E5D::Rva004C9E5D(const int*p,float f):Rva002390CB(p),frame(f),anyConditions(false) {}
