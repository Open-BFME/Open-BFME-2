// cl: /DNDEBUG /MD /EHsc
//
// Rva0026EDC4Xfer at retail 0x0026EDC4, 24 bytes (mangled Rva0026EDC4Xfer free cdecl
// taking Xfer and void). Free helper called by Upgrade xfer at 0x0026EE11:
// forwards Xfer and status field to Xfer vtable slot +0x94 with UpgradeStatusType
// context and size 4. String xref unique to this body. Vtable layout follows the
// XferVersionTransfer TU where BFME2 transfer sits at +0x98 so +0x94 is slot37.

class Xfer
{
public:
	virtual ~Xfer(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void xferStatus(const char *name, void *data, int size);
	void Version1();
};

void __cdecl Rva0026EDC4Xfer(Xfer *xfer, void *data)
{
	xfer->xferStatus("UpgradeStatusType", data, 4);
}

class Rva0026EE11
{
public:
	void rva0026EE11(Xfer *xfer);
private:
	unsigned char m_pad[8];
	int m_status;
};

// Rva0026EE11 chain at retail 0x0026EE11 31 bytes: Version1 via rowed Xfer
// then the helper above with status field at +8. Callees both rowed.
void Rva0026EE11::rva0026EE11(Xfer *xfer)
{
	xfer->Version1();
	Rva0026EDC4Xfer(xfer, &m_status);
}
