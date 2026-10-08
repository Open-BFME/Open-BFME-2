// cl: -GR- -EHsc-
// ?Run@Rva005A5B38Box@@QAE_NXZ @0x005A5B38 119B: flag-gated refresh toggle.
// When +0x4A0 is set, clear it, resolve the display name through the box's
// own slot-0x28 virtual, and issue the rowed AptCall (manager global, the
// +0x274 key, the name, the opaque runtime constant); else refresh through
// the pinned thiscall 0x5A51B9, stamp +0x488, snapshot timeGetTime, set
// +0x4A0 and return true.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
extern const char g_rva005A5B38Const[];

struct Rva005A5B38Helper
{
	int m_0;
	int m_4;
	char pad[4];
	void *m_C;
};

struct Rva005A5B38Box
{
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual const char *GetName();

	void DoRefresh(int tag, void *ctx);
	bool Run();

	char pad[0x58 - 4];
	void *m_58;
	char pad2[0x488 - 0x5c];
	int m_488;
	char pad3[0x4a0 - 0x48c];
	unsigned char m_4A0;
	char pad4[7];
	unsigned int m_4A8;
	char pad5[0x4dc - 0x4ac];
	unsigned int m_4DC;
};

bool Rva005A5B38Box::Run()
{
	void *obj = m_58;
	if (m_4A0 != 0) {
		m_4A0 = 0;
		void *key = *(void **)((char *)obj + 0x274);
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), key, GetName(), g_rva005A5B38Const);
		return false;
	}
	Rva005A5B38Helper *h = (Rva005A5B38Helper *)((char *)m_58 + 0x298);
	void *ctx = &h->m_C;
	DoRefresh(h->m_4, ctx);
	m_488 = 0xd;
	unsigned long stamp = timeGetTime();
	m_4A8 |= -1;
	m_4DC = stamp;
	m_4A0 = 1;
	return true;
}
