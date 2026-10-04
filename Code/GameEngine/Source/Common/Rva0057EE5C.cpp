// cl: /O1 /DNDEBUG /MD /GX
// ??1Rva0057EE5C@@UAE@XZ @0x0057EE5C 141B
// Evidence: unlock dtor stores vtable 0x0086F4F0 frees +0xB4 +0x7C +0x70 +0x64 via rowed _free 0x00030830 releases +0x58 via rowed fastcall ReleaseTreeHintRef 0x0007DEEF then pinned base dtor 0x005248D0. Callers 0x0044227B 0x0057EEF1 0x0043DAC3. Prev VectorObjectIDFillInsert next Rva0057F2DE.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

extern "C" void __cdecl free(void *ptr);

struct FreeHolder0057EE5C
{
	char *m_ptr;
	~FreeHolder0057EE5C()
	{
		if (m_ptr)
			free(m_ptr);
	}
};

struct ReleaseHolder0057EE5C
{
	TargetRef00217D4C *m_ptr;
	~ReleaseHolder0057EE5C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva0057EE5C : public Rva005248D0
{
public:
	virtual ~Rva0057EE5C();
private:
	char m_pad04[0x58 - 4];
	ReleaseHolder0057EE5C m_58;
	char m_pad5C[0x64 - 0x5C];
	FreeHolder0057EE5C m_64;
	char m_pad68[0x70 - 0x68];
	FreeHolder0057EE5C m_70;
	char m_pad74[0x7C - 0x74];
	FreeHolder0057EE5C m_7C;
	char m_pad80[0xB4 - 0x80];
	FreeHolder0057EE5C m_B4;
};

Rva0057EE5C::~Rva0057EE5C()
{
}
