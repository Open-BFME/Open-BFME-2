// cl: /EHs /MD
// ??1Rva0053FB33@@UAE@XZ, retail 0x0053FB33, 66 bytes.
// Virtual dtor: installs vtable 0x008694DC, destroys StringBase<char> at
// +0x18 via rowed releaseBuffer 0x00036410, frees heap pointer at +4 via
// rowed _free 0x00030830, with __EH_prolog frame 0x00629188. Same EH plus
// releaseBuffer shape as Rva003F0C6CDtor (53B, two StringBases). Evidence:
// vtable store plus lea ecx [esi+0x18] plus free branch; ctor sibling at
// 0x0053FAB7 installs same vtable; deleting-dtor candidate at 0x0053FB75
// calls here then operator delete.
extern "C" void __cdecl free(void *block);

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct Rva0053FB33Holder
{
	~Rva0053FB33Holder() { if (m_ptr != 0) free(m_ptr); }
	void *m_ptr;
};

class Rva0053FB33
{
public:
	virtual ~Rva0053FB33();
private:
	Rva0053FB33Holder m_holder04;
	char m_pad08[0x18 - 0x08];
	StringBase<char> m_str18;
};

Rva0053FB33::~Rva0053FB33()
{
}
