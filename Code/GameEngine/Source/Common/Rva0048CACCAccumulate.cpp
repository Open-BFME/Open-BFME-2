// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0048CACC@Rva0048CACC@@QAEXPAURva0048CACCArg@@@Z @0x0048CACC 76B ret 4.
// testStatus(0xA) on the object at this-0x18. While the limit at
// [this-0x1C]+0x1C is still above the accumulator, add arg+0x20. Crossing
// the limit calls apply on this-0x20 and snaps the accumulator to the limit.

enum ObjectStatusTypes
{
	OS_A = 0xA
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
};

class FlameCleanup00293E50
{
public:
	void apply();
};

struct Rva0048CACCArg
{
	char m_pad[0x20];
	float m_add;
};

struct Rva0048CACCThing
{
	char m_pad[0x1C];
	float m_limit;
};

class Rva0048CACC
{
public:
	void rva0048CACC(Rva0048CACCArg *arg);

private:
	char m_pad[0x18];
	float m_acc;
};

void Rva0048CACC::rva0048CACC(Rva0048CACCArg *arg)
{
	Object *obj = *(Object **)((char *)this - 0x18);
	if (obj->testStatus(OS_A) == 0)
		return;
	Rva0048CACCThing *thing = *(Rva0048CACCThing **)((char *)this - 0x1C);
	if (thing->m_limit > m_acc)
	{
		m_acc += arg->m_add;
		if (m_acc >= thing->m_limit)
		{
			((FlameCleanup00293E50 *)((char *)this - 0x20))->apply();
			*(unsigned int *)&m_acc = *(unsigned int *)&thing->m_limit;
		}
	}
}
