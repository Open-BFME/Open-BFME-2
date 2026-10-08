// cl: /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Oy-
//
// ?Rva005C94C8Get@@YA?AVUnicodeString@@PAX@Z, retail 0x005c94c8, 258 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Hero army display name: empty key or missing payload falls back to the
// parent label at +0x78/+0x64 via TheGameText Ascii slot 0x38, else formats
// STRATEGICHUD:HeroArmyName with the payload UnicodeString at +0x58.
// Evidence: callers at 0x005F4C02/0x005D221F pass hidden UnicodeString plus
// obj, isEmpty row 0x00001E2F, rva002D06CA row 0x002D06CA via g_009FF000,
// GameText slots 0x38/0x3C per Rva0020E89CFetch, copy 0x00037050,
// releaseBuffer 0x00036E70, format 0x006CB5D0, TheNullChr 0x007BB5C4.
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

struct Rva005C94C8Parent
{
	char m_pad[0x64];
	AsciiString m_label;
};

struct Rva005C94C8Obj
{
	char m_pad0[0x18];
	AsciiString m_key;
	char m_pad1[0x78 - 0x18 - 4];
	Rva005C94C8Parent *m_parent;
};

struct Rva005C94C8Payload
{
	char m_pad[0x58];
	UnicodeString m_text;
};

UnicodeString Rva005C94C8Get(void *objPtr)
{
	Rva005C94C8Obj *obj = (Rva005C94C8Obj *)objPtr;
	if (((const StringBase<char> &)obj->m_key).isEmpty()) {
		obj = (Rva005C94C8Obj *)obj->m_parent;
		return TheGameText->fetch(((Rva005C94C8Parent *)obj)->m_label);
	}
	void *found = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&obj->m_key);
	if (!found)
		return TheGameText->fetch(obj->m_parent->m_label);
	UnicodeString *payloadText = (UnicodeString *)((char *)found + 0x58);
	bool exists;
	UnicodeString label = TheGameText->fetch("STRATEGICHUD:HeroArmyName", &exists);
	if (!exists)
		return *payloadText;
	UnicodeString result;
	result.format(label.str(), payloadText->str());
	return result;
}
