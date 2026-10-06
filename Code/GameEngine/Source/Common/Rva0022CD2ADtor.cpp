// cl: /MD /EHs
// ??1Rva0022CD2A@@QAE@XZ @0x0022CD2A 59B
// Non-virtual dtor over pointer-holder at +0 (inline free of [esi] via
// rowed _free 0x00030830) and rowed member ??1Rva002268B0@@QAE@XZ at +0xC.
// Retail calls the +0xC dtor first (lea ecx [esi+0xC] call 0x0022C64A) then
// frees [esi] under the same __EH_prolog shape as the rowed 0x0022C64A
// (same cookie 0xb6f893): and [ebp-4] 0 before the call, or [ebp-4] -1
// after. Evidence: unlock packet calls rowed 0x0022C64A and rowed free
// 0x00030830; callers at 0x0022D0E8 0x0022D94A 0x004142F5 and jmps at
// 0x0022D28B 0x00786006; unblocks 0x0022D941 0x0022D0E5 0x0041428F.
extern "C" void __cdecl free(void *block);

class Rva002268B0
{
public:
	~Rva002268B0();
};

struct Rva0022CD2AHead
{
	void *m_ptr;
	~Rva0022CD2AHead()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

class Rva0022CD2A
{
public:
	~Rva0022CD2A();
private:
	Rva0022CD2AHead m_head;
	int m_unk04;
	int m_unk08;
	Rva002268B0 m_item;
};

Rva0022CD2A::~Rva0022CD2A()
{
}
