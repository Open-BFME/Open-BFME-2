// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004F6234@Rva004F6234@@QAEXHPAUPred004F6234@@@Z, retail 0x004F6234, 52 bytes.
// Thiscall predicate loop over slot vectors: slot = m_slots[idx], iterate begin..end step 4 calling pred virtual.
// Evidence: stride 0xC imul; offsets +0xC/+0x10 begin/end; virtual call via [edx] with ecx=pred; callers 0x005EAA9C 0x005EAB20 0x005EABD9.
struct Pred004F6234
{
	virtual bool Check(int val);
};

class Rva004F6234
{
public:
	void rva004F6234(int idx, Pred004F6234 *pred);
private:
	char _00[12];
	struct Slot
	{
		int *m_begin;
		int *m_end;
		int m_pad;
	} m_slots[2];
};

void Rva004F6234::rva004F6234(int idx, Pred004F6234 *pred)
{
	int *first = m_slots[idx].m_begin;
	int *last = m_slots[idx].m_end;
	for (; first != last; ++first)
	{
		int v = *first;
		if (!pred->Check(v))
			break;
	}
}
