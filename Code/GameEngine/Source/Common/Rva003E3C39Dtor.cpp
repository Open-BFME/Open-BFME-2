// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva003E3C39@@UAE@XZ @0x003E3C39 (27B): virtual dtor storing vtable 0x00835B34
// then deleting +0x04 member via its slot0(0) plus operator delete. Evidence:
// vtable store at [this] unlocks 0x003E54F7 caller 0x003E54FA rowed operator
// delete 0x0002FD60 neighbours Disp8CmpBoolGetters and evaluateBridgeBroken.
class Rva003E3C39Interface
{
public:
	virtual void *slot0(int flag);
};

class Rva003E3C39
{
public:
	virtual ~Rva003E3C39();

private:
	Rva003E3C39Interface *m_04;
};

extern const void *const g_00C35B34[];

Rva003E3C39::~Rva003E3C39()
{
	if (m_04) {
		void *p = m_04->slot0(0);
		::operator delete(p);
	}
}
