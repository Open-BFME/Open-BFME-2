// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6DC4@Rva002E6DC4@@QAE_NPAX0@Z @0x002E6DC4 168B.
// Honest address name: unclaimed __thiscall predicate with 32 callers and no
// donor string vtable or export to prove a real identity. Byte-exact model:
// bool method on honest Rva002E6DC4 (void* +0x48) taking two void* args,
// ret 8 proves 2 stack args, test al,al in callers proves byte bool return.
// Evidence: UNCLAIMED callers e.g. 0x002E7D6D 0x002E85AD; callees none;
// prev/next are Disp getters in the same Common dir; flags /O1 from
// Rva002E6ECAGet sibling with the same xor/mov al and cmp-imm8 idioms.
// Switch on (flags&0xF) gives sub/dec for cases 3/4; (unsigned char)(flags>>N)
// truncation forces retail mov/shr/test-cl-1 idiom for bits 18/17/22.

class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
private:
	char m_pad[0x48];
	void *m_48;
};
struct Rva002E6DC4_P1
{
	unsigned int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
struct Rva002E6DC4_P2Inner
{
	char m_pad[0x28];
	void *m_28;
};
struct Rva002E6DC4_P2
{
	Rva002E6DC4_P2Inner *m_0;
	char m_pad4[8];
	unsigned int m_C;
};
// g_00DBD33C: VA 0x00DBD33C (.data); exact retail initial dwords below.
unsigned int g_00DBD33C[16] = {
	0x00000009, 0x0000000A, 0x0000000C, 0x00000018,
	0x00000028, 0x00000048, 0x00000048, 0x00000088,
	0x00000000, 0x3E490FDB, 0x41A00000, 0x41A00000,
	0x00000000, 0x00000001, 0x00000000, 0xFFFFFFFF
};
bool Rva002E6DC4::rva002E6DC4(void *a_raw, void *b_raw)
{
	Rva002E6DC4_P1 *a = (Rva002E6DC4_P1 *)a_raw;
	Rva002E6DC4_P2 *b = (Rva002E6DC4_P2 *)b_raw;
	if (!b)
		return false;
	unsigned int flags = b->m_C;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0 && a->m_5 != 0)
		return false;
	unsigned int low = flags & 0xF;
	switch (low) {
	case 3:
		if ((flags & 0x3F0) != 0x10)
			return false;
		break;
	case 4: {
		void *chase = b->m_0 ? b->m_0->m_28 : 0;
		if (chase == m_48)
			return true;
		break;
	}
	default:
		break;
	}
	if ((a->m_0 & g_00DBD33C[low]) == 0)
		return false;
	unsigned char b17 = (unsigned char)(flags >> 17);
	if (a->m_4 != 0 && (b17 & 1) != 0)
		return false;
	if (a->m_C != 0) {
		unsigned char b22 = (unsigned char)(flags >> 22);
		if (((b22 & 1) == 0) && low == 4)
			return false;
	}
	int v = a->m_8;
	if (v < 0 || (int)((flags >> 19) & 3) <= v)
		return true;
	return false;
}
