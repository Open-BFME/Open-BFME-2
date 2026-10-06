// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005D30EE@Rva005D30EE@@QAEXHH@Z @0x005D30EE 101B, ?rva005D3153@Rva005D30EE@@QAEXHH@Z @0x005D3153 101B,
// ?rva005D31B8@Rva005D30EE@@QAEXHH@Z @0x005D31B8 101B: Apt counter setters (BuildPlots/ArmoryPoints/CommandPoints)
// via StrategicHUD::SetString and by-value "%d/%d" formatter pinned at 0x005D303A. Guarded pair caches at
// +0x08/+0x0C, +0x10/+0x14, +0x18/+0x1C; level at +0, outer at +4. Honest address names.
#include "ascii_string.h"
#include "unicode_string.h"
namespace StrategicHUD
{
	void SetString(unsigned int level, const AsciiString &clipName, const char *suffix, const UnicodeString &text);
}
UnicodeString __cdecl Rva005D303AFormat(int a, int b);
class Rva005D30EE
{
public:
	void rva005D30EE(int a, int b);
	void rva005D3153(int a, int b);
	void rva005D31B8(int a, int b);
private:
	unsigned int m_level;
	AsciiString m_clipName;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
};
void Rva005D30EE::rva005D30EE(int a, int b)
{
	if (a == m_08 && b == m_0C)
		return;
	StrategicHUD::SetString(m_level, m_clipName, "BuildPlots", Rva005D303AFormat(a, b));
	m_08 = a;
	m_0C = b;
}
void Rva005D30EE::rva005D3153(int a, int b)
{
	if (a == m_10 && b == m_14)
		return;
	StrategicHUD::SetString(m_level, m_clipName, "ArmoryPoints", Rva005D303AFormat(a, b));
	m_10 = a;
	m_14 = b;
}
void Rva005D30EE::rva005D31B8(int a, int b)
{
	if (a == m_18 && b == m_1C)
		return;
	StrategicHUD::SetString(m_level, m_clipName, "CommandPoints", Rva005D303AFormat(a, b));
	m_18 = a;
	m_1C = b;
}
