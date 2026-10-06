// ?createLightPulse@W3DDisplay@@QAEXPBUVector3@@0MMII@Z
// partial score=0.95 date=2026-10-06
// ?createLightPulse@W3DDisplay@@QAEXPBUVector3@@0MMII@Z
// partial score=0.95 date=2026-10-06
// ?createLightPulse@W3DDisplay@@QAEXPBUVector3@@0MMII@Z
// partial score=0.95 date=2026-10-06
// Banked candidate for W3DDisplay::createLightPulse @0x0004423C (233B). 232/233 bytes exact.
// WALL = single scheduling diff at +0x95: retail hoists lea ecx,[ebp-0xC] (&loc) BEFORE the
// y-store and delays the z-store past the call push; all variants emit lea late + z-store early.
// Solved along the way: ret-0x18 proves thiscall-ignoring-this (not static); temp-mediated
// doubled Vector3 copy reproduces movss load/store/reload rhythm (t6 scratch proof); repeated
// m_lines-style indexing not needed here; pool 0x6F94A candidate pin + slot-0x58 virtual via
// 23 dummies + g_00BC2904 floor all settled. Next: perturb loc-init scheduling (ploc-after-x
// tried, no move) or accept 4B. t=55 model=muse-spark
// 2026-10-06 r00b: scheduler insensitive to source shape. Tried (a) y/z temp-split
// (float y=pos->y; ploc->y=y; float z=pos->z; ploc->z=z) and (b) per-use &loc with
// ploc declared after y-load ((&loc)->y=y; (&loc)->z=z; setVec006e(&loc)): both emit
// byte-identical output (lea late + z-store early). The sinking/hoisting is pure
// backend scheduling freedom; needs a different lever (e.g. intervening sequence point
// the backend cannot cross, or a reg-pressure change). t=25 model=muse-spark
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?createLightPulse@W3DDisplay@@QAEXPBUVector3@@0MMII@Z @0x0004423C 233B.
// W3DDisplay::createLightPulse: pulse light setup. Skips when the summed
// range falls below the 0xBC2904 floor; otherwise takes a W3DDynamicLight
// from the scene pool (unrowed 0x6F94A via a candidate pin, same as the
// 0x33930 precedent), enables it, copies the color into Ambient and Diffuse,
// pushes the position through virtual slot 0x58, stages FarAttenStart/End,
// runs the rowed setFrameFade and sets the +0x145/+0x146 bytes. Identity as
// W3DDisplay::createLightPulse is carried from the rowed setFrameFade TU's
// caller evidence (call site 0x4430D); the pool/floor symbols are
// address-derived candidates. SSE float codegen per the /arch:SSE line.
struct Vector3
{
	float x;
	float y;
	float z;
};

class W3DDynamicLight
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void setVec006e(const Vector3 *v);
	void setEnabled(bool enabled);
	void setFrameFade(unsigned int frameIncreaseTime, unsigned int decayFrameTime);

public:
	unsigned char m_pad4[0xD4 - 4];
	Vector3 Ambient;
	Vector3 Diffuse;
	unsigned char m_padEC[0x100 - 0xEC];
	float FarAttenStart;
	float FarAttenEnd;
	unsigned char m_pad108[0x145 - 0x108];
	bool m_b145;
	bool m_b146;
};

class RTS3DScene
{
public:
	W3DDynamicLight *rva0006F94A(void);
};

class W3DDisplay
{
public:
	void createLightPulse(const Vector3 *pos, const Vector3 *color, float a, float b, unsigned int c, unsigned int d);

	static RTS3DScene *m_3DScene;
};

extern float g_00BC2904;

void W3DDisplay::createLightPulse(const Vector3 *pos, const Vector3 *color, float a, float b, unsigned int c, unsigned int d)
{
	float range = a + b;
	if (g_00BC2904 > range)
		return;
	W3DDynamicLight *light = m_3DScene->rva0006F94A();
	light->setEnabled(true);
	Vector3 tmp;
	tmp.x = color->x;
	tmp.y = color->y;
	tmp.z = color->z;
	Vector3 *ambient = &light->Ambient;
	ambient->x = tmp.x;
	ambient->y = tmp.y;
	ambient->z = tmp.z;
	tmp.x = color->x;
	tmp.y = color->y;
	tmp.z = color->z;
	Vector3 *diffuse = &light->Diffuse;
	diffuse->x = tmp.x;
	diffuse->y = tmp.y;
	diffuse->z = tmp.z;
	Vector3 loc;
	loc.x = pos->x;
	Vector3 *ploc = &loc;
	ploc->y = pos->y;
	ploc->z = pos->z;
	light->setVec006e(ploc);
	light->FarAttenStart = a;
	light->FarAttenEnd = range;
	light->setFrameFade(c, d);
	light->m_b145 = true;
	light->m_b146 = true;
}
