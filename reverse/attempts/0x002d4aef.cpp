// ?DoMove@RadarPing@Impl@Palantir@@QAEXMM@Z
// partial score=0.978 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?Update@RadarPing@Impl@Palantir@@QAEXXZ retail 0x002D4A69..0x002D4AEF
// (134 bytes ret 0). WorldBuilder twin 0x00F415E0 is
// Palantir::Impl::RadarPing::Update (Palantir.cpp; assert "TheAptPlayer !=
// NULL" at line 852; string evidence "CreateRadarPing"/"MoveRadarPing").
// Sole caller 0x002D6ABC calls it directly. Once per ping (flag +0x14) and
// only with an owner (+0x08) it fires the Apt callback "CreateRadarPing"
// with the ping id (+0x18) and name (+0x10) through the rowed 0x002D43EF
// helper then scales the normalised position (+0x1C/+0x20) by the Apt
// player's scale pair (vtable +0x40) and fires "MoveRadarPing" through the
// rowed 0x002D4464 helper. The scaled floats are by-value parameters of an
// inline wrapper whose addresses reach the helper: that is what lets the
// scheduler sink retail's x store past the owner push. The global at
// 0x009FE4CC is TheAptPlayer in WorldBuilder; the ledger's provisional
// name is used. Owner and scale types are views.
#include "ascii_string.h"
#include <math.h>

class Rva00222A8BTarget;

int Rva002D43EFFire(Rva00222A8BTarget *target, void *owner, const char *name, int *value,
	const AsciiString *text);
int Rva002D4464Fire(Rva00222A8BTarget *target, void *level, const char *name, int *intParam,
	float *float1, float *float2);

struct AptScale
{
	float x;
	float y;
};

class BfmeAptWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual const AptScale *getScale(); // +0x40
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

static __forceinline int fireMoveRadarPing(void *level, int *id, float x, float y)
{
	return Rva002D4464Fire(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), level,
		"MoveRadarPing", id, &x, &y);
}

struct PalantirRadarPingOwner
{
	char m_pad00[0x5C];
	void *m_aptLevel; // +0x5C
};

static const volatile float radarMoveThreshold = 0.5f;

namespace Palantir {
class Impl
{
public:
	class RadarPing
	{
	public:
		void DoMove(float x, float y);

	private:
		char m_pad00[8];
		PalantirRadarPingOwner *m_owner; // +0x08
		char m_pad0C[4];
		AsciiString m_name; // +0x10
		bool m_initialized; // +0x14
		int m_id; // +0x18
		float m_x; // +0x1C
		float m_y; // +0x20
	};
};
}

void Palantir::Impl::RadarPing::DoMove(float x, float y)
{
 if (fabs((double)(x - m_x)) >= radarMoveThreshold || fabs((double)(y - y)) >= radarMoveThreshold)
 {
  if (m_initialized && m_owner != 0)
  {
   const AptScale *scale = g_bfmeAptWindowManager->getScale();
   fireMoveRadarPing(m_owner->m_aptLevel, &m_id, x * scale->x, y * scale->y);
  }
  m_x = x;
  m_y = y;
 }
}
