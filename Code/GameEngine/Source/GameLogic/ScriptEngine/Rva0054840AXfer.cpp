// cl: /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
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
#include <algorithm>
// The existing speed scope also keeps the placement construction helper
// identical to STLport's verified provider at 0x00620140.
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline void _Construct<int, int>(int *p, const int &value)
{
    ::new (p) int(value);
}

}
#pragma optimize("", on)

// The tail operation is supplied by the verified pop_back provider.
namespace _STL { template <> void list<int>::pop_back(); }

// Compare node addresses directly, as in the native iterator comparison.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits> &a,
                              const _List_iterator<T, Traits> &b)
{ return a._M_node != b._M_node; }
template <class T, class Traits>
static inline bool operator==(const _List_iterator<T, Traits> &a,
                              const _List_iterator<T, Traits> &b)
{ return a._M_node == b._M_node; }

}

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
    void rva00548464(int flags,int id);
    void rva005482E9(int flags);
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
	// back() reads this same tail node; avoid emitting a prefix-- copy.
	if (static_cast<_STL::_List_node<int> *>(m_list04.end()._M_node->_M_prev)->_M_data == (int)m_08)
		m_08 = 0;
	m_list04.pop_back();
}

// Retail 0x00548464..0x00548527: WB ObjectOrderQueue::insertOrder
// supplies the identity lead; the existing constructors and xfer establish
// the 0x14-byte queue layout. The order activation vcall is at slot +0x10.
// Keep the existing address-derived lookup spelling: ArmorTemplate is not
// evidence that the returned order is an armor template.
// STLport 4.5.3 emits real list<int> find/__find instantiations, identical
// in bytes and relocations to the existing ObjectID instantiations.
enum NameKeyType { NK_NONE = 0 };
class ArmorTemplate;
class Rva00355B61
{
public:
    const ArmorTemplate *rva00355155(NameKeyType) const;
};
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;
struct OrderActivationView
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4(ObjectID);
};

void Rva0054840A::rva00548464(int flags, int id)
{
    if (!id)
        return;
    if (flags & 2) {
        m_list04.push_back(id);
        if (!m_08)
            m_08 = id;
        m_10 = 0;
    } else if (flags & 1) {
        m_0c = 0;
        if (!m_08)
            m_list04.push_back(id);
        else {
            // Retail passes the stored 32-bit ID's address, without a copy.
            ListInt::iterator pos = _STL::find(m_list04.begin(), m_list04.end(),
                reinterpret_cast<const int &>(m_08));
            if (pos == m_list04.end())
                m_08 = 0;
            m_list04.insert(pos, id);
        }
        if (m_list04.front() == id) {
            const ArmorTemplate *order = ((Rva00355B61 *)TheAiOrdersManager)
                ->rva00355155((NameKeyType)m_list04.front());
            if (order)
                ((OrderActivationView *)order)->slot4(m_00);
        }
    }
}

// Retail 0x005482E9..0x005483C6 clears the selected queue range.
// Target flags select boundaries around the stored active ID; each removed
// ID is passed to the existing notification wrapper before range erase.
void __cdecl rva005480E8(void *, NameKeyType, int);
void Rva0054840A::rva005482E9(int flags)
{
    ListInt::iterator first = m_list04.begin();
    ListInt::iterator last = m_list04.end();
    if (!(flags & 2) && m_08)
        last = _STL::find(m_list04.begin(), m_list04.end(), reinterpret_cast<const int &>(m_08));
    if (!(flags & 1)) {
        first = last;
        if (m_08)
            first = _STL::find(m_list04.begin(), m_list04.end(), reinterpret_cast<const int &>(m_08));
    }
    for (ListInt::iterator i = first; i != last; ++i) {
        rva005480E8((void *)m_00, (NameKeyType)*i, 1);
        if (*i == (int)m_08) m_08 = 0;
        if (*i == (int)m_0c) m_0c = 0;
        if (*i == (int)m_10) m_10 = 0;
    }
    m_list04.erase(first, last);
}
