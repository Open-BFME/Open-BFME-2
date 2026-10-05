// cl: /O1 /DNDEBUG /MD
//
// BFME2's time line (post-game graph) screen Apt callbacks
// "AptTimeLine::OnButtonContinue", 0x0051F6D7, and 0x0051E3C3, bound by
// those names as member pointers by the screen's registration; that binding
// is their only reference. The class is named for the strings' prefix.

// Rva00434160Init.cpp's 0x00434160 and Rva00433D3CClear.cpp's 0x00433D3C.
void __cdecl Rva00434160Init(int a, int b, bool c);
void Rva00433D3CClear();

class AptTimeLine
{
public:
	void OnButtonContinue(const char *unused);
	// Bound as "AptTimeLine::OnButtonSaveReplay" and "AptScoreScreen::Save":
	// one body or two folded, so it keeps its address.
	void rva0051E3C3(const char *unused);

	// Unrowed 0x0051ED7E (345 bytes), pinned by address.
	void rva0051ED7E();
};

// Retail 0x0051E3C3, 22 bytes: bound as "AptTimeLine::OnButtonSaveReplay"
// and "AptScoreScreen::Save".
void AptTimeLine::rva0051E3C3(const char *unused)
{
	Rva00434160Init(3, 4, false);
	Rva00433D3CClear();
}

// Retail 0x0051F6D7, 8 bytes: "AptTimeLine::OnButtonContinue".
void AptTimeLine::OnButtonContinue(const char *unused)
{
	rva0051ED7E();
}
