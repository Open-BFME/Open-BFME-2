// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva004D6119@Rva004D6119@@QBE?AVUnicodeString@@XZ @0x004D6119 (27B):
// Value-returning wide-string getter, same shape as PlayerTemplate::getDisplayName
// @0x00449B8F (27B) and GlobalData::rva002360FC @0x002360FC (30B, 3B larger for
// 0x1244 disp32 vs 0x1c disp8). Returns member at +0x1c via the rowed wide
// StringBase copy ctor @0x00037050 directly; hidden return pointer in [ebp+8]
// returned in eax. Callers pass a stack temp and read the string out (0x004D1023,
// 0x004D10F1, 0x00590F47, 0x00590F76 plus 6 more unblocked). Honest-address name:
// owner unproven so class Rva004D6119.

typedef int Int;
typedef unsigned short WideChar;

#define NULL 0

#include "ascii_string.h"


#include "unicode_string.h"

class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;

private:
	char m_pad[0x1c];
	UnicodeString m_str1c;
};

UnicodeString Rva004D6119::rva004D6119() const
{
	return m_str1c;
}
