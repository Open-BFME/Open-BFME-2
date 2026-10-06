// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?xfer@SynchronizeGroupOrder@@UAEXPAVXfer@@@Z @0x00546A34 68B evidence: vslot slot 3 offset 0xC of vtable 0x0086A314 class of ??1SynchronizeGroupOrder; base GroupOrder xfer rowed 0x00548AC2; version 1 1 via Xfer slot 0x28; set at +0x18 via rowed Rva002F1CDDXfer 0x002F1CDD; bool at +0x24 via Xfer slot 0x90.
#include <set>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

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
	virtual Xfer &xferVersion(XferVersion *version);
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
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferBool(Bool &value);
};

typedef _STL::set<int> SetInt;
Xfer *Rva002F1CDDXfer(Xfer *xfer, SetInt *set);

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad04[0x18 - 4];
};

class SynchronizeGroupOrder : public GroupOrder
{
public:
	virtual ~SynchronizeGroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
private:
	SetInt m_18;
	bool m_24;
};

void SynchronizeGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	xfer->xferVersion(&version);
	Rva002F1CDDXfer(xfer, &m_18);
	xfer->xferBool(m_24);
}
