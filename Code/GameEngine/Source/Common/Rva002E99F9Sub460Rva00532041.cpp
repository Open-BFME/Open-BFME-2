// cl: /O1 /arch:SSE /G7 /Os
// ?rva00532041@Rva002E99F9Sub460@@QAEGHHHPAPAURva00532041Record@@@Z @0x00532041 40B
// Banked attempt reverse/attempts/0x00532041.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

// Target evidence: 0x00532041 indexes a pointer table and a 16-byte record,
// loads the word at record+8, and passes it with the original context through
// 0x00531FE6. The helper receives the same ECX value and its return stays in
// EAX through the caller's ret 0x10. The record's meaning is unknown.
// This class association is inferred from the same-this sibling thunk at
// 0x0053241F, which forwards to 0x00531FE6; the original owner identity remains
// unproven.

struct Rva00532041Record
{
	char m_prefix[8];
	unsigned short m_value;
	char m_suffix[6];
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva00531FE6(int mode, int context, unsigned short value);
	unsigned short rva00532041(int context, int tableIndex, int recordIndex,
		Rva00532041Record **records);
};

unsigned short Rva002E99F9Sub460::rva00532041(
	int context, int tableIndex, int recordIndex, Rva00532041Record **records)
{
	Rva00532041Record *record = records[tableIndex];
	unsigned short value = record[recordIndex].m_value;
	return rva00531FE6(0, context, value);
}
