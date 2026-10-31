// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
// stlport
// The list<AsciiString> fill Rva0020700FXfer (0x0020700F) moved to
// ScriptEngineDoXfer.cpp: retail compiles it in DoXfer's unit, before DoXfer.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"


typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "../../Common/System/XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

// Native constructor 0x0060C36E and throw type CFFD18 identify the real class.
// The ordinary C++ throw emits those same constructor/runtime references.
class XferException
{
public:
 XferException(int tag, const char *format, ...);
 XferException(const XferException &);
 ~XferException();
 char *text;
 int tag;
};

// BFME1 donor575 XferListAsciiStringCoord3D is the semantic guide.
// BFME2 allocation206AE0 proves24-byte nodes and16-byte string/coordinate payload;
// Chain203DA2 transfers string0 and Coord3D4; caller20A859 loads the old save format.
// Original helper name is unknown.
#include "Coord3D.h"
namespace _STL {
 template<> pair<AsciiString,Coord3D>::pair() {}
 template<> pair<AsciiString,Coord3D>::pair(const pair<AsciiString,Coord3D> &that) : first(that.first) {
  second.x=that.second.x; second.y=that.second.y; second.z=that.second.z;
 }
}
typedef _STL::pair<AsciiString,Coord3D> Rva002080DARecord;
typedef _STL::list<Rva002080DARecord> ListAscii;

// Retail keeps this _M_create_node out of line (0x00206AE0, 34B); insert 0x00207162 calls it.
namespace _STL {
template <>
inline __declspec(noinline) _List_node<Rva002080DARecord> *ListAscii::_M_create_node(const Rva002080DARecord &x)
{
    _Node *node = this->_M_node.allocate(1);
    _Construct(&node->_M_data, x);
    return node;
}
}

class Rva00203DA2A;
void Rva00203DA2Chain(Rva00203DA2A *a, void *b);

Xfer *Rva002080DAXferList(Xfer *xfer, ListAscii *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->operator==(reinterpret_cast<Xfer::Version &>(version));

	UnsignedInt count = (UnsignedInt)list->size();
	xfer->operator==("std::list").operator==(count);

	if (xfer->IsStoring())
	{
		ListAscii::_Node *sentinel = (ListAscii::_Node *)list->_M_node._M_data;
		ListAscii::_Node *node = (ListAscii::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			Rva00203DA2Chain((Rva00203DA2A *)xfer, &node->_M_data);
			node = (ListAscii::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			throw XferException(4, "List must be empty on load");
		}

		Rva002080DARecord value;
		while (count != 0)
		{
			--count;
			Rva00203DA2Chain((Rva00203DA2A *)xfer, &value);
			list->push_back(value);
		}
		--count;
	}
	return xfer;
}
