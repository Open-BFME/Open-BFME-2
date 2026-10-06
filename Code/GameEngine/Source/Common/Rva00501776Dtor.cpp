// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva00501776@@QAE@XZ @0x00501776 54B: dtor destroying vectors at +0x14/+0x20
// via rowed ??1Rva005011DA@@QAE@XZ (Code/GameEngine/Source/Common/RvaVectorDtorFamily.cpp).
// Evidence: retail calls 0x005011DA twice with ecx=esi+0x20 then esi+0x14 under
// __EH_prolog with EH state clear/set; callers at 0x00501838/0x00501869/0x005019E8
// reach here; no vptr store so non-virtual.

struct Rva005011DA
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva005011DA();
};

struct Rva00501776
{
	char m_pad[0x14];
	Rva005011DA m_a;
	Rva005011DA m_b;
	~Rva00501776();
};

Rva00501776::~Rva00501776()
{
}

// ??1Rva005017AC@@QAE@XZ @0x005017AC 8B: outer dtor tail-jmps to ??1Rva00501776
// after shifting this by +4. Evidence: retail is add ecx 4 plus jmp 0x00501776;
// deleting-dtor caller at 0x00501D96 calls here then operator delete 0x0002FD60.
struct Rva005017AC
{
	int m_head;
	Rva00501776 m_mid;
	~Rva005017AC();
};

Rva005017AC::~Rva005017AC()
{
}
