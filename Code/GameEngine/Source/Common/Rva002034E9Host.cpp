// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002034E9@Rva002034E9Host@@QAE_NXZ at retail 0x002034E9 (25B).
// Returns true when this+0x114 != 3, else the rowed callee on the same this.
// Target evidence: cmp [ecx+0x114],3; jne true; call
// ?rva0023C6A4@Rva0023C6A4@@QAE_NXZ; test al,al; jne true; xor eax,eax;
// ret; true: xor eax,eax; inc eax; ret. Callers (e.g. 0x00293687) pass
// TheGameLogic in ecx and test al. +0x114 matches GameLogic m_unk114
// (GameLogicModeGateChecks.cpp); owner unproven so honest Rva host,
// same family as Rva0023C6A4Check.cpp.

typedef bool Bool;

class Rva0023C6A4
{
public:
	Bool rva0023C6A4();
};

class Rva002034E9Host
{
public:
	Bool rva002034E9();

private:
	char m_pad[0x114]; // +0x00..0x114
	int m_field114; // +0x114
};

Bool Rva002034E9Host::rva002034E9()
{
	return m_field114 != 3 || ((Rva0023C6A4 *)this)->rva0023C6A4();
}
