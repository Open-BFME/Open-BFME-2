// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /EHsc
// ?rva002E573C@Rva002E66F2@@UAE?AVUnicodeString@@PBUOuter002E573C@@H@Z 0x002E573C 52B
// Evidence: vslot 14 offset 0x38 of vtable 0x00804FA8 class Rva002E66F2; outer ptr at +0 inner name at +8 else g_Rva0107301CEmptyString; forwards to slot 17 offset 0x44 then StringBase<G> copy 0x00037050
#include "unicode_string.h"


struct Inner002E573C
{
	char m_pad[8];
	char m_name[1];
};

struct Outer002E573C
{
	Inner002E573C *m_ptr;
};


class Rva002E66F2
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual UnicodeString rva002E573C(const Outer002E573C *outer, int b);
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual const UnicodeString &slot17(const char *s, int b) = 0;
};

UnicodeString Rva002E66F2::rva002E573C(const Outer002E573C *outer, int b)
{
	const char *s = outer->m_ptr ? outer->m_ptr->m_name : "";
	return slot17(s, b);
}
