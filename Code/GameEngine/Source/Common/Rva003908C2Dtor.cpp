// ??1Rva003908C2@@UAE@XZ
// partial score=0.96 date=2026-09-30
// cl: /DNDEBUG /MD /EHs
//
// ??1Rva003908C2@@UAE@XZ, retail 0x003908C2, 79 bytes.
// Evidence: vtable 0x00819F74 plus s_secondary0C at +0x0C plus g_00C19F68
// at +0x10 plus _free of +0x20 via rowed 0x00030830 plus base dtor
// ??1Rva0024A797 rowed 0x0024A797; EH prolog 0x00629188; caller 0x003909DE.
// MI fix: three vptrs are implicit via two empty polymorphic bases, moving and-ebp-4-0 late after load.
extern "C" void __cdecl free(void *block);

class Rva0024A797
{
public:
	virtual ~Rva0024A797();
protected:
	char m_pad[8];
};

class MiBase1
{
public:
	virtual void f1() = 0;
};

class MiBase2
{
public:
	virtual void f2() = 0;
};

class Rva003908C2 : public Rva0024A797, public MiBase1, public MiBase2
{
public:
	virtual ~Rva003908C2();
private:
	char m_pad14[0x20 - 0x14];
	void *m_p20;
};

Rva003908C2::~Rva003908C2()
{
	if (m_p20)
		free(m_p20);
}
