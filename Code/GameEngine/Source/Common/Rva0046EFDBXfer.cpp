// ?Rva0046EFDBXfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// partial score=0.90 date=2026-09-30
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva0046EFDBXfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x0046EFDB 202B
// Xfer helper for vector<const ModuleData*> with version {1,1} via slot 0x28 size via slot 0x2C/0x78 isSaving via slot 0x08 per-element via slot 0x70 reserve 0x002B712E push_back 0x004DFCB0 FormatText 0x0060C36E Throw 0x00629094 strings "std::vector" "Vector must be empty on load" caller 0x00475632.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class ModuleData;

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
	virtual void xferModuleData(const ModuleData *&value);
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

typedef _STL::vector<const ModuleData *> ModuleDataVector;

Xfer *Rva0046EFDBXfer(Xfer *xfer, ModuleDataVector *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(&count);

	if (xfer->isSaving()) {
		ModuleDataVector::iterator last = vec->end();
		ModuleDataVector::iterator first = vec->begin();
		for (; first != last; ++first)
			xfer->xferModuleData((const ModuleData *&)*first);
	} else {
		if (!vec->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Vector must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		vec->reserve(count);
		while (count != 0) {
			--count;
			const ModuleData *tmp;
			vec->push_back(tmp);
			xfer->xferModuleData(vec->back());
		}
	}
	return xfer;
}

// The (void *, void *) declaration above is a C++ overload, so calls spell
// ?_CxxThrowException@@YGXPAX0@Z; retail calls the MSVC 7.1 throw helper
// __CxxThrowException@8 (its import thunk at 0x00629094). Same ABI: bind the spelling.
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")
