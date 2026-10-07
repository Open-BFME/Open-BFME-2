// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
//
// ?Rva00208081Xfer@@YAPAVXfer@@PAV1@PAX@Z, retail 0x00208081, 89 bytes.
// Fixed 20-element array of 12-byte vectors via rowed Rva001ECA2DXfer.
// Count via slot 0x78 checked against 0x14 with FormatText plus Throw.
// Evidence: leaf lane caller 0x0020B803 and rowed callees plus prev next Xfer list units.
typedef unsigned int UnsignedInt;
typedef bool Bool;

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
	virtual Xfer &xferVersion(void *version);
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
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

extern Xfer *Rva001ECA2DXfer(Xfer *xfer, void *storage);

Xfer *Rva00208081Xfer(Xfer *xfer, void *storage)
{
	UnsignedInt count = 20;
	xfer->xferUnsignedInt(count);
	if (count != 20)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
	}
	char *p = (char *)storage;
	UnsignedInt left = 20;
	do
	{
		Rva001ECA2DXfer(xfer, p);
		p += 12;
		--left;
	} while (left != 0);
	return xfer;
}
