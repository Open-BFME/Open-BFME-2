// cl: /DNDEBUG /MD
//
// BFME2's online stats screen Apt callback "AptOnline::Stats::CurrentTab",
// 0x005B8F04, bound by that name as a member pointer by the screen's
// registration; that binding is its only reference. The scope and class
// are named for the string.

extern "C" int __cdecl strcmp(const char *left, const char *right);

// REL32 at 0x005B8F5F passes this unchanged to the rowed 73-byte
// tab dispatcher in Rva005B8EBBBox.cpp; both use the tab word at +0x8C.
class Rva005B8EBB
{
public:
	void Run();
};

class AptOnline
{
public:
class Stats
{
public:
	void CurrentTab(const char *tab);

private:
	unsigned char m_pad00[0x8C];
	int m_tab; // +0x8C
};
};

// Retail 0x005B8F04, 101 bytes: "AptOnline::Stats::CurrentTab" selects the
// "Tournament", "OpenPlay" or "Strategic" tab.
void AptOnline::Stats::CurrentTab(const char *tab)
{
	if (strcmp(tab, "Tournament") == 0)
		m_tab = 0;
	else if (strcmp(tab, "OpenPlay") == 0)
		m_tab = 1;
	else if (strcmp(tab, "Strategic") == 0)
		m_tab = 2;
	else
		return;
	reinterpret_cast<Rva005B8EBB *>(this)->Run();
}
