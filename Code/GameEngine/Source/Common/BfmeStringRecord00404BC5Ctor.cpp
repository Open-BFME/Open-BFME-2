// cl: /MD /Ireference/shims/bfme2_ascii
// ??0BfmeStringRecord00404BF3@@QAE@ABVAsciiString@@@Z retail 0x00404BC5 46B
// Evidence: __thiscall ret 4 takes string; calls rowed 0x000365F0 StringBase copy; zeroes +4 +8 +C +10 +14 via movss; callers 0x0040561A 0x004056B4 build vector<BfmeStringRecord00404BF3>; returns this
#include "ascii_string.h"
struct BfmeStringRecord00404BF3
{
	AsciiString text; // +0x00
	float f0; // +0x04
	float f1; // +0x08
	float f2; // +0x0C
	float f3; // +0x10
	float f4; // +0x14
	BfmeStringRecord00404BF3(const AsciiString &s);
};

BfmeStringRecord00404BF3::BfmeStringRecord00404BF3(const AsciiString &s) : text(s), f0(0.0f), f1(0.0f), f2(0.0f), f3(0.0f), f4(0.0f)
{
}

// Current BFME1 9cbfb551 VictorySystemXfer.cpp's default parameter constructor
// supplies the operation lead. Native 404BA3..404BC5 is a complete entry after
// the preceding RET and before the rowed string-taking constructor above.
// Only the accessed prefix and receiver return are established here: neither
// the original receiver type nor constructor-versus-reset identity is known.
struct Rva00404BA3InitializationView
{
	unsigned word00;
	float f04, f08, f0C, f10, f14;
	Rva00404BA3InitializationView *rva00404BA3();
};

Rva00404BA3InitializationView *Rva00404BA3InitializationView::rva00404BA3()
{
	word00 = 0;
	f04 = 0.0f;
	f08 = 0.0f;
	f0C = 0.0f;
	f10 = 0.0f;
	f14 = 0.0f;
	return this;
}
