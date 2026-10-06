// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0054840A@Rva0054840A@@QAEXPAVXfer@@@Z @0x0054840A 90B thiscall xfer with version 1 1 plus ObjectID plus three uints plus list<int>.
// Evidence: chain callee rowed xferListInt 0x00206861; callees rowed XferObjectID 0x003060B2 plus Xfer slots 0x28 version and 0x78 uint; caller 0x003550EB news 0x14 and calls directly; ret 4 single Xfer arg.
// ??0Rva0054840A@@QAE@XZ @0x0054829B 37B default ctor zeroing ObjectID plus list base 0x004EC36C plus three uints.
// Evidence: same 0x14 layout as xfer 0x0054840A; caller 0x003550DD news 0x14; no vtable.
// ??0Rva0054840A@@QAE@W4ObjectID@@@Z @0x005482C0 41B one-arg ctor setting ObjectID plus list base 0x004EC36C plus three uints.
// Evidence: same 0x14 layout; caller 0x00355842 in 0x003557B7; allocator temp at ebp+0xb.
// ?rva00548700@Rva0054840A@@QAEXXZ @0x00548700 44B pop list back when non-empty and m_08 non-zero with m_10 clear plus conditional m_08 clear.
// Evidence: same 0x14 layout list at +4 uints at +8 +0x10; caller 0x003551F9; tail-jmp to rowed pop_back 0x00053D4F.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
// Retail's list<int> iterator prefix-- copy is the speed form (edx: mov edx,
// [ecx+4]); this TU builds /O1 which emits the size form (ecx). Define the
// explicit specialization for speed so our COMDAT matches retail; code this
// TU's rows inline keeps this TU's flags.
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline _List_iterator<int, _Nonconst_traits<int> > &_List_iterator<int, _Nonconst_traits<int> >::operator--()
{
	this->_M_decr();
	return *this;
}
}
#pragma optimize("", on)

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
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
};

enum ObjectID
{
	INVALID_ID = 0
};

typedef _STL::list<int> ListInt;

void XferObjectID(Xfer *xfer, ObjectID *objectID);
Xfer *xferListInt(Xfer *xfer, ListInt *list);

class Rva0054840A
{
public:
	Rva0054840A();
	Rva0054840A(ObjectID id);
	void rva0054840A(Xfer *xfer);
	void rva00548700();
private:
	ObjectID m_00;
	ListInt m_list04;
	UnsignedInt m_08;
	UnsignedInt m_0c;
	UnsignedInt m_10;
};

Rva0054840A::Rva0054840A()
	: m_00(INVALID_ID)
	, m_08(0)
	, m_0c(0)
	, m_10(0)
{
}

Rva0054840A::Rva0054840A(ObjectID id)
	: m_00(id)
	, m_08(0)
	, m_0c(0)
	, m_10(0)
{
}

void Rva0054840A::rva0054840A(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	XferObjectID(xfer, &m_00);
	xfer->xferUnsignedShort(&m_08);
	xfer->xferUnsignedShort(&m_0c);
	xfer->xferUnsignedShort(&m_10);
	xferListInt(xfer, &m_list04);
}

void Rva0054840A::rva00548700()
{
	if (m_list04.empty())
		return;
	if (m_08 == 0)
		return;
	m_10 = 0;
	if (m_list04.back() == (int)m_08)
		m_08 = 0;
	m_list04.pop_back();
}
