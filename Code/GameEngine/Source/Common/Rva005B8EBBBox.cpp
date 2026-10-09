// cl: -O1 -GR- -EHsc-
// ?Run@Rva005B8EBB@@QAEXXZ @0x005B8EBB 73B: dispatch + tail.
// Calls the +0x60 sub-object helper (rowed 0x5DE96B) and the +0x58 object
// helper (pinned 0x517F31), switches m_8C 0/1/2 to the pinned trio
// (0x5B8D1C/0x5B89A1/0x5B8A40), then tailcalls the pinned 0x5DD48C on the
// +0x60 sub-object. Targets from retail REL32; names unknown.
// Native+60 subobject is AptStats; call its sole recovered refresh owner.
class AptStats {public:void rva005DD48C();};
class Rva005DE96B
{
public:
	void rva005DE96B();
};

struct Rva005B8EBB
{
	char pad[0x58];
	void *m_58;
	char pad2[0x60 - 0x58 - 4];
	char m_60[0x8C - 0x60];
	int m_8C;

	void rva00517F31();
	void rva005B8D1C();
	void rva005B89A1();
	void rva005B8A40();

	void Run();
};

void Rva005B8EBB::Run()
{
	((Rva005DE96B *)((char *)this + 0x60))->rva005DE96B();
	((Rva005B8EBB *)m_58)->rva00517F31();
	switch (m_8C) {
	case 0:
		rva005B8D1C();
		break;
	case 1:
		rva005B89A1();
		break;
	case 2:
		rva005B8A40();
		break;
	}
	((AptStats *)((char *)this + 0x60))->rva005DD48C();
}
