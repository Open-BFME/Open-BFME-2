// cl: /O2 /MD
// ?Rva0073EB00Xfer@@YAPAVXfer@@PAV1@PAG@Z @0x0073EB00 106B
// Shroud PlayerState counters[3] Xfer helper N=3 twin of N=2 at 0x0073EA90.
// Evidence: caller 0x0073EBB0 passes Xfer plus short ptr; slots 0x78 count and 0x80 per-short;
// throw via _bfmeFormatText 0x0060C36E plus _CxxThrowException 0x00629094 with g_guardTargetTypeThrowInfo.

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
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual void slot31();
	virtual Xfer &xferShort(unsigned short *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;

Xfer *Rva0073EB00Xfer(Xfer *xfer, unsigned short *vals)
{
	UnsignedInt count = 3;
	int n = 3;
	xfer->xferUnsignedInt(&count);
	if (count != 3) {
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
	}
	do {
		xfer->xferShort(vals++);
	} while (--n != 0);
	return xfer;
}
