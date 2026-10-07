// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00390911XferCoordVector@@YAPAVXfer@@PAV1@PAUAICommandCoordVector@@@Z @0x00390911 205B evidence: Version 1 1 via slot 0x28 plus count via slots 0x2C 0x78 plus isSaving via 0x08 plus per-element via slot 0x60 plus reserve 0x390729 plus push_back 0x2CE7DC plus FormatText 0x60C36E plus Throw 0x629094 plus strings std-vector Vector-must-be-empty. Callers 0x390E29 0x45CB3A 0x48E57C 0x48E5CF. Donor Rva00426F17Xfer.cpp shape. Pin return void is wrong, retail returns Xfer.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Rva00390729Element
{
	int opaque[3];
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
	virtual void slot24(Coord3D &value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

struct AICommandCoordVector : public _STL::vector<Coord3D>
{
};

Xfer * __cdecl Rva00390911XferCoordVector(Xfer *xfer, AICommandCoordVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);
	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(count);
	if (xfer->isSaving()) {
		Coord3D *end = vec->end();
		Coord3D *cur = vec->begin();
		while (cur != end) {
			xfer->slot24(*cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Vector must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
		reinterpret_cast<_STL::vector<Rva00390729Element> *>(vec)->reserve(count);
		Coord3D value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			xfer->slot24(vec->back());
		}
	}
	return xfer;
}
