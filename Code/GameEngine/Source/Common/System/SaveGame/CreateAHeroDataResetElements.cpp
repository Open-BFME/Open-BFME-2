// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ?rva0040732C@CreateAHeroData@@QAE_NXZ, retail 0x0040732C..0x0040737F (83
// bytes, EH): resets the fifteen 12-byte elements at +0x80 of CreateAHeroData
// (the array its copy constructor 0x00409D4D and destructor 0x00409285 lay
// out) by assigning a default element to each (rowed assignment 0x00406E22,
// default constructor inlined) and answers true. No caller or vtable slot
// names it, so the method keeps an address-derived name.

#include "ascii_string.h"

struct BfmeHeroElement005C39DE
{
	AsciiString text;
	unsigned int word4, word8;
	BfmeHeroElement005C39DE() : text(), word4(0), word8(0) {}
	BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};

class CreateAHeroData
{
public:
	bool rva0040732C();
private:
	unsigned char m_pad00[0x80];
	BfmeHeroElement005C39DE elements80[15];	// +0x80
};

bool CreateAHeroData::rva0040732C()
{
	BfmeHeroElement005C39DE blank;
	for (int i = 0; i < 15; ++i)
		elements80[i] = blank;
	return true;
}
