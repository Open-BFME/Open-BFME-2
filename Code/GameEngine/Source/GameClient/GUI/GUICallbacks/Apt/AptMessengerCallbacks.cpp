// cl: /O1 /DNDEBUG /MD
//
// BFME2's messenger screen Apt callbacks "AptMessenger::OnButtonSend",
// "AptMessenger::OnBttn_0" and "AptMessenger::OnBttn_1", bound by those
// names as member pointers by the screen's registration; that binding is
// their only reference. The class is named for the strings' prefix. Both
// buttons act on the active tab (Rva005118F3Show.cpp's g_Va00E046BC).

extern int g_Va00E046BC;

// A tab's chat entry; its unrowed 0x005B000C sends the typed line, pinned
// by address.
class Rva005B000C
{
public:
	void rva005B000C();
};

class AptMessenger
{
public:
	void OnButtonSend(const char *unused);
	void OnBttn_0(const char *unused);
	void OnBttn_1(const char *unused);

	// Unrowed tab actions and the refresh 0x00511CE6, pinned by address.
	void rva005AE886();
	void rva005AE990();
	void rva005AEA3E();
	void rva005AE90F();
	void rva005AE7C6();
	void rva00511CE6();

private:
	unsigned char m_pad000[0x280];
	Rva005B000C **m_entries; // +0x280, one per tab
	unsigned char m_pad284[0x2A0 - 0x284];
	bool m_2a0; // +0x2A0
};

// Retail 0x005119E4, 27 bytes: "AptMessenger::OnButtonSend".
void AptMessenger::OnButtonSend(const char *unused)
{
	Rva005B000C *entry = m_entries[g_Va00E046BC];
	if (entry)
		entry->rva005B000C();
}

// Retail 0x005AEF16, 28 bytes: "AptMessenger::OnBttn_0".
void AptMessenger::OnBttn_0(const char *unused)
{
	switch (g_Va00E046BC)
	{
	case 0:
		rva005AE886();
		break;
	case 1:
		rva005AE990();
		break;
	}
}

// Retail 0x005AEF32, 57 bytes: "AptMessenger::OnBttn_1".
void AptMessenger::OnBttn_1(const char *unused)
{
	switch (g_Va00E046BC)
	{
	case 0:
		if (m_2a0)
			rva005AE90F();
		else
			rva005AE7C6();
		break;
	case 1:
		rva005AEA3E();
		break;
	}
	rva00511CE6();
}
