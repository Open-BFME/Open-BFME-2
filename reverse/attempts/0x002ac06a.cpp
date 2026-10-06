// ?rva002AC06A@Rva002AC06A@@QAEXPAVXfer@@@Z
// partial score=0.8811 date=2026-10-05
// ?rva002AC06A@Rva002AC06A@@QAEXPAVXfer@@@Z
// partial score=0.9 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva002AC06A@Rva002AC06A@@QAEXPAVXfer@@@Z @0x002AC06A 318B: KindOf BitFlags xfer.
// Evidence: TheKindOfBitNames via 0x002AA2CF 218 entries; Popcount 0x002AACDB BitCopy 0x002ABBBE
// Set 0x002AAD23 StringBase 0x00037BA0 releaseBuffer 0x00036410 memset ji FormatText 0x0060C36E
// Throw 0x00629094 empty g_Rva0107301CEmptyString guard g_guardTargetTypeThrowInfo;
// Xfer slots Version 0x28 IsStoring 0x08 IsLightCRC 0x10 AsciiString 0x6C int 0x7C XferRawBytes 0x24;
// donors XferListInt 0x00206861 XferVectorBool 0x0060C253 ObjectTypes 0x00376B70.
#include "ascii_string.h"

struct _s__ThrowInfo;

extern "C" void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct XferException
{
	char *text;
	int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;
extern const char g_Rva0107301CEmptyString[];

class Rva002ABBBE
{
public:
	void rva002ABBBE(void *other);
};

class Rva002AACDB
{
public:
	int rva002AACDB();
};

class Rva002AA2CF
{
public:
	const char *rva002AA2CF(unsigned int idx);
};

class Rva002AAD23
{
public:
	bool rva002AAD23(const char *token);
};

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual Xfer &xferAsciiString(AsciiString &value);
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual Xfer &xferInt(int &value);
};

class Rva002AC06A
{
public:
	void rva002AC06A(Xfer *xfer);
private:
	unsigned int m_bits[7];
};

// ?rva002AC06A@Rva002AC06A@@QAEXPAVXfer@@@Z present-unmatched
void Rva002AC06A::rva002AC06A(Xfer *xfer)
{
	int left;
	XferVersion ver;
	ver.m_version = 1;
	ver.m_currentVersion = 1;
	xfer->xferVersion(&ver);
	if (xfer->IsLightCRC()) {
		((Rva002ABBBE *)this)->rva002ABBBE(xfer);
		return;
	}
	if (xfer->IsStoring()) {
		left = ((Rva002AACDB *)this)->rva002AACDB();
		xfer->xferInt(left);
		for (int i = 0; i < 0xDA; ++i) {
			const char *p = ((Rva002AA2CF *)this)->rva002AA2CF((unsigned int)i);
			if (p != 0) {
				AsciiString s(p);
				xfer->xferAsciiString(s);
				--left;
			}
		}
		return;
	}
	ji_006291ae(this, 0, 28);
	int count;
	xfer->xferInt(count);
	AsciiString cur;
	for (int i = 0; i < count; ++i) {
		xfer->xferAsciiString(cur);
		char *t = *(char **)(void *)&cur;
		const char *str = t ? t + 8 : g_Rva0107301CEmptyString;
		if (((Rva002AAD23 *)this)->rva002AAD23(str) == 0) {
			XferException err;
			bfmeFormatText(&err, 0, 0);
			_CxxThrowException(&err, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
	}
}
