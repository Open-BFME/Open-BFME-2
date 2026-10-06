// cl: /MD
// ?rva002A7AFE@PlayerList@@QAEXPAX@Z @0x002A7AFE 30B.
// PlayerList fan-out over 20 slots calling rowed armor remove. Evidence:
// chain lane via 0x002AD19E, prev PlayerList::reset same TU, push-imm 0x14
// pop-edi /O1 idiom, frameless dec-jne loop, returns void ret 4.
class Rva002AD19E
{
public:
	bool rva002AD19E(void *arg);
};
class PlayerList
{
	char _pad[24];
public:
	void rva002A7AFE(void *arg);
	Rva002AD19E *m_slots[20];
};
void PlayerList::rva002A7AFE(void *arg)
{
	Rva002AD19E **slot = m_slots;
	int count = 20;
	do {
		(*slot)->rva002AD19E(arg);
		++slot;
	} while (--count != 0);
}
