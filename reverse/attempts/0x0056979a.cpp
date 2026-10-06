// ?rva0056979A@Rva00569543@@QAEXPBUFloatPair@@I@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD
//
// ?rva0056979A@Rva00569543@@QAEXPBUFloatPair@@I@Z @0x0056979A 93B.
// Per-slot cell probe: for each non-null +0x2C slot, copy the two floats at
// the argument pair to the outgoing 8B struct slot and call pinned 0x005C8176
// (thiscall float-pair cell lookup, SSE body); a non-null cell runs rowed
// 0x005C884D on the tag then rowed Rva00569543::rva005695F2 sorted insert of
// the cell. Counter and this spill to [ebp-4]/[ebp-8] under register
// pressure. Honest address-derived names.
class ModuleData;

struct FloatPair
{
	float m_0;
	float m_4;
};

class Rva005C8176
{
public:
	void *rva005C8176(FloatPair p);
};

class Rva005C884D
{
public:
	void rva005C884D(unsigned short val);
};

class Rva00569543
{
public:
	void rva005695F2(const ModuleData *m);
	void rva0056979A(const FloatPair *p, unsigned tag);
private:
	char m_pad[0x2C];
	Rva005C8176 *m_slots[4];	// +0x2C
};

void Rva00569543::rva0056979A(const FloatPair *p, unsigned tag)
{
	Rva005C8176 **slot = m_slots;
	int left = 4;
	do {
		if (*slot != 0) {
			void *cell = (*slot)->rva005C8176(*p);
			if (cell != 0) {
				((Rva005C884D *)cell)->rva005C884D((unsigned short)tag);
				rva005695F2((const ModuleData *)cell);
			}
		}
		++slot;
	} while (--left != 0);
}
