// cl: /MD
// ?xfer@Rva005445D4@@UAEXPAVXfer@@@Z, retail 0x00544AD2, 65 bytes.
// Slot 3 of vtable 0x00869A20, class of ??0Rva005445D4@@QAE@PAVStateMachine@@@Z.
// Version(1,2) via slot 0x28 then ObjectID at +0x24 via rowed XferObjectID
// 0x003060B2 then uint at +0x20 via slot 0x78 when version>=2. Evidence:
// vslot slot 3; rowed XferObjectID 0x003060B2; ctor layout m_20/m_24.
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	OBJECTID_0 = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion &version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24(int *value);
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(void *value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36(int *value);
};

extern void __cdecl XferObjectID(Xfer *xfer, enum ObjectID *id);

class State
{
public:
	virtual ~State();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
protected:
	char m_pad04[0x20 - 0x04];
};

class Rva005445D4 : public State
{
public:
	virtual void xfer(Xfer *xfer);
private:
	UnsignedInt m_20;
	enum ObjectID m_24;
};

void Rva005445D4::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(version);
	XferObjectID(xfer, &m_24);
	if (version.m_currentVersion >= 2)
		xfer->xferUnsignedInt(m_20);
}
