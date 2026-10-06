// cl: /DNDEBUG /MD /EHsc
//
// ??0Locomotor@@QAE@PBVLocomotorTemplate@@@Z @0x005C96EB (104B):
// BFME1 Locomotor ctor (donor LocomotorConstructor.cpp); BFME2 layout is
// 0x26C. Base ctor 0x00313847 (BfmeAptScreenBase), member ctor 0x00524B7A at
// +0x218, vtable 0x00C74B70 at +0. Clears the dword block at +0x258..+0x264
// through a local int pointer, then ORs status bit 0x640 at +8, copies status
// to +0x254 and clears the byte at +0x268. Evidence: sole caller newLocomotor
// 0x005C9886 (pushes 0x26C); symbols.csv pin; rowed base/member ctors.
class LocomotorTemplate;

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase(void *ctx);
	~BfmeAptScreenBase();
	virtual void slot0();
protected:
	void *m_anchor;
	int m_status;
private:
	char m_rest[0x20C];
};

class Rva00524B7A
{
public:
	Rva00524B7A();
private:
	void *m_vtable;
	char m_basePad[8];
	void *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
};

extern const void *const g_00C74B70[];

class Locomotor : public BfmeAptScreenBase
{
public:
	Locomotor(const LocomotorTemplate *tmpl);
private:
	Rva00524B7A m_218;
	int m_254;
	int m_258[4];
	unsigned char m_268;
	char m_pad[3];
};

Locomotor::Locomotor(const LocomotorTemplate *tmpl) : BfmeAptScreenBase((void *)tmpl)
{
	int *p = m_258;
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;
	m_status |= 0x640;
	m_254 = m_status;
	m_268 = 0;
}
