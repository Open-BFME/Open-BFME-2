// cl: /DNDEBUG /MD /EHsc /O1
// Xfer::operator==(Version &), ported from Open-BFME-1's
// XferVersionTransfer.cpp. BFME 2 inserts one virtual ahead of the raw
// transfer, so it is slot +0x98 here (BFME 1: +0x94); the version checks and
// their exceptions are unchanged.
//
// XferException's (tag, format, ...) constructor is the formatter the ledger
// holds as _bfmeFormatText at 0x0060C36E: a cdecl varargs member that stores
// the tag and a heap copy of the formatted text.

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Xfer
{
public:
	class Version
	{
	public:
		unsigned char data[2];	// [0] earliest supported, [1] current
	};

	virtual ~Xfer(void);
	virtual void slot01(void);
	virtual bool isStoring(void) const;	// +08
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void transfer(void *context, const void *data, unsigned int size);	// +98

	virtual Xfer &operator==(Version &v);
};

Xfer &Xfer::operator==(Xfer::Version &v)
{
	if (isStoring())
	{
		transfer(reinterpret_cast<void *>(0x00766572), &v.data[1], 1);
	}
	else
	{
		unsigned char previousVersion;
		unsigned char loadedVersion;
		unsigned char earliestVersion;
		{
			previousVersion = v.data[1];
			transfer(reinterpret_cast<void *>(0x00766572), &v.data[1], 1);
			loadedVersion = v.data[1];
			earliestVersion = v.data[0];
		}
		if (loadedVersion < earliestVersion)
			throw XferException(2, "Found version %i but the earliest supported is %i",
				loadedVersion, earliestVersion);
		if (loadedVersion > previousVersion)
			throw XferException(3, "Don't know how to load version %i (most recent is %i)",
				loadedVersion, previousVersion);
	}
	return *this;
}
