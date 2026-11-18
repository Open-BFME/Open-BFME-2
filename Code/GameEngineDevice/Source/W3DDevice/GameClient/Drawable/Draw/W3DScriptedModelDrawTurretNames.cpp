// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// turretNamesDiffer (retail 0x000B7E8B, 121 B, RET 0), the file-static helper
// of W3DScriptedModelDraw::setModelState (retail 0x000C4E23, WB 0x00932CA0;
// its only caller, call at 0x000C4F45). WorldBuilder 0x00935680 is the same
// helper by callsite. Zero Hour W3DModelDraw.cpp's static turretNamesDiffer
// is the semantic donor: both states must have valid turrets, then the angle
// and pitch name keys of each turret are compared. BFME2 keeps the turrets in
// a vector of 24-byte records at +0xD0 (bounded by both sizes), the valid flag
// is the byte at +0xF5 and MAX_TURRETS is 1 (target facts from the retail and
// WB bodies; the member names are carried from the donor).
//
// Retail passes `a` in EDI and `b` in EBX: cl 7.1 picks that private
// convention itself for a file-static noinline function, so the helper is
// spelled as plain C++ and emitted through a source-only caller until
// setModelState is recovered in this unit.

#include <vector>

#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"

typedef int NameKeyType;

enum { MAX_TURRETS = 1 };

struct ModelConditionInfo
{
	struct TurretInfo
	{
		NameKeyType m_turretAngleNameKey;
		NameKeyType m_turretPitchNameKey;
		Int m_unknown08[4];
	};

	char m_unknown000[0xD0];
	_STL::vector<TurretInfo> m_turrets;     // +0xD0
	char m_unknown0DC[0xF5 - 0xDC];
	Bool m_turretsValid;                    // +0xF5
};

static __declspec(noinline) Bool turretNamesDiffer(const ModelConditionInfo *a, const ModelConditionInfo *b)
{
	if (!a->m_turretsValid || !b->m_turretsValid)
		return true;
	for (Int i = 0; i < MAX_TURRETS; ++i)
	{
		if (i >= a->m_turrets.size() || i >= b->m_turrets.size())
			break;
		if (a->m_turrets[i].m_turretAngleNameKey != b->m_turrets[i].m_turretAngleNameKey ||
			a->m_turrets[i].m_turretPitchNameKey != b->m_turrets[i].m_turretPitchNameKey)
			return true;
	}
	return false;
}

// ?W3DScriptedModelDrawTurretNamesCaller absent-from-retail
Bool W3DScriptedModelDrawTurretNamesCaller(const ModelConditionInfo *newState, const ModelConditionInfo *curState)
{
	return turretNamesDiffer(newState, curState);
}
