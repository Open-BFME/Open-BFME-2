// cl: /Oy- /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// 0x005CB432 (56B): a TU of its own because retail keeps a frame pointer for this body (/Oy-); the region
// default (/O1 /arch:SSE /G7) plus /Oy- is exact. RegionUI view as in VslotSmallBodiesW5SN4.cpp.
// Bank for 0x005CB432; RegionUI view as in Code/GameEngine/Source/Common/VslotSmallBodiesW5SN4.cpp
typedef int Int;
class Image; class UnicodeString;
class RegionUI {
public:
	virtual void v0();
	virtual void SetRegionImage(const Image *);
	virtual void v2();
	virtual void SetText(const UnicodeString &);
	virtual void SetPageCounts(Int enabled, Int total);
	virtual void SetUpgradeCounts(Int available, Int total);
	virtual void SetRegionValues(Int a, Int b);
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void SetVisibility(bool);
};

// 0x005CB432 (56B, register arguments, no direct reference): the owner's
// +0x170 pointer vector, counted by entries whose +0x20 word is set, feeds
// SetPageCounts(enabled, total).
struct Rva005CB432Entry
{
	char m_pad00[0x20];
	int m_enabled;
};
struct Rva005CB432Vector
{
	Int size() const { return m_finish - m_start; }
	Rva005CB432Entry *operator[](Int i) const { return m_start[i]; }
	Rva005CB432Entry **m_start;
	Rva005CB432Entry **m_finish;
	Rva005CB432Entry **m_end;
};
struct Rva005CB432Owner
{
	char m_pad000[0x170];
	Rva005CB432Vector m_entries;	// +0x170
};
void __fastcall updatePageCounts(RegionUI *ui, Rva005CB432Owner *owner)
{
	Int enabled = 0;
	Int total = owner->m_entries.size();
	for (Int i = 0; i < total; ++i)
		if (owner->m_entries[i]->m_enabled != 0)
			++enabled;
	ui->SetPageCounts(enabled, total);
}

