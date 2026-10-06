// cl: /DNDEBUG /MD
// ?Rva00263569Xfer@@YAPAVXfer@@PAV1@PAH@Z
//
// retail 0x00263569 (89 bytes). Xfer GuardTargetType[2] with version 2 check
// via slot 0x78, throw via bfmeFormatText plus _CxxThrow on version mismatch,
// then loop 2 via XferGuardTargetType. From banked stash 0x00263569 (score
// 0.93): register allocation ebx-vs-edi. Evidence: callee 0x0060C36E rowed
// plus pins 0x00629094 and 0x00305E5A rowed; caller at 0x00268024;
// XferException's throw information in use.
class Xfer;

void __cdecl XferGuardTargetType(Xfer *xfer, int *value);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};



class Xfer
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void xferVersion(int *version);
};

Xfer *__cdecl Rva00263569Xfer(Xfer *xfer, int *values)
{
	int version = 2;
	Xfer *x = xfer;
	x->xferVersion(&version);
	if (version != 2) {
		throw XferException(0, 0);
	}
	int *p = values;
	int count = 2;
	do {
		XferGuardTargetType(x, p);
		++p;
		--count;
	} while (count != 0);
	return x;
}
