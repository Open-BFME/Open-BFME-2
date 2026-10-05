// cl: /O1 /DNDEBUG /MD
//
// BFME2's save/load screen Apt callbacks, 0x00433DB1 onward, bound by these
// names ("AptSaveLoad::OnClosed" ...) as member pointers by the screen's
// registration; that binding is their only reference. The class is named
// for the strings' prefix. +0x27C is the screen's state.

// Rva00433D27Enable.cpp's 0x00433D27.
void Rva00433D27Enable();

// TheShell (VA 0x00E01E48, the ledger's g_Va00A01E48).
struct GlobalA01E48
{
	unsigned char m_pad[0x54];
	bool m_54; // +0x54
	unsigned char m_pad55[0x5D - 0x55];
	bool m_5d; // +0x5D
};

extern struct GlobalA01E48 *g_Va00A01E48;

// The pending confirmation at +0x280 keeps its kind at +0x28.
struct AptSaveLoadPending
{
	unsigned char m_pad[0x28];
	int m_kind; // +0x28
};

class AptSaveLoad
{
public:
	void OnClosed(const char *unused);
	void Cancel(const char *unused);
	void Delete(const char *unused);

	// Unrowed 0x00433F7F (94 bytes; banked), pinned by address.
	int rva00433F7F();

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	AptSaveLoadPending *m_pending; // +0x280
};

// Retail 0x00433DB1, 47 bytes: "AptSaveLoad::OnClosed" flags the shell
// unless a kind 6 confirmation closed it in state 6.
void AptSaveLoad::OnClosed(const char *unused)
{
	if (g_Va00A01E48)
	{
		if (m_state != 6 || !m_pending || m_pending->m_kind != 6)
			g_Va00A01E48->m_54 = true;
	}
	Rva00433D27Enable();
}

// Retail 0x00433DE0, 17 bytes: "AptSaveLoad::Cancel".
void AptSaveLoad::Cancel(const char *unused)
{
	if (m_state == 0)
		Rva00433D27Enable();
}

// Retail 0x00434318, 31 bytes: "AptSaveLoad::Delete".
void AptSaveLoad::Delete(const char *unused)
{
	if (m_state == 0 && rva00433F7F())
		m_state = 16;
}
