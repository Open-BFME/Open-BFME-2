// cl: /DNDEBUG /MD
//
// ?rva004E9378@Rva004E9378@@QAE_NXZ, retail 0x004E9378, 20 bytes.
// Bool predicate over int at +0x10: true when 2 or 3 else false. Honest-address
// identity: __thiscall reading ecx+0x10 with 19 callers all testing al (bool)
// at 0x004E945A 0x004EA221 0x00597840 0x005978A7 0x0059799C 0x00599358 and more.
// Prev row appendOnce ends exactly at 0x004E9378. No donor. /O1 gives xor-inc.

class Rva004E9378
{
	char m_pad[0x10]; // +0x00..+0x10 unknown
	int m_state; // +0x10
public:
	bool rva004E9378();
};

bool Rva004E9378::rva004E9378()
{
	return m_state == 2 || m_state == 3;
}
