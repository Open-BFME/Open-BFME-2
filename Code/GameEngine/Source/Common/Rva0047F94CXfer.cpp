// cl: /MD
// ?xfer@Rva0047F94C@@QAEXPAVXfer@@@Z @ 0x0047F94C 50B
// Slot 3 (xfer) shared by vtables 0x00848418 (class of ??1Rva0047F92D) and
// 0x0084F838 (class of ??1Rva004969FF), both in Rva0024A797Derived.cpp.
// Version-gated base xfer: single-arg virtual slot 0x28 on the Xfer with a
// 2-byte version struct {1,2}, then UpdateModule::xfer only when the second
// byte reads back >= 2. Evidence: slot-3 xfer recipe; base call resolves to
// rowed ?xfer@UpdateModule@@QAEXPAVXfer@@@Z 0x0044DF9F; slot-0x28 callee
// identity unproven (indirect call, no relocation); owner class placeholder.

struct XferVersion47
{
	unsigned char m_version;
	unsigned char m_flags;
};

class Xfer
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void xferVersion(XferVersion47 *version);
};

class UpdateModule
{
public:
	void xfer(Xfer *xfer);
};

class Rva0047F94C : public UpdateModule
{
public:
	void xfer(Xfer *xfer);
};

void Rva0047F94C::xfer(Xfer *xfer)
{
	XferVersion47 version;
	version.m_version = 1;
	version.m_flags = 2;
	xfer->xferVersion(&version);
	if (version.m_flags >= 2)
		UpdateModule::xfer(xfer);
}
