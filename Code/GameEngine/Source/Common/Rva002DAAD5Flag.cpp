// cl: /O1 /DNDEBUG /MD
//
// ?rva002DAAD5@Rva002DAAD5Owner@@QAEXXZ @0x002DAAD5 29B: flag-setter with
// saved-field roundtrip (thiscall, no args, void). Retail stashes +0x74,
// sets the +0x50 byte, calls the pinned siblings at 0x002DA8AF and
// 0x002D9ADC on this, then restores +0x74. Honest address-derived names.

class Rva002DAAD5Owner
{
public:
	void rva002DA8AF();
	void rva002D9ADC();
	void rva002DAAD5();
private:
	char m_pad00[0x50]; // +0x00..+0x50 unclaimed
	unsigned char m_b50; // +0x50
	char m_pad51[0x74 - 0x51]; // +0x51..+0x74 unclaimed
	void *m_p74; // +0x74
};

// ?rva002DAAD5@Rva002DAAD5Owner@@QAEXXZ
void Rva002DAAD5Owner::rva002DAAD5()
{
	void *tmp = m_p74;
	m_b50 = 1;
	rva002DA8AF();
	rva002D9ADC();
	m_p74 = tmp;
}
