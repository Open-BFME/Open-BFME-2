// cl: /O1 /MD
// stlport
//
// ?bfmeVal1038@BfmeY1038@@QAEHXZ retail 0x0040CF91, 54 B (the pin name its
// five callers use; WorldBuilder leaves its twin 0x0108B740 unnamed).
// Target evidence: sums, over the 8-byte entry vector at +0x40 (the same
// entries ArmySummary::GetEntry 0x0040CBD7 searches; size recomputed each
// pass), the int the rowed 0x0037DCA5 returns for each entry's held unit
// (WB CarryoverUnit::GetCommandPointSize). So an army's total command
// points; the owner keeps its placeholder name.
#include <vector>

class Rva0037DCA5
{
public:
	int rva0037DCA5();		// 0x0037DCA5
};

class Rva004F6093Holder
{
public:
	Rva0037DCA5 *get() const { return m_p; }
private:
	Rva0037DCA5 *m_p;
};

struct Rva0040CB3AEntry
{
	int m_key;
	Rva004F6093Holder m_holder;	// +0x04
};

class BfmeY1038
{
public:
	int bfmeVal1038();
private:
	char m_pad[0x40];
	std::vector<Rva0040CB3AEntry> m_entries;	// +0x40
};

int BfmeY1038::bfmeVal1038()
{
	int total = 0;
	for (unsigned int i = 0; i < m_entries.size(); ++i)
		total += m_entries[i].m_holder.get()->rva0037DCA5();
	return total;
}

// 0x0040CF55, 60 B: the same +0x40 entry vector, summing the field at +0x90
// of each held unit whose flag byte at +0xC5 is clear. The unit is
// address-derived (Rva0040CF55Unit); only its two field offsets are evidence.
class Rva0040CF55Unit
{
public:
	char m_pad0[0x90];
	int m_value;		// +0x90
	char m_pad1[0x31];
	unsigned char m_flag;	// +0xC5
};

class Rva0040CF55Holder
{
public:
	Rva0040CF55Unit *get() const { return m_p; }
private:
	Rva0040CF55Unit *m_p;
};

struct Rva0040CF55Entry
{
	int m_key;
	Rva0040CF55Holder m_holder;	// +0x04
};

class Rva0040CF55Owner
{
public:
	int sumUnflagged() const;
private:
	char m_pad[0x40];
	std::vector<Rva0040CF55Entry> m_entries;	// +0x40
};

int Rva0040CF55Owner::sumUnflagged() const
{
	int total = 0;
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		Rva0040CF55Unit *unit = m_entries[i].m_holder.get();
		if (!unit->m_flag)
			total += unit->m_value;
	}
	return total;
}
