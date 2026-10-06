// cl: /MD
// ??1Rva00382B3F@@QAE@XZ @0x00382B3F 8B
// Dtor tail-jmp to rowed ??1BuddyInfo@@QAE@XZ at 0x003820FE; add ecx,4 then
// jmp. Member at +4 with 4B pad at +0; empty dtor lets compiler tail-call.
// Unblocks 0x0038404A 0x00383F9C; callers 0x003833FC etc.
struct BuddyInfo
{
	~BuddyInfo();
};

struct Rva00382B3F
{
	unsigned int m_00;
	BuddyInfo m_04;
	~Rva00382B3F();
};

Rva00382B3F::~Rva00382B3F()
{
}
