// cl: /O1 /DNDEBUG /MD
//
// ?xfer@SpecialDisguiseUpdate@@MAEXPAVXfer@@@Z, retail 0x004B01F4, 97 bytes:
// slot 3 of SpecialDisguiseUpdate's primary vtable 0x00C56398 (ctors
// 0x004B0164, 0x004B02B7), the xfer slot. The UpdateModule part first
// (0x0044DF9F, pinned), nothing more for a light CRC (Xfer slot 4); then the
// two-byte version block (1, 2) through Xfer slot 10, the +0x90 field through
// slot 36 and the +0x8C field through slot 28, and from version 2 on the
// SpecialAbilityUpdate part (matched 0x0044F996). The field types behind
// slots 28 and 36 are not established. The version block is a small class
// with a constructor: that is what lets cl 7.1 place it in the dead argument
// slot (+8) the way retail does.
typedef unsigned char UnsignedByte;

class XferVersion
{
public:
	XferVersion(UnsignedByte first, UnsignedByte version) : m_first(first), m_version(version) {}
	UnsignedByte m_first;
	UnsignedByte m_version;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool slot1(); virtual bool slot2(); virtual bool slot3();
	virtual bool isLightCRC();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27();
	virtual Xfer &xferSlot28(void *value);
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35();
	virtual Xfer &xferSlot36(void *value);
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	virtual void slot1(); virtual void slot2();
	void xfer(Xfer *xfer);
};

class SpecialAbilityUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

class SpecialDisguiseUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad04[0x8C - 4];
	int m_8C; // +0x8C
	int m_90; // +0x90
};

void SpecialDisguiseUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->isLightCRC())
		return;
	XferVersion version(1, 2);
	xfer->xferVersion(&version);
	xfer->xferSlot36(&m_90);
	xfer->xferSlot28(&m_8C);
	if (version.m_version >= 2)
		SpecialAbilityUpdate::xfer(xfer);
}
