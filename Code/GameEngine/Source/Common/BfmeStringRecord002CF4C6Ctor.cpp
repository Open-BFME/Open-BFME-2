// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0BfmeStringRecord002CF4C6@@QAE@ABVAsciiString@@0IIE@Z @0x0033B13B 79B
// Evidence: vector element type BfmeStringRecord002CF4C6 via rowed push_back 0x0033D433 caller 0x0033D751;
// layout text0 text1 word0 word1 flag0 flag1 matches copy ctor 0x002CF4C6; 2 StringBase copies via pinned 0x000365F0.
#include "ascii_string.h"

struct BfmeStringRecord002CF4C6
{
	AsciiString text0;
	AsciiString text1;
	unsigned int word0;
	unsigned int word1;
	unsigned char flag0;
	unsigned char flag1;
	BfmeStringRecord002CF4C6(const AsciiString &t0, const AsciiString &t1, unsigned int w0, unsigned int w1, unsigned char f1);
};

BfmeStringRecord002CF4C6::BfmeStringRecord002CF4C6(const AsciiString &t0, const AsciiString &t1, unsigned int w0, unsigned int w1, unsigned char f1)
	: text0(t0), text1(t1), word0(w0), word1(w1), flag0(0), flag1(f1)
{
}
