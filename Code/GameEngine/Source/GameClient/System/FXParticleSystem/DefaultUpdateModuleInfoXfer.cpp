// cl: /MD
// ?xfer@DefaultUpdateModuleInfo@FXParticleSystem@@UAEXPAVXfer@@@Z, retail 0x0055F67C, 148 bytes.
// Evidence: vtable slot 3 of 0x0081BCE0 (DefaultUpdateModuleInfo) DoXfer;
//   8 GameClientRandomVariable plus rotation-typed extra at +0x40.

class Xfer
{
public:
	virtual void r0();
	virtual void r1();
	virtual bool isSaving();
	virtual void r3();
	virtual bool r4();
	virtual void r5();
	virtual void r6();
	virtual void r7();
	virtual void r8();
	virtual void r9();
	virtual void xferVersion(unsigned char *version);
	virtual void r11();
	virtual void r12();
	virtual void r13();
	virtual void r14();
	virtual void r15();
	virtual void r16();
	virtual void r17();
	virtual void r18();
	virtual void r19();
	virtual void r20();
	virtual void r21();
	virtual void r22();
	virtual void r23();
	virtual void r24();
	virtual void r25();
	virtual void r26();
	virtual void r27();
	virtual void xferReal(float *value);
	void Version1();
};

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);
void XferRotationType(Xfer *xfer, int *value);

namespace FXParticleSystem
{

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

class DefaultUpdateModuleInfo : public Snapshot
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();
	virtual void xfer(Xfer *xfer);
private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	int m_extra;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
};

}

void FXParticleSystem::DefaultUpdateModuleInfo::xfer(Xfer *xfer)
{
	if (xfer->r4())
		return;
	union Ver { int i; unsigned char b[4]; } ver;
	ver.b[0] = 1;
	ver.b[1] = 2;
	xfer->xferVersion(&ver.b[0]);
	xferRandomVariable(*xfer, m_var0);
	xferRandomVariable(*xfer, m_var1);
	xferRandomVariable(*xfer, m_var2);
	xferRandomVariable(*xfer, m_var3);
	xferRandomVariable(*xfer, m_var4);
	XferRotationType(xfer, &m_extra);
	if (ver.b[1] < 2)
		return;
	xferRandomVariable(*xfer, m_var5);
	xferRandomVariable(*xfer, m_var6);
	xferRandomVariable(*xfer, m_var7);
}

class Rva0055F710
{
public:
	virtual void rva0055F710(Xfer *xfer);
private:
	unsigned char m_pad[0x18];
	FXParticleSystem::DefaultUpdateModuleInfo m_info;
};

void Rva0055F710::rva0055F710(Xfer *xfer)
{
	xfer->Version1();
	m_info.FXParticleSystem::DefaultUpdateModuleInfo::xfer(xfer);
}

namespace FXParticleSystem
{
class DefaultPhysicsModuleInfoX
{
public:
	virtual void xfer(Xfer *xfer);
};
}

class Rva0055F76C
{
public:
	virtual void rva0055F76C(Xfer *xfer);
private:
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	int m_1c;
	float m_20;
	float m_24;
	float m_28;
};

void Rva0055F76C::rva0055F76C(Xfer *xfer)
{
	union Ver { int i; unsigned char b[4]; } ver;
	ver.b[0] = 1;
	ver.b[1] = 2;
	xfer->xferVersion(&ver.b[0]);
	xfer->xferReal(&m_04);
	xfer->xferReal(&m_08);
	xfer->xferReal(&m_0c);
	xfer->xferReal(&m_10);
	xfer->xferReal(&m_14);
	xfer->xferReal(&m_18);
	XferRotationType(xfer, &m_1c);
	if (ver.b[1] < 2)
		return;
	xfer->xferReal(&m_20);
	xfer->xferReal(&m_24);
	xfer->xferReal(&m_28);
}

class Rva0055F805
{
public:
	virtual void rva0055F805(Xfer *xfer);
private:
	unsigned char m_pad[0x08];
	Rva0055F76C m_info;
};

void Rva0055F805::rva0055F805(Xfer *xfer)
{
	xfer->Version1();
	m_info.Rva0055F76C::rva0055F76C(xfer);
}
