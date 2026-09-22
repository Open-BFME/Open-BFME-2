// ?bfmeQuery932C@BfmeSub932C@@QAEEXZ, retail 0x004D7383, 18 bytes.
// Nullable-delegate query: when the +0x4 sub-chain is present the answer comes
// from its 16th virtual (slot 0x3C); otherwise the +0x3A fallback byte answers.
// The sub family is unrowed (its slot-15 bodies live at 0x0033F504 and
// 0x003412A5, both unclaimed), so the chain is modelled on BfmeSub932C itself
// with declared-only placeholder virtuals (TurretAI_removeSelfAsTargeter
// precedent: declared-only and never constructed, so no vtable is emitted).
// Shard TU on purpose: BfmeConv932.cpp's rowed bfmeGo932C calls this body, and
// a visible definition there would reschedule its caller (Bucket new law).
// /O1 is load-bearing: size-opt emits the cmp-mem head plus the reload tail,
// while /O2 forwards the load (mov eax plus test, no reload).
// cl: /O1

class BfmeSub932C
{
public:
	virtual void _slot000();
	virtual void _slot001();
	virtual void _slot002();
	virtual void _slot003();
	virtual void _slot004();
	virtual void _slot005();
	virtual void _slot006();
	virtual void _slot007();
	virtual void _slot008();
	virtual void _slot009();
	virtual void _slot010();
	virtual void _slot011();
	virtual void _slot012();
	virtual void _slot013();
	virtual void _slot014();
	virtual unsigned char _slot015();

	unsigned char bfmeQuery932C();

	BfmeSub932C *m_bfmeSub;
	unsigned char m_bfmePad[0x32];
	unsigned char m_bfmeFallback;
};

unsigned char BfmeSub932C::bfmeQuery932C()
{
	if (m_bfmeSub != 0)
		return m_bfmeSub->_slot015();
	return m_bfmeFallback;
}
