// cl: /MD
// ?get@Rva002E3A8DHolder@@QAEPAURva002E3A8DPair@@PAU2@H@Z, retail 0x002E3A8D, 27 bytes.
// Target evidence: leaf; returns the destination pointer in EAX (retail's tail
// leaves out in EAX), which is what pins the void-vs-pointer signature. Next
// body is ?call@Rva002E3A80Holder@@QAEXXZ at 0x002E3A80, so the owning class is
// the same address-named holder. No donor.
struct Rva002E3A8DPair
{
	float m_x;
	int m_y;
};
struct Rva002E3A8DHolder
{
	unsigned char m_pad[8];
	Rva002E3A8DPair *m_array;
	Rva002E3A8DPair *get(Rva002E3A8DPair *out, int index);
};
Rva002E3A8DPair *Rva002E3A8DHolder::get(Rva002E3A8DPair *out, int index)
{
	Rva002E3A8DPair *slot = &m_array[index];
	out->m_x = slot->m_x;
	out->m_y = slot->m_y;
	return out;
}
