// ?Rva004EE9E9Xfer@@YAPAVXfer@@PAV1@PAVRva004EE6D0@@@Z
// partial score=0.92 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva004EE9E9Xfer@@YAPAVXfer@@PAV1@PAVRva004EE6D0@@@Z @0x004EE9E9 245B.
// Xfer vector-load over the 12B Rva004EE6D0 element vector: version 1 1 via
// slot 0x28, count via slots 0x2C/0x78, isSaving via slot 8, per-element via
// slot 0x30, empty-check FormatText plus Throw, reserve plus push_back rows.
// Evidence: chain lane every callee rowed or pinned; skeleton mirrors landed
// Rva00426F17Xfer 0x00426F17; strings std-vector and Vector-must-be-empty.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
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
	virtual Xfer &xferVersion(XferVersion &version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12(void *elem);
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
	virtual Xfer &xferUnsignedShort(UnsignedInt &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
};
struct Elem003AF8C0;
class Rva004EE6D0
{
public:
	void push_back(const Elem003AF8C0 &x);
	char *m_start00;
	char *m_finish04;
};
class Rva004EE55EVector
{
public:
	void reserve(UnsignedInt n);
};
struct XferException
{
	char *text;
	int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern int g_00C62A28;
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Temp12Init
{
	int m_a0;
	unsigned short m_b4;
	unsigned short m_c6;
	unsigned short m_d8;
};
// ?Rva004EE9E9Xfer@@YAPAVXfer@@PAV1@PAVRva004EE6D0@@@Z present-unmatched
Xfer *Rva004EE9E9Xfer(Xfer *xfer, Rva004EE6D0 *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);
	UnsignedInt count = (UnsignedInt)((vec->m_finish04 - vec->m_start00) / 12);
	xfer->xferTypeName("std::vector").xferUnsignedShort(count);
	if (xfer->isSaving()) {
		char *finish = vec->m_finish04;
		char *cur = vec->m_start00;
		while (cur != finish) {
			xfer->slot12(cur);
			cur += 12;
		}
	} else {
		if (vec->m_start00 != vec->m_finish04) {
			XferException error;
			bfmeFormatText(&error, 4, "Vector must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
		((Rva004EE55EVector *)vec)->reserve(count);
		Temp12Init tmp;
		tmp.m_a0 = (int)&g_00C62A28;
		tmp.m_b4 = 0;
		tmp.m_c6 = 0;
		tmp.m_d8 = 0;
		while (count != 0) {
			--count;
			vec->push_back(*(const Elem003AF8C0 *)&tmp);
			xfer->slot12(vec->m_finish04 - 12);
		}
	}
	return xfer;
}
