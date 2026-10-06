// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common
// stlport
// ?Rva002070F7Xfer@@YAPAVXfer@@PAV1@PAV?$list@UBfmeSpecialPowerTimer8@@V?$allocator@UBfmeSpecialPowerTimer8@@@_STL@@@_STL@@@Z @0x002070F7 89B free helper xferring array of 20 SpecialPowerTimer lists via rowed 0x00206B02 count 20 via slot 0x78.
// Evidence: chain lane callee 0x00206B02 rowed; callers 4x in FUN_0060a859; prev 0x00206FE6 next 0x00207150.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "BfmeSpecialPowerTimer8.h"

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

typedef _STL::list<BfmeSpecialPowerTimer8> ListTimer;
Xfer *Rva00206B02Xfer(Xfer *xfer, ListTimer *list);

Xfer *Rva002070F7Xfer(Xfer *xfer, ListTimer *lists)
{
	UnsignedInt count = 20;
	xfer->xferUnsignedShort(&count);
	if (count != 20) {
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
	}
	for (int i = 0; i < 20; ++i)
		Rva00206B02Xfer(xfer, &lists[i]);
	return xfer;
}
