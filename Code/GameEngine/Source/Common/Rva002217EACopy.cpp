// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva002217EA@@QAE@ABV0@@Z @0x002217EA 51B
// Copy ctor: UnicodeString at +0 via StringBase wide copy 0x00037050 plus
// Rva0036CA00Str at +4 via nothrow copy 0x000A8C7C plus ints at +8 +0xC +0x10.
// Caller 0x00221A34 passes same src. Evidence: retail bytes.
#include "unicode_string.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

class Rva0036CA00Str
{
	void *m_item;
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str();
};

class Rva002217EA
{
public:
	Rva002217EA(const Rva002217EA &other);
private:
	UnicodeString m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva002217EA::Rva002217EA(const Rva002217EA &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
{
}
