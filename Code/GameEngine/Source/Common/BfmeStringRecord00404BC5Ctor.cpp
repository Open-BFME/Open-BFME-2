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
