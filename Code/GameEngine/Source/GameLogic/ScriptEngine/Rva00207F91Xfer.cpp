// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// ?Rva00207F91XferList@@YAPAVXfer@@PAV1@PAV?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@@Z @0x00207F91 240B
// Evidence: leaf lane free Xfer list helper; virtual slots 0x28 version 0x2C typename 0x78 count 0x08 isSaving match rowed xferListInt 0x00206861 and Rva00460216 donor; saving walks nodes via rowed Chain 0x00203D6A at edi+8; loading checks empty via FormatText plus Throw then reloads via Chain plus rowed insert wrapper 0x00207B90; strings std::list plus List must be empty on load.
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

struct NoCaseTreeValue4 { unsigned int m_value; NoCaseTreeValue4() : m_value(0) {} };

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> PairNocase4;
typedef _STL::list<PairNocase4, _STL::allocator<PairNocase4> > ListNocase4;

class Rva00203D6AA;
void Rva00203D6AChain(Rva00203D6AA *a, void *b);

class Rva00207B90
{
public:
	ListNocase4 m_list;
	void rva00207B90(const PairNocase4 &x);
};

Xfer *Rva00207F91XferList(Xfer *xfer, ListNocase4 *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = (UnsignedInt)list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		ListNocase4::_Node *sentinel = (ListNocase4::_Node *)list->_M_node._M_data;
		ListNocase4::_Node *node = (ListNocase4::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			Rva00203D6AChain((Rva00203D6AA *)xfer, &node->_M_data);
			node = (ListNocase4::_Node *)node->_M_next;
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

		PairNocase4 value;
		while (count != 0)
		{
			--count;
			Rva00203D6AChain((Rva00203D6AA *)xfer, &value);
			((Rva00207B90 *)list)->rva00207B90(value);
		}
		--count;
	}
	return xfer;
}
