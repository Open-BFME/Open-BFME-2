// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0039B548@Rva003BD306Target@@QAEXXZ @0x0039B548 55B
// Clear method: zero m_38/m_0C, 0.0f to m_10, global float to m_1C,
// empty AsciiString at +8 via rowed releaseBuffer, zero m_20, then rowed
// Rva003BD306Target::rva0039B28F(1) on same this. Evidence: pin-only callee
// ?rva0039B28F@Rva003BD306Target@@QAEXH@Z proves owner Rva003BD306Target;
// callers 0x0029405F 0x004BDA78; float global g_Va00BBB8D8 (?g_Va00BBB8D8@@3MA);
// neighbours Rva0039B2E6 Rva0039B632 share flags.
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"

extern float g_Va00BBB8D8;

struct ExperienceParentView;
class BfmeThingEFC;
class Rva003BD306Target
{
public:
	void rva0039B3D1(float value,bool feedback);
	void rva0039B28F(bool v);
	void rva0039B548();
	void rva0039B2C7(int count, bool value);
	char m_pad00[0x4];
	ExperienceParentView *parent; // +0x04
private:
	AsciiString m_str08; // +0x08
public:
	int m_level; // +0x0C
	float experience; // +0x10
	char m_pad14[0x8];
private:
	float m_1C; // +0x1C
	unsigned char m_20; // +0x20
	char m_pad21[0xB];
public:
	BfmeThingEFC *handle; // +0x2C
	char m_pad30[0x8];
	ObjectID sink; // +0x38
	bool enable; // +0x3C
	char m_pad3D[0x3];
};

void Rva003BD306Target::rva0039B548()
{
	sink = INVALID_OBJECT_ID;
	experience = 0.0f;
	m_1C = g_Va00BBB8D8;
	m_str08.clear();
	m_level = 0;
	m_20 = 0;
	rva0039B28F(1);
}

void Rva003BD306Target::rva0039B2C7(int count, bool value)
{
	for (; count > 0; --count)
		rva0039B28F(value);
}
