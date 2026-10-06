// cl: /MD /DNDEBUG
//
// W3DModelDraw::setShadowsEnabled (retail 0x000B2E29, 30 bytes) and
// W3DModelDraw::releaseShadows (0x000B2E14, 21 bytes), ported from Zero
// Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DModelDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slots 12 and 13 of the W3DModelDraw-family vtable 0x00BCBFC0
// (slot-2 name getter returns "W3DSupplyDraw"), right after the 1563-byte
// doDrawModule in slot 11, as in Zero Hour's DrawModule order
// (doDrawModule, setShadowsEnabled, releaseShadows, allocateShadows).
// Layout (target evidence): m_fullyObscuredByShroud +0x49 (the rowed
// setFullyObscuredByShroud), m_shadowEnabled +0x4A, m_shadow +0x58; the
// shadow's enable flag is +0x04 and its release is vtable slot 2.
// BFME 2 difference: setShadowsEnabled only enables the shadow's render when
// the flag byte at +0x4B is clear (unnamed; Zero Hour has no such test).
// Retail is size-optimised (/O1), unlike the /O2 W3DModelDraw.cpp port.

typedef bool Bool;

class Shadow
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void release(void);
	void enableShadowRender(Bool isEnabled) { m_isEnabled = isEnabled; }
private:
	Bool m_isEnabled; // +0x04
};

class W3DModelDraw
{
public:
	virtual void setShadowsEnabled(Bool enable);
	virtual void releaseShadows(void);
private:
	unsigned char m_pad04[0x49 - 0x04];
	Bool m_fullyObscuredByShroud; // +0x49
	Bool m_shadowEnabled; // +0x4A
	Bool m_bfme4B; // +0x4B
	unsigned char m_pad4C[0x58 - 0x4C];
	Shadow *m_shadow; // +0x58
};

//-------------------------------------------------------------------------------------------------
void W3DModelDraw::releaseShadows(void)	///< frees all shadow resources used by this module - used by Options screen.
{
	if (m_shadow)
		m_shadow->release();
	m_shadow = 0;
}

//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setShadowsEnabled(Bool enable)
{
	if (m_shadow)
		m_shadow->enableShadowRender(enable && !m_bfme4B);
	m_shadowEnabled = enable;
}
