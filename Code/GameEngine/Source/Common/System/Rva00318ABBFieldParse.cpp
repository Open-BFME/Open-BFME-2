// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the 78B frameless dispatcher at 0x00318ABB: sync the
// Sunbeam field-parse globals, run the SunbeamObject FieldParse into the
// second global through the rowed INI::initFromINI, mirror the globals
// back unless the INI's +0x08 kind is 2 or 4, then tail-jump the
// 0x00A01CEC global's slot 14 when present. All names but INI,
// initFromINI and AsciiString are address-derived; the addresses, the
// literal and the call shapes are target facts.
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	void initFromINI(void *chunk, const FieldParse *parse);
	unsigned char m_pad[8];
	int m_08;
};

// Bind to the existing data-ledger owner; keep the retail access view local.
extern unsigned int g_00E01CF0;
// Bind to the existing data-ledger owner; keep the retail access view local.
extern unsigned int g_00E01CF4;
extern const FieldParse TheRva00318ABBSunbeam;

class Rva00318ABBTarget
{
public:
	virtual void t00() = 0; virtual void t01() = 0;
	virtual void t02() = 0; virtual void t03() = 0;
	virtual void t04() = 0; virtual void t05() = 0;
	virtual void t06() = 0; virtual void t07() = 0;
	virtual void t08() = 0; virtual void t09() = 0;
	virtual void t10() = 0; virtual void t11() = 0;
	virtual void t12() = 0; virtual void t13() = 0;
	virtual void t14() = 0;
};

extern Rva00318ABBTarget *TheRva00318ABBTarget;

void rva00318ABB(INI *ini)
{
	(*(AsciiString *)&g_00E01CF4) = (*(AsciiString *)&g_00E01CF0);
	ini->initFromINI(&(*(AsciiString *)&g_00E01CF4), &TheRva00318ABBSunbeam);
	if (ini->m_08 != 2 && ini->m_08 != 4)
		(*(AsciiString *)&g_00E01CF0) = (*(AsciiString *)&g_00E01CF4);
	if (TheRva00318ABBTarget != 0)
		return TheRva00318ABBTarget->t14();
}
