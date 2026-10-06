// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Bfme/Rva0094D8B0Reset.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?reset@Rva0094D8B0@@QAE_NXZ 0x00171522 (30B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Structural recovery for the reset/delegate body at retail 0x0094D8B0.

void d_0094d450(void);

class Rva0094D8B0Delegate
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void slot4(void);
	virtual void slot5(void);
	virtual void slot6(void);
	virtual void slot7(void);
	virtual void slot8(void);
	virtual void slot9(void);
	virtual bool tail(void);
};

class Rva0094D8B0
{
public:
	bool reset(void);

private:
	unsigned char m_prefix[0x18];
	Rva0094D8B0Delegate *m_delegate;
	unsigned char m_reset;
};

bool Rva0094D8B0::reset(void)
{
	if (m_reset != 0)
		d_0094d450();
	Rva0094D8B0Delegate *delegate = m_delegate;
	if (delegate != 0)
		return delegate->tail();
	return false;
}
