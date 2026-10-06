// cl: /DNDEBUG /MD
//
// Bfme939Helper's matched callers use the dword at this+0x1C as an integer
// gate (BfmeGlob939D::bfmeCall939D at 0x0023C6FD). Retail 0x0030F2C7 is the
// exact 4-byte load-and-return also used by NetWrapperCommandMsg::getData;
// Rva0023C666Check at 0x0023C666 uses the same value as a pointer sentinel.
// ?get@Bfme939Helper@@QBEHXZ

struct Bfme939Helper
{
	int get() const;
	char m_lead[0x1C];
	int m_value;
};

int Bfme939Helper::get() const
{
	return m_value;
}
