// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport
// ?Rva00586231Xfer@@YAPAVXfer@@PAV1@PAV?$deque@UGen_t_00595870_p12cd@@V?$allocator@UGen_t_00595870_p12cd@@@_STL@@@_STL@@@Z @0x00586231 212B: deque xfer std-deque then count then isSaving store-iterate else empty-check load-push_back. Evidence: rowed _M_subtract 0x004218A5 _M_increment 0x00421B1E push_back 0x00586204 _bfmeFormatText 0x0060C36E pin _CxxThrowException 0x00629094; strings std-deque Deque-must-be-empty-on-load; caller 0x00587075; sibling Gen00595870DequePushBackAux same flags.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Gen_t_00595870_p12cd
{
	int m_a;
	int m_b;
	int m_c;
};

struct BfmeE12
{
	float x, y, z;
};

typedef _STL::deque<BfmeE12> E12Deque;

typedef _STL::deque<Gen_t_00595870_p12cd> GenDeque;

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
	virtual Xfer &slot24(Gen_t_00595870_p12cd &value);
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(void *value);
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
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;

Xfer *Rva00586231Xfer(Xfer *xfer, GenDeque *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	E12Deque *evec = (E12Deque *)vec;
	UnsignedInt count = (UnsignedInt)evec->size();
	xfer->xferTypeName("std::deque").xferUnsignedInt(count);

	if (xfer->isSaving()) {
		E12Deque::iterator end = evec->end();
		E12Deque::iterator cur = evec->begin();
		while (cur != end) {
			xfer->slot24((Gen_t_00595870_p12cd &)*cur);
			++cur;
		}
	} else {
		if (!evec->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Deque must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
		Gen_t_00595870_p12cd value;
		while (count != 0) {
			--count;
			xfer->slot24(value);
			vec->push_back(value);
		}
	}
	return xfer;
}
