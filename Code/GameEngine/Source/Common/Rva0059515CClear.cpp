// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva0059515C@Rva0059515C@@QAEXXZ @0x0059515C 35B: clear 8 stride-0x1E slots at this+0x9E plus flag at this+0x17C after base clear. Evidence: calls rowed 0x0059510D ?rva0059510D@Rva0059510D@@QAEXXZ; callers 0x00595D0B 0x0059534A.
class Rva0059510D
{
public:
	void rva0059510D();
private:
	char m_data[0x54];
};

#pragma pack(push, 1)
struct Rva0059515CSlot
{
	unsigned int val;
	char _pad[0x1A];
};
#pragma pack(pop)

class Rva0059515C : public Rva0059510D
{
public:
	void rva0059515C();
private:
	char m_pad[0x4A];
	Rva0059515CSlot m_slots[8];
};

void Rva0059515C::rva0059515C()
{
	rva0059510D();
	*(unsigned int *)((char *)&m_slots[7] + 0xC) = 0;
	Rva0059515CSlot *p = m_slots;
	int n = 8;
	do {
		p->val = 0;
		++p;
	} while (--n != 0);
}
