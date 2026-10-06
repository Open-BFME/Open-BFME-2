// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0032B7A7@SidesList@@QAEXPAV1@@Z retail 0x0032B7A7 60 bytes.
// SidesList single-teamrec swap: rowed TeamsInfoRec::swap at 0x0032B651 for
// the record at +0xF44, plus rowed SidesListNotifier posts at 0x0032B540
// for this (+0x10) and other with callback at 0x005CB279.
// Evidence: +0xF44 teamrec via rowed emptyTeams at 0x0032D05C and pinned
// clear at 0x0032C9C6; +0x10 notifier via SidesList layout; caller at
// 0x0032F117 in load at 0x0032F0AA passing a temp SidesList.

void Rva005CB279();

class TeamsInfoRec
{
public:
	void swap(TeamsInfoRec *other);
};

class SidesListNotifier
{
public:
	void post(void (*callback)(), void *owner, int other);
};

class SidesList
{
public:
	void rva0032B7A7(SidesList *other);

private:
	char m_pad00[0x10];
	SidesListNotifier m_notifier;
	char m_pad[0xF44 - 0x11];
	TeamsInfoRec m_teamrec;
};

void SidesList::rva0032B7A7(SidesList *other)
{
	m_teamrec.swap(&other->m_teamrec);
	m_notifier.post(Rva005CB279, this, (int)other);
	other->m_notifier.post(Rva005CB279, other, (int)this);
}
