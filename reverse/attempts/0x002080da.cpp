// ?Rva002080DAXferList@@YAPAVXfer@@PAV1@PAV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z
// partial score=0.96 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva002080DAXferList@@YAPAVXfer@@PAV1@PAV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z @0x002080DA 237B evidence leaf Xfer list helper version 1 1 via slots 0x28 0x2C 0x78 0x08 saving via Chain 0x00203DA2 loading via Chain plus push_back strings std-list List-must-be-empty AsciiString value gives exact size 237 no structural frame diff only
#define _STLP_NO_EXCEPTIONS 1
#include <list>
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
	virtual void slot27();
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

typedef _STL::list<AsciiString> ListAscii;

class Rva00203DA2A;
void Rva00203DA2Chain(Rva00203DA2A *a, void *b);

Xfer *Rva002080DAXferList(Xfer *xfer, ListAscii *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = (UnsignedInt)list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
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
			XferException error;
			bfmeFormatText(&error, 4, "List must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}

		AsciiString value;
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
