// ?rva001F3828@Rva001F3828@@QAE_NHH@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva001F3828@Rva001F3828@@QAE_NHH@Z @0x001F3828 34B.
// Guarded forward: asks TheGameClient (global 0x00DFE77C, GameClient view
// per GameLogicBindObjectAndDrawable) slot 0x40 for the +0xB0 key; on null
// returns false, else tail-jumps to the unrowed thiscall at 0x002788C7 on
// the returned object (pinned from the emitted spelling) and returns its
// bool. Two dead int params (ret 8, never read; virtual-override shape
// unproven). Strict key/result types unproven.
class GameClient
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void *slot0x40(int key);
};

extern GameClient *TheGameClient;

struct Rva002788C7Obj
{
	bool rva002788C7();
};

class Rva001F3828
{
public:
	bool rva001F3828(int a, int b);
private:
	char m_pad00[0xB0];
	int m_keyB0;
};

bool Rva001F3828::rva001F3828(int a, int b)
{
	(void)a;
	(void)b;
	Rva002788C7Obj *o = (Rva002788C7Obj *)TheGameClient->slot0x40(m_keyB0);
	if (o == 0)
		return false;
	return o->rva002788C7();
}
