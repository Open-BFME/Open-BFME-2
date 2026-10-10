// cl: /MD
// ?xfer@Rva003AF9A9@@MAEXPAVXfer@@@Z retail 0x0055E5F6 64 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0081C81C (??_7Rva003AF9A9@@6B
// ModuleInfoHeadBase@@@, class of rowed copy ctor ??0Rva003AF9A9@@QAE@ABV0@@Z;
// ICF-shared with slot 3 of 0x0081CC10 and 0x0081D0F8): Version1, three
// GameClientRandomVariable members at +0x24/+0x30/+0x3C through the rowed
// xferRandomVariable 0x00306183, then the Real at +0x48 through Xfer slot 28
// (xferReal, as in xferRandomVariable.cpp). No base call. Precedent:
// Rva003AF22EXfer.cpp.
class Xfer
{
public:
	virtual void r0();
	virtual void r1();
	virtual void r2();
	virtual void r3();
	virtual void r4();
	virtual void r5();
	virtual void r6();
	virtual void r7();
	virtual void r8();
	virtual void r9();
	virtual void r10();
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

// The two tables (data ledger): ModuleInfoHeadBase at +0 and the
// TerrainFireEmissionInfo table at +0x1C, both with xfer in slot 3; slot 3 of
// the second is the this-adjusting (sub ecx, 0x1C) thunk 0x003AC178.
class Rva003AF9A9HeadView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
protected:
	virtual void xfer(Xfer *xfer) = 0;
private:
	char m_unmodelled04[0x1C - 0x04];
};

class Rva003AF9A9InfoView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
protected:
	virtual void xfer(Xfer *xfer) = 0;
private:
	char m_unmodelled20[0x24 - 0x20];
};

struct EmitVtableTag;

class Rva003AF9A9 : public Rva003AF9A9HeadView, public Rva003AF9A9InfoView
{
public:
	Rva003AF9A9(EmitVtableTag *);
	GameClientRandomVariable m_var24;
	GameClientRandomVariable m_var30;
	GameClientRandomVariable m_var3C;
	float m_real48;

protected:
	virtual void xfer(Xfer *xfer);
};

void Rva003AF9A9::xfer(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_var24);
	xferRandomVariable(*xfer, m_var30);
	xferRandomVariable(*xfer, m_var3C);
	xfer->xferReal(&m_real48);
}

// Tag constructor with no retail counterpart: it only makes this TU emit the
// class's tables and with them the xfer thunk.
// ?<Rva003AF9A9::Rva003AF9A9> absent-from-retail
Rva003AF9A9::Rva003AF9A9(EmitVtableTag *)
{
}
