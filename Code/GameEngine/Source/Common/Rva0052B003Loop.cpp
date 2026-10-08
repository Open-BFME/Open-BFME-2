// cl: /MD
// ?rva0052B003@Holder0052B003@@QAEXH@Z @0x0052B003 33B
// Pointer-range loop: for each Obj* from +0x2C to +0x30 call pinned
// 0x005C4180 with the int arg.
// The ledger row at 0x005C4180 is Rva005C41C9::rva005C4180(unsigned char).
class Rva005C41C9
{
public:
	void rva005C4180(unsigned char value);
};

struct Obj0052B003
{
};

struct Holder0052B003
{
	char m_pad[0x2C];
	Obj0052B003 **m_2C; // +0x2C
	Obj0052B003 **m_30; // +0x30
	void rva0052B003(int value);
};

void Holder0052B003::rva0052B003(int value)
{
	Obj0052B003 **begin = m_2C;
	Obj0052B003 **end = m_30;
	for (Obj0052B003 **p = begin; p != end; ++p)
		((Rva005C41C9 *)*p)->rva005C4180((unsigned char)value);
}
