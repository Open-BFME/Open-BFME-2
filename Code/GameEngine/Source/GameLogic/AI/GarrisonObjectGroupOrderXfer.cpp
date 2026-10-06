// cl: /MD
// ?xfer@GarrisonObjectGroupOrder@@UAEXPAVXfer@@@Z @0x00546D15 65B evidence: slot 3 of 0x0086A3C4 GarrisonObjectGroupOrder dtor in Rva00548948Derived; base GroupOrder xfer rowed 0x00548AC2 then xferVersion 1-1 then XferObjectID rowed 0x003060B2 for this+0x18 then Xfer slot 0x60 virtual for this+0x1c.
// Proven slot 3 keeps real name xfer; owner GarrisonObjectGroupOrder via vtable.
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
};

extern void __cdecl XferObjectID(Xfer *xfer, enum ObjectID *id);

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
protected:
	unsigned char m_pad04[0x14];
};

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);
private:
	enum ObjectID m_18;
	int m_1c;
};

void GarrisonObjectGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	xfer->xferVersion(version);
	XferObjectID(xfer, &m_18);
	xfer->slot24(&m_1c);
}
