// cl: /O1 /MD
//
// ?GetEntry@ArmySummary@@QAE?AUArmySummaryEntryRef@@H@Z retail 0x0040CBD7, 55 B.
// Name: WorldBuilder's ArmySummary::GetEntry at the same call sites (the pin
// its callers use). Target evidence: binary-searches the 8-byte entry array
// at +0x40 (rowed 0x0040CB3A); a miss returns a null holder, a hit returns a
// copy of the entry's holder at +0x04 through the rowed copy constructor
// 0x004F6093. The two returns of a class with a destructor give retail's
// return-value flag at [ebp-4].
class ArmySummaryEntry
{
public:
	void ApplyWorldMapUpgrades();		// 0x0040C6A5
private:
	char m_pad[0xBC];
public:
	int m_bc;				// +0xBC, gates ApplyWorldMapUpgrades
};

class Rva004F6093Holder
{
public:
	ArmySummaryEntry *get() const { return (ArmySummaryEntry *)m_p; }
	Rva004F6093Holder() : m_p(0) {}
	Rva004F6093Holder(const Rva004F6093Holder &that);	// 0x004F6093
	~Rva004F6093Holder();
private:
	void *m_p;
};

struct ArmySummaryEntryRef
{
 __declspec(dllimport) __forceinline ~ArmySummaryEntryRef() {}

	ArmySummaryEntryRef() {}
	ArmySummaryEntryRef(const Rva004F6093Holder &holder) : m_holder(holder) {}
	Rva004F6093Holder m_holder;
};

struct Rva0040CB3AEntry
{
	int m_key;
	Rva004F6093Holder m_holder;	// +0x04
};

// The ledger rows the binary search 0x0040CB3A on this same object under a
// placeholder view (Rva0040CB3ABinarySearch.cpp).
struct Rva0040CB3AEntryArray
{
	unsigned int size() const { return m_end - m_begin; }
	Rva0040CB3AEntry &operator[](unsigned int i) { return m_begin[i]; }
	Rva0040CB3AEntry *m_begin;		// +0x40
	Rva0040CB3AEntry *m_end;		// +0x44
};

class Rva0040CB3AIndexedField
{
public:
	int find(int key) const;		// 0x0040CB3A
};

class ArmySummary
{
public:
	ArmySummaryEntryRef GetEntry(int key);
	void rva0040CC8F();
private:
	char m_pad[0x40];
	Rva0040CB3AEntryArray m_entries;	// +0x40
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline ArmySummaryEntryRef ArmySummary::GetEntry(int key)
{
	int index = ((const Rva0040CB3AIndexedField *)this)->find(key);
	if (index < 0)
		return ArmySummaryEntryRef();
	return ArmySummaryEntryRef(m_entries.m_begin[index].m_holder);
}

// ?bfmeAnchorArmySummaryGetEntry absent-from-retail
ArmySummaryEntryRef bfmeAnchorArmySummaryGetEntry(ArmySummary *armySummary, int key)
{
	return armySummary->GetEntry(key);
}


// ?rva0040CC8F@ArmySummary@@QAEXXZ retail 0x0040CC8F, 55 B. WorldBuilder's
// twin 0x01089620 is unnamed. Every entry whose +0xBC is set gets its
// ArmySummaryEntry::ApplyWorldMapUpgrades (rowed 0x0040C6A5); the entry
// count is re-read from the +0x40/+0x44 array each pass; modelling that
// array as a subobject with inline size()/operator[] gives retail's reloads.
void ArmySummary::rva0040CC8F()
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		ArmySummaryEntry *entry = m_entries[i].m_holder.get();
		if (entry->m_bc)
			entry->ApplyWorldMapUpgrades();
	}
}

// ?rva003191DA@Rva003191DAOwner@@QAEXXZ @0x003191DA 8B: loads the ArmySummary pointer held at +0x78, then tail-jumps ArmySummary::rva0040CC8F above.
// Owner and name are address-derived; no referencing site was found in this
// pass.
class Rva003191DAOwner
{
public:
	void rva003191DA();
private:
	char m_pad00[0x78];
	ArmySummary *m_summary78;
};

void Rva003191DAOwner::rva003191DA()
{
	m_summary78->rva0040CC8F();
}
