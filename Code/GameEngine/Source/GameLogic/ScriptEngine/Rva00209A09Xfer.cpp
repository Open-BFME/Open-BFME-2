// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common
// stlport
//
// ?Rva00209A09Xfer@@YAPAVXfer@@PAV1@PAV?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@@Z @0x00209A09 89B
// Evidence: chain lane calls 0x002081C7 now rowed; count 20 via slot 0x78 with throw on mismatch via FormatText plus Throw; loops 20 calling rowed 0x002081C7; callers 4x in 0x0020B47E.
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

Xfer *Rva002081C7XferList(Xfer *xfer, ListNocase4 *list);

Xfer *Rva00209A09Xfer(Xfer *xfer, ListNocase4 *lists)
{
	UnsignedInt count = 20;
	xfer->xferUnsignedShort(&count);
	if (count != 20) {
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
	}
	for (int i = 0; i < 20; ++i)
		Rva002081C7XferList(xfer, &lists[i]);
	return xfer;
}
