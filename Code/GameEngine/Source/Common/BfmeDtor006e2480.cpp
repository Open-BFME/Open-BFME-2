// cl: /O1 /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeDtor006e2480.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Gen006E2310::~Gen006E2310 0x00095360 (83B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

class BfmeRef006e2480
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}

private:
	int m_refs;
};

// 0X012F8048 is retail's global dword (?g_get_00710fb0@@3HA, defined in
// W3DDevice/GameClient/Gen_00710fb0_Global.cpp).  Retail reloads it each
// time, so this TU reads and writes it as the pointer it holds.
extern int g_get_00710fb0;
#define g_bfmeObj006e1be0 (*reinterpret_cast<BfmeRef006e2480 **>(&g_get_00710fb0))

class Gen_dtor_0040ba10
{
public:
	virtual ~Gen_dtor_0040ba10(void);
};

class Gen006E2310 : public Gen_dtor_0040ba10
{
public:
	virtual ~Gen006E2310(void);
};

// ??1Gen006E2310@@UAE@XZ
Gen006E2310::~Gen006E2310(void)
{
	if (g_bfmeObj006e1be0)
	{
		g_bfmeObj006e1be0->Release_Ref();
		g_bfmeObj006e1be0 = 0;
	}
}
