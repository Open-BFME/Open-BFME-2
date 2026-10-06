// cl: /DNDEBUG /MD /EHs
// ??0Rva0055F218@@QAE@IAAUSrc0055F218@@@Z, retail 0x0055F218, 120 bytes.
// UInt-plus-template ctor: forwards the dword to the rowed base
// ??0Rva0055EFE1@@QAE@I@Z at 0x0055EFE1, subobject defaults at +0xC/+0x10/+0x14/+0x15,
// final vtables +0 0x00C1D1D4 plus +8 s_slot3E4first plus +0xC 0x00C1D1E4,
// float via rowed GameClientRandomVariable::getValue 0x002341A1, flag bytes
// from +0x3C/+0x3D. Same shape as sibling 0x005646BC. Caller at 0x003ACF96.

class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

class Rva0055EFE1
{
public:
	Rva0055EFE1(unsigned int a);
	~Rva0055EFE1();
private:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
};

extern const void *const g_00C1D1D4[];
extern const void *const g_00C1D1E4[];
extern const void *const g_00C1D1F4[];
extern "C" char s_slot3E4first;

struct Src0055F218
{
	char m_pad0[0x30];
	GameClientRandomVariable m_var30;
	unsigned char m_3C;
	unsigned char m_3D;
};

struct Rva0055F218Sub
{
	Rva0055F218Sub() : m_v((void *)g_00C1D1F4), m_f(0.0f), m_b14(0), m_b15(0) {}
	~Rva0055F218Sub();
	void *m_v;
	float m_f;
	unsigned char m_b14;
	unsigned char m_b15;
};

class Rva0055F218 : public Rva0055EFE1, public Rva0055F218Sub
{
public:
	Rva0055F218(unsigned int a, struct Src0055F218 &src);
	~Rva0055F218();
};

Rva0055F218::Rva0055F218(unsigned int a, struct Src0055F218 &src)
	: Rva0055EFE1(a), Rva0055F218Sub()
{
	*(void **)this = (void *)g_00C1D1D4;
	*(void **)((char *)this + 8) = (void *)&s_slot3E4first;
	m_v = (void *)g_00C1D1E4;
	float v = src.m_var30.getValue();
	m_f = v;
	m_b14 = src.m_3C;
	m_b15 = src.m_3D;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C1D1F4@@3QBQBXB=??_7Rva003ADE98@@6B@")
