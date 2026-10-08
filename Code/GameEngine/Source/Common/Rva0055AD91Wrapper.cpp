// cl: /MD
// ?registerWithBuilder@AIBuildable@@UAEXPAX_N@Z retail 0x0055AD91 41B: wrapper loads global 0x00DFEEF8 to get record for arg then clears +0x10 when flag byte 0 then adds this via rowed 0x004EC83F; evidence vtable slot 6 plus pin-rowed callees plus sibling 0x0055ADBA
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
};

class Rva004EC276
{
public:
	void rva004EC83F(void *x);
};

extern Rva002A8F24 *g_00DFEEF8;

// A virtual: slot 6 of nine retail vtables (0x00C6B900, 0x00C70BD0 of
// AIUpgrade, 0x00C765F8 of AIBuildableUnit, ...) that inherit it unchanged, as
// its WB twin is slot 6 of nine WB tables; +0x0 is the vptr.
class AIBuildable
{
public:
	virtual void registerWithBuilder(void *x, bool flag);
	char m_pad04[12];
	int m_10;
};

void AIBuildable::registerWithBuilder(void *x, bool flag)
{
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(x);
	if (!flag)
		m_10 = 0;
	((Rva004EC276 *)rec)->rva004EC83F(this);
}
