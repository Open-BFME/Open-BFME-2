// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ??1Rva001E125D@@UAE@XZ retail 0x001E125D 62B
// Evidence: unlock lane stores vtable at this then destroys member at +0x148 via releaseBuffer then base ??1Rva001DFA48Owner. Caller 0x001E1241 28B.
class Rva001DFA48Owner
{
public:
	virtual ~Rva001DFA48Owner();
};

class Rva001E125D : public Rva001DFA48Owner
{
public:
	virtual ~Rva001E125D();
private:
	char m_pad04[0x148 - 0x4];
	AsciiString m_str148;
};

Rva001E125D::~Rva001E125D()
{
}
