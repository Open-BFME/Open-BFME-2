// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0045A413@AutoAbilityBehavior@@QAEXXZ, retail 0x0045A413, 14 bytes.
// Sets the AsciiString at +0x20 to the empty string via the rowed
// StringBase<char>::set at 0x000055F5. Layout follows the rowed dtor
// ??1AutoAbilityBehavior at 0x0045A37F (AsciiString at +0x20) and the
// pinned ctor at 0x0045A78F (zeroes +0x20). Callers at 0x0045A72F,
// 0x0045A76C, 0x0045A89B, 0x0045ADA8 consume it to clear the string
// before setWakeFrame. No EH frame in retail; no locals need unwind.

#include "ascii_string.h"


class AutoAbilityBehavior
{
public:
	void rva0045A413();

private:
	unsigned char m_pad[0x20];
	AsciiString m_str20;
};

void AutoAbilityBehavior::rva0045A413()
{
	m_str20.set("");
}
