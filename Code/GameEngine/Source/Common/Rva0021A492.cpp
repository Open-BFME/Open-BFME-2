// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
//
// ?rva0021A492@Rva0021A492Host@@QAEPAXXZ @ 0x0021A492 84B (dump range 7).
// Target constructs an AsciiString from "MyHero.dat", calls 0x004099CA on
// this+0x0C with its address and zero, and returns this+0x0C when AL is set.
// The local object's type is supported by its constructor/destructor calls;
// helper owner and full semantic identity remain unresolved.
#include "ascii_string.h"

class Rva004099CAHelper
{
public:
	bool rva004099CA(void *, int);
};

class Rva0021A492Host
{
public:
	void *rva0021A492();
};

void *Rva0021A492Host::rva0021A492()
{
	bool found;
	Rva004099CAHelper *sub;
	{
		AsciiString filename("MyHero.dat");
		sub = (Rva004099CAHelper *)((char *)this + 0x0C);
		found = sub->rva004099CA(&filename, 0);
	}
	return found ? (void *)sub : 0;
}
