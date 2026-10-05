// cl: /O1 /DNDEBUG /MD
//
// BFME2's time line (post-game graph) screen Apt callback
// "AptTimeLine::OnButtonContinue", 0x0051F6D7, bound by that name as a
// member pointer by the screen's registration; that binding is its only
// reference. The class is named for the string's prefix.

class AptTimeLine
{
public:
	void OnButtonContinue(const char *unused);

	// Unrowed 0x0051ED7E (345 bytes), pinned by address.
	void rva0051ED7E();
};

// Retail 0x0051F6D7, 8 bytes: "AptTimeLine::OnButtonContinue".
void AptTimeLine::OnButtonContinue(const char *unused)
{
	rva0051ED7E();
}
