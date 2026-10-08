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
