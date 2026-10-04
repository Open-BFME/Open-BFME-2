// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00426F17Xfer@@YAPAVXfer@@PAV1@PAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@@Z @0x00426F17 248B evidence: version 1 1 via slot 0x28 plus size via slots 0x2C 0x78 plus isSaving via 0x08 plus per-element via rowed 0x4266BC plus reserve 0x426BE5 plus push_back 0x426EE0 plus default ctor 0x4267CC plus releaseBuffer 0x36410 plus FormatText 0x60C36E plus Throw 0x629094 plus strings std-vector Vector-must-be-empty
#include <vector>
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include "ascii_string.h"
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
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString &value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};
struct BfmeStringRecord00426A5B {
	AsciiString text;
	unsigned char flag0, flag1, flag2;
	BfmeStringRecord00426A5B();
	BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &o);
};
void * __cdecl Rva004266BCProcess(void *objRaw, void *rec);
struct XferException
{
	char *text;
	int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
typedef _STL::vector<BfmeStringRecord00426A5B> BfmeVec;
Xfer *Rva00426F17Xfer(Xfer *xfer, BfmeVec *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);
	UnsignedInt count = (UnsignedInt)vec->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(count);
	if (xfer->isSaving()) {
		BfmeStringRecord00426A5B *end = vec->end();
		BfmeStringRecord00426A5B *cur = vec->begin();
		while (cur != end) {
			Rva004266BCProcess(xfer, cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Vector must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
		vec->reserve(count);
		BfmeStringRecord00426A5B value;
		while (count != 0) {
			--count;
			vec->push_back(value);
			Rva004266BCProcess(xfer, &vec->back());
		}
		--count;
	}
	return xfer;
}
