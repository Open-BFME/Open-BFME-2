// cl: /O1 /MD
//
// ?GetEntry@ArmySummary@@QAE?AUArmySummaryEntryRef@@H@Z retail 0x0040CBD7, 55 B.
// Name: WorldBuilder's ArmySummary::GetEntry at the same call sites (the pin
// its callers use). Target evidence: binary-searches the 8-byte entry array
// at +0x40 (rowed 0x0040CB3A); a miss returns a null holder, a hit returns a
// copy of the entry's holder at +0x04 through the rowed copy constructor
// 0x004F6093. The two returns of a class with a destructor give retail's
// return-value flag at [ebp-4].
class Rva004F6093Holder
{
public:
	Rva004F6093Holder() : m_p(0) {}
	Rva004F6093Holder(const Rva004F6093Holder &that);	// 0x004F6093
	~Rva004F6093Holder();
private:
	void *m_p;
};

struct ArmySummaryEntryRef
{
	ArmySummaryEntryRef() {}
	ArmySummaryEntryRef(const Rva004F6093Holder &h) : m_holder(h) {}
	Rva004F6093Holder m_holder;
};

struct Rva0040CB3AEntry
{
	int m_key;
	Rva004F6093Holder m_holder;	// +0x04
};

// The ledger rows the binary search 0x0040CB3A on this same object under a
// placeholder view (Rva0040CB3ABinarySearch.cpp).
class Rva0040CB3AIndexedField
{
public:
	int find(int key) const;		// 0x0040CB3A
};

class ArmySummary
{
public:
	ArmySummaryEntryRef GetEntry(int key);
private:
	char m_pad[0x40];
	Rva0040CB3AEntry *m_begin;		// +0x40
	Rva0040CB3AEntry *m_end;		// +0x44
};

ArmySummaryEntryRef ArmySummary::GetEntry(int key)
{
	int index = ((const Rva0040CB3AIndexedField *)this)->find(key);
	if (index < 0)
		return ArmySummaryEntryRef();
	return ArmySummaryEntryRef(m_begin[index].m_holder);
}
