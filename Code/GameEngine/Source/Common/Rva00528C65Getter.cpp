// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva00528C65@Rva00528C65@@QBE?AVAsciiString@@XZ retail 0x00528C65 32B
// Evidence: EBP frame; copy [ecx+4]+0x12C via StringBase copy 0x365F0 into hidden return; caller 0x00529224
#include "ascii_string.h"

struct Rva00528C65Mid
{
	char m_pad[0x12C];
	AsciiString m_str;
};

class Rva00528C65
{
public:
	AsciiString rva00528C65() const;
private:
	char m_pad04[4];
	Rva00528C65Mid *m_ptr;
};

AsciiString Rva00528C65::rva00528C65() const
{
	return m_ptr->m_str;
}
