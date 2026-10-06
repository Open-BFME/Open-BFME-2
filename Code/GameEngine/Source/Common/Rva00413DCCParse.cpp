// cl: /Oy- /DNDEBUG /MD /GX-
// LivingWorldAutoResolveResourceBonus::parseBonusIniSubBlock (WorldBuilder name, lines 44..45: initFromINI then the MinResourceBonus check).
// was ?rva00413DCC@Rva00413DCC@@QAEXPAVINI@@@Z @0x00413DCC 65B
// INI parse validator: initFromINI(this) through table 0x00839E58 (rowed
// 0x0002DE78), then throw INIException code 3 with the retail message when
// the int at +0 is negative. Same recipe as Rva004135CDParse (filler
// 0x0002F681 plus CxxThrow 0x00629094 plus throwinfo anchor 0x00CFE2FC).
// Evidence: unlock lane; caller 0x00414009; packet message; drain sibling of
// 0x004135CD.
struct FieldParse;
class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};
extern const FieldParse g_00839E58;
struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva00413DCCThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva00413DCCThrowInfoAnchor rva00413DCCThrowInfoAnchor = { 0, 0, 0, 0 };
class LivingWorldAutoResolveResourceBonus
{
public:
	void parseBonusIniSubBlock(INI *ini);
private:
	int m_value00;
};
// was ?rva00413DCC@Rva00413DCC@@QAEXPAVINI@@@Z
void LivingWorldAutoResolveResourceBonus::parseBonusIniSubBlock(INI *ini)
{
	ini->initFromINI(this, &g_00839E58);
	if (m_value00 < 0)
	{
		INIException exc(3, "Must provide a MinResourceBonus, and it must be >= 0");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva00413DCCThrowInfoAnchor); __assume(0);
	}
}
