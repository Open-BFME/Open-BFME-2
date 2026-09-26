// cl: /O1 /DNDEBUG /MD
//
// BFME2 network Transport helpers. The class is a BFME2 rewrite of the
// Zero Hour / BFME1 Transport: the message rings still sit at +0x00000 and
// +0x20700 with stride 0x40E, but the tail is reworked around an 8-slot
// table (cleared one slot at a time through the word-indexed slot clearer
// at 0x4D5133) and a winsock-active byte flag at +0x40E08.

extern "C" {
__declspec(dllimport) int __stdcall WSACleanup(void);
}

class Transport
{
public:
	void clearSlot_Rva004D5133(unsigned short index);
	void Rva004D5496(void);

private:
	char m_pad[0x40E08];
	bool m_winsockActive;
};

// ?Rva004D5496@Transport@@QAEXXZ
// retail 0x004D5496, 42 bytes. Clears the 8 transport slots, then shuts
// down winsock if the active flag is set.
void Transport::Rva004D5496(void)
{
	for (int i = 0; i < 8; ++i)
		clearSlot_Rva004D5133((unsigned short)i);
	if (m_winsockActive) {
		WSACleanup();
		m_winsockActive = false;
	}
}
