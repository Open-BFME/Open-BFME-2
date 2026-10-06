// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common
// stlport
// ?Rva0020700FXfer@@YAPAVXfer@@PAV1@PAV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z @0x0020700F 232B free list<AsciiString> Xfer helper version 1 1 via slot 0x28 size via slots 0x2C 0x78.
// Evidence: leaf lane 3 callers in FUN_0060a859; prev 0x00206FE6 next 0x002070F7; strings std-list List-must-be-empty.
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
	virtual void xferAsciiString(AsciiString &value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

typedef _STL::list<AsciiString> ListAsciiString;

Xfer *Rva0020700FXfer(Xfer *xfer, ListAsciiString *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = (UnsignedInt)list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving()) {
		ListAsciiString::_Node *sentinel = (ListAsciiString::_Node *)list->_M_node._M_data;
		ListAsciiString::_Node *node = (ListAsciiString::_Node *)sentinel->_M_next;
		while (node != sentinel) {
			xfer->xferAsciiString((AsciiString &)node->_M_data);
			node = (ListAsciiString::_Node *)node->_M_next;
		}
	} else {
		if (!list->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "List must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
		AsciiString value;
		while (count != 0) {
			--count;
			xfer->xferAsciiString(value);
			list->push_back(value);
		}
		--count;
	}
	return xfer;
}
