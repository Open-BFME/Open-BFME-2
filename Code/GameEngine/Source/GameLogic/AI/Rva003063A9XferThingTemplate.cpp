// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// Retail 0x003063A9, 112 bytes.
// Free Xfer helper for ThingTemplate*: copies the template name at +0x64 or
// the empty string, xfers it as AsciiString (Xfer slot 0x6c), and on load
// looks it up via the factory at 0x009FF000 (rowed 0x002D06CA).
// Evidence: callers WorkOrder::xfer 0x004F073B and Rva00468FB4 0x00468FC5;
// immediates AsciiString::TheEmptyString 0x009E0878 and g_009FF000;
// callees StringBase copy 0x000365F0, Xfer slots 0x6c/0x4, factory 0x002D06CA,
// releaseBuffer 0x00036410; LINK BONUS 2 files.
#include "ascii_string.h"

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual Xfer &operator==(AsciiString &value); // slot 27 (+0x6c)
};

class ThingTemplate
{
public:
	unsigned char m_pad[0x64];
	AsciiString m_name; // +0x64
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *s);
};
extern class ThingFactory *TheThingFactory;

void Rva003063A9XferThingTemplate(Xfer *xfer, const ThingTemplate **thing)
{
	AsciiString tmp = (*thing ? *(const AsciiString *)((const char *)*thing + 0x64) : AsciiString::TheEmptyString);
	xfer->operator==(tmp);
	if (!xfer->IsLoading())
		return;
	*thing = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp);
}
