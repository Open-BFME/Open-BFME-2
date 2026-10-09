// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?Rva0005CC28Xfer@@YAPAVXfer@@PAV1@PAV?$map@VAsciiString@@MU?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@M@_STL@@@3@@_STL@@@Z
// retail 0x0005CC28..0x0005CD41 (281 bytes cdecl). Xfer of a
// map<AsciiString Real>: the map twin of Rva00470222Xfer (map<int int>).
// Version {1 1} via vtable +0x28 then "std::map" (+0x2C) and the node count
// (+0x78); saving (+0x08) walks the tree (_M_increment 0x00024250) copying
// each node value (pair copy 0x00466EA7) into Rva00051BC5Call 0x00051BC5;
// loading throws XferException(4 "Map must be empty on load") (ctor
// 0x0060C36E and the compiler throw info __TI1?AVXferException@@) unless
// empty then reads count pairs into map::operator[] 0x0005B67C. The
// WorldBuilder twin 0x007B4B70 has the same shape. The free-function name is
// address-derived.
#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

namespace _STL
{
struct _Rb_tree_node_base
{
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class _Dummy> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <class T> struct less;
template <class T> class allocator;

template <class A, class B> struct pair
{
	pair(const pair &other);

	A first;
	B second;
};

template <class K, class V, class C, class Al> class map
{
public:
	V &operator[](const K &key);

	_Rb_tree_node_base *m_header;
	UnsignedInt m_nodeCount;
};
}

typedef _STL::map<AsciiString, Real, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Real> > > AsciiStringRealMap;

// The save loop copies each node's value through the out-of-line pair copy
// at 0x00466EA7, rowed under its NoCaseTreeValue4 instantiation (the
// AsciiString key copy plus one word fold to one body).
struct NoCaseTreeValue4
{
	int m_word;
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> StoredPair4;

struct Rva0005CC28Pair
{
	Rva0005CC28Pair() : second(0.0f) {}

	AsciiString first;
	Real second;
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
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version); // +0x28
	virtual Xfer &xferTypeName(const char *const &name); // +0x2C
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value); // +0x78
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

int __cdecl Rva00051BC5Call(void *xfer, int pair);

Xfer *Rva0005CC28Xfer(Xfer *xfer, AsciiStringRealMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = map->m_nodeCount;
	xfer->xferTypeName("std::map").xferUnsignedInt(&count);

	if (xfer->isSaving())
	{
		_STL::_Rb_tree_node_base *last = map->m_header;
		for (_STL::_Rb_tree_node_base *cur = last->m_left; cur != last;
			cur = _STL::_Rb_global<bool>::_M_increment(cur))
		{
			StoredPair4 item(*reinterpret_cast<StoredPair4 *>(cur + 1));
			Rva00051BC5Call(xfer, (int)&item);
		}
	}
	else
	{
		if (map->m_nodeCount != 0)
			throw XferException(4, "Map must be empty on load");
		Rva0005CC28Pair item;
		while (count--)
		{
			Rva00051BC5Call(xfer, (int)&item);
			(*map)[item.first] = item.second;
		}
	}
	return xfer;
}
