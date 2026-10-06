// cl: /DNDEBUG /MD /EHsc
// ??0Rva004E13EB@@QAE@XZ, RVA 0x004E13EB, 43B. Unlock lane: ctor storing
// vtable 0x008618CC then zeroing int at +4 floats at +8/+C/+10/+14 int at
// +18 byte at +1C via xorps plus movss. Adjacent to DoXfer at 0x004E1398 but
// different vtable so new class. Caller at 0x004E1439. Owner unknown so
// honest address-derived name.
class Rva004E13EB
{
public:
	Rva004E13EB();
	virtual ~Rva004E13EB();
	int m04;
	float m08;
	float m0c;
	float m10;
	float m14;
	int m18;
	unsigned char m1c;
};

Rva004E13EB::Rva004E13EB() : m04(0), m08(0.0f), m0c(0.0f), m10(0.0f), m14(0.0f), m18(0), m1c(0)
{
}
