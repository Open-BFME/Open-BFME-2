// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??0Rva003B39C7@@QAE@XZ @0x003B39C7 113B. Default ctor: int 1 at +0x00,
// AsciiString from "UNUSED/(placeholder)/placeholder" at +0x04, null
// AsciiStrings at +0x08/+0x0C (retail's unwind map destroys narrow strings
// at +4, +8 and +0xC), ints at +0x10/+0x14, then an array of twelve
// AsciiStrings at +0x18 built through ??_L with the rowed default ctor
// 0x00326BE6 and dtor 0x0048BA39 (count 12, size 4), then zeros at +0x48,
// +0x7C and twelve dwords at +0x4C. The banked 0.90 attempt read the ??_L
// arguments as four 12-byte elements. Callers include 0x00204615.
#include "ascii_string.h"
class Rva003B39C7
{
public:
	Rva003B39C7();
private:
	int m00;
	AsciiString m04;
	AsciiString m08;
	AsciiString m0C;
	int m10;
	int m14;
	AsciiString m18[12];
	int m48;
	int m4C[12];
	int m7C;
};
Rva003B39C7::Rva003B39C7()
	: m00(1), m04("UNUSED/(placeholder)/placeholder"), m10(0), m14(0), m48(0), m7C(0)
{
	for (int i = 0; i < 12; i++)
		m4C[i] = 0;
}
