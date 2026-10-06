// cl: /Ireference/shims/bfme2_ascii /O1 /Ob0
// ??4Rva00381E56@@QAEAAV0@ABV0@@Z @0x00381E56 69B. Copy-assign: AsciiString
// at +0x00 via rowed/pinned operator= 0x000366F0, UnicodeString at +0x04 via
// pinned set 0x00037150, ints at +0x08..+0x1C copied, returns this.
// Evidence: 2 pinned calls plus 6 int moves; callers 0x00386DD3/0x00386E9C;
// next Rva00630D60Assign same /O1 /Ob0 assign recipe.
#include "ascii_string.h"


class Rva00381E56
{
public:
	Rva00381E56 &operator=(const Rva00381E56 &other);
private:
	AsciiString m00;
	StringBase<unsigned short> m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
};

Rva00381E56 &Rva00381E56::operator=(const Rva00381E56 &other)
{
	m00 = other.m00;
	m04.set(other.m04);
	m08 = other.m08;
	m0C = other.m0C;
	m10 = other.m10;
	m14 = other.m14;
	m18 = other.m18;
	m1C = other.m1C;
	return *this;
}
