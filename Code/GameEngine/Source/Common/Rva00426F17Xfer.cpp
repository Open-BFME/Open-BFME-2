// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// ?Rva00426F17Xfer@@YAPAVXfer@@PAV1@PAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@@Z @0x00426F17 248B evidence: version 1 1 via slot 0x28 plus size via slots 0x2C 0x78 plus isSaving via 0x08 plus per-element via rowed 0x4266BC plus reserve 0x426BE5 plus push_back 0x426EE0 plus default ctor 0x4267CC plus releaseBuffer 0x36410 plus FormatText 0x60C36E plus Throw 0x629094 plus strings std-vector Vector-must-be-empty
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"
struct BfmeStringRecord00426A5B {
	AsciiString text;
	unsigned char flag0, flag1, flag2;
	BfmeStringRecord00426A5B();
	BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &o);
};
void * __cdecl Rva004266BCProcess(void *objRaw, void *rec);
// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see System/XferException.cpp).
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};
typedef _STL::vector<BfmeStringRecord00426A5B> BfmeVec;
Xfer *Rva00426F17Xfer(Xfer *xfer, BfmeVec *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);
	UnsignedInt count = (UnsignedInt)vec->size();
	(*xfer == "std::vector") == count;
	if (xfer->IsStoring()) {
		BfmeStringRecord00426A5B *end = vec->end();
		BfmeStringRecord00426A5B *cur = vec->begin();
		while (cur != end) {
			Rva004266BCProcess(xfer, cur);
			++cur;
		}
	} else {
		if (!vec->empty()) {
			throw XferException(4, "Vector must be empty on load");
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
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<BfmeStringRecord00426A5B *>(BfmeStringRecord00426A5B *,BfmeStringRecord00426A5B *); }
// bfme link decl-only end
