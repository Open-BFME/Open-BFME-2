// cl: /DNDEBUG /MD
//
// ?Rva0049B51EParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x0049B51E (66B): the
// AttributeModifierAuraUpdate AffectsKindOf FieldParse proc (row 0x00C50E28).
// It parses nothing and only raises the debug crash "AttributeModifierAuraUpdate...
// AffectsKindOf is obsolete, please replace with ObjectFilter. -M Lo" through
// the Debug vtable (SkipNext slot +0x60, CrashBegin +0x6C, operator<< +0x38,
// CrashDone +0x4C) when the debug flag 0x000387C0 is set. The Debug view
// follows INI_Rva0033940FParse.cpp. Name address-derived.

class INI;

#include "../../../Common/debug.h"

extern Debug *theDebug;
void __cdecl _bfme_debugRecordCallsite(int kind);
bool __cdecl bfmeRva000387C0(void);

// ?Rva0049B51EParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0049B51EParse(INI *, void *, void *, const void *)
{
	if (bfmeRva000387C0())
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "AttributeModifierAuraUpdate... AffectsKindOf is obsolete, please replace with ObjectFilter. -M Lo").CrashDone(2);
	}
}
