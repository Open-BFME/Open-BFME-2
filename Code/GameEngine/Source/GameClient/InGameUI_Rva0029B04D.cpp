// cl: /DNDEBUG /MD /EHsc
//
// InGameUI slots 99-100: monotonic max-setter plus clearer over the
// unsigned field at +0x7EC. Slot evidence from the InGameUI vtable at
// 0x7BE810 (slots 88-89 are the landed selectMatching pair, so the table
// is proven): slot 99 points at 0x0029B04D, slot 100 at 0x0029B060, and
// the clearer sits immediately after the setter with no other references.
// Both are leaves (no calls, no pins). The member is unsigned (retail
// compares with jbe, not jle) and the pad is 4 short of the offset for
// the vtable pointer. Semantic names are unproven so both ride
// address-derived InGameUI-scoped names; opaque behavior.

class InGameUI
{
	char m_pad[0x7EC - 4];
	unsigned int m_7EC;
public:
	virtual void setRva0029B04D(int value);
	virtual void clearRva0029B060();
};

// ?setRva0029B04D@InGameUI@@UAEXH@Z
void InGameUI::setRva0029B04D(int value)
{
	if (value > m_7EC)
		m_7EC = value;
}

// ?clearRva0029B060@InGameUI@@UAEXXZ
void InGameUI::clearRva0029B060()
{
	m_7EC = 0;
}
