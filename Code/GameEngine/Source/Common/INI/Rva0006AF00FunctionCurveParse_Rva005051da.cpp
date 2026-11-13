// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs-c- /Os
// Open-BFME: function-curve INI loader at retail RVA 0x005051DA.
// Its neighbouring addKey/final-key bodies establish the accumulator layout;
// the three field names and the BFME padding-name table are the shipped
// literals used by this loader.

typedef int Int;

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"

typedef void (__cdecl *INIFieldParseProc)( INI *, void *, void *, const void * );

#include "../../../Include/Common/INI/FieldParse.h"

class Rva0006AB10Curve
{
};

// Null-terminated padding names used by INI::parseIndexList.
const char *g_012A718C[] =
{
	"HOLD", "EXTRAPOLATE", "CYCLE", "CYCLE_OFFSET", "MIRROR", 0
};

class Rva00504F09FunctionCurve { public: void finish(); };
class Rva0006AB90FunctionCurve
{
public:
	Rva0006AB90FunctionCurve( Rva0006AB10Curve *curve );/* the rowed Rva00504F09FunctionCurve::finish */ __declspec(dllimport) __forceinline void finish() { ((Rva00504F09FunctionCurve *)this)->finish(); }

private:
	Rva0006AB10Curve *m_curve;
	bool m_firstKey;
	float m_lastTime;
	float m_lastValue;
	float m_inTangent;
	float m_outTangent;
	bool m_haveInTangent;
	bool m_haveOutTangent;
};

#include "../../../Include/Common/Rva0006AF00FunctionCurve.h"

// ?parse@Rva0006AF00FunctionCurve@@QAEXPAVINI@@@Z
void Rva0006AF00FunctionCurve::parse( INI *ini )
{
	Rva0006AB90FunctionCurve accumulator( (Rva0006AB10Curve *)this );
	FieldParse fields[] =
	{
		{ "InPadding", INI::parseIndexList, g_012A718C, 0 },
		{ "OutPadding", INI::parseIndexList, g_012A718C, 4 },
		{ "Key", parseKey, &accumulator, 8 },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI( this, fields );
	accumulator.finish();
}
