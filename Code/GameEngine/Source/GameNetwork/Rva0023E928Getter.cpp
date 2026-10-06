// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva0023E928@Rva0023E928@@QBE?AVUnicodeString@@XZ @0x0023E928 (27B):
// RVO UnicodeString getter copying the member at +0x24 through the rowed
// wide StringBase copy ctor at 0x37050 into the hidden return pointer.
// Same 27B shape as the neighbour ?getMap@GameInfo@@QBE?AVAsciiString@@XZ
// at 0x0023E943 in GameInfoGetMap.cpp with identical flags.
// Callers pass a stack temp and read the string out of it at 0x002408CD
// 0x002408E1 0x00240981 0x00240A11 0x00240AB2 0x00240B0D 0x00240B9C in
// 0x00240866 plus 0x00590FB0 0x00591335 0x00591AE3 0x005938BF.
// Unlocks 5 functions of which 3 become ready. No new pins.
typedef unsigned short WideChar;

#include "unicode_string.h"


class Rva0023E928
{
public:
	unsigned char m_pad[0x24];
	UnicodeString m_str;
	UnicodeString rva0023E928() const;
};

// ?rva0023E928@Rva0023E928@@QBE?AVUnicodeString@@XZ
UnicodeString Rva0023E928::rva0023E928() const
{
	return m_str;
}
