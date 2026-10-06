// cl: /EHs /MD
// ??1Rva005407C9@@QAE@XZ @0x005407C9 65B inner dtor.
// Retail frees +0x10 then +0 via rowed _free with __EH_prolog frame.
// Evidence: unlock lane; caller 0x0054080A lea ecx [esi+0x24] then base
// ??1Rva0053FB33@@UAE@XZ; pattern copied from Rva0053FB33Dtor TU.
extern "C" void __cdecl free(void *block);

struct Rva005407C9Holder
{
	~Rva005407C9Holder() { if (m_ptr != 0) free(m_ptr); }
	void *m_ptr;
};

class Rva005407C9
{
public:
	~Rva005407C9();
private:
	Rva005407C9Holder m_00;
	unsigned char m_pad[0x10 - 0x04];
	Rva005407C9Holder m_10;
};

Rva005407C9::~Rva005407C9()
{
}
