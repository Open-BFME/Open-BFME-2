// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?xfer@GroupOrder@@UAEXPAVXfer@@@Z @0x00548AC2 70B evidence: vtable slot 3 offset 0xC of 0x0086A520 class of GroupOrder ctor; calls rowed Rva00398280Xfer 0x00398280 with this+4 vector; xferVersion 1-1 then xferUnsignedInt this+0x10 this+0x14; unblocks 0x00546FC9 etc.; callers 0x00546A48 etc.
// Proven method keeps real name xfer (slot 3 recipe).
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_0 = 0
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
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(void *value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};

typedef _STL::vector<ScienceType> ScienceTypeVector;
extern Xfer *Rva00398280Xfer(Xfer *xfer, ScienceTypeVector *vec);

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
private:
	ScienceTypeVector m_list;
	UnsignedInt m_10;
	UnsignedInt m_14;
};

void GroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);
	Rva00398280Xfer(xfer, &m_list);
	xfer->xferUnsignedInt(m_10);
	xfer->xferUnsignedInt(m_14);
}
