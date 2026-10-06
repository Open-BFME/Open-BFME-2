// cl: /MD
// ??1Rva0043283C@@QAE@XZ, retail 0x0043283C, 28 bytes.
// Dtor stores derived vtable 0x00C3CA28, clears singleton 0x00E032C8 if it holds this, stores base vtable 0x00BDBA74. Evidence: caller 0x00432A1F deleting dtor, base vtable RVA 0x007DBA74 matches BfmeOwnVVD base, singleton matches g_Va00E032C8.
class Rva0043283CBase
{
public:
	Rva0043283CBase() { }
	~Rva0043283CBase() { }
	virtual void rva0043283CSlot0();
};

class Rva0043283C : public Rva0043283CBase
{
public:
	~Rva0043283C();
};

extern int g_Va00E032C8;

Rva0043283C::~Rva0043283C()
{
	if (g_Va00E032C8 == (int)this)
		g_Va00E032C8 = 0;
}
