// ?DoMove@RadarPing@Impl@Palantir@@QAEXMM@Z
// partial score=0.97 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc
// Rva002D43EFFire, retail 0x002D43EF, 117 bytes, sole caller 0x002D4A95.
// UI callback firer: formats the int through the rowed Rva00222834Get
// 0x00222834 and passes its text and the given AsciiString's text (both
// falling back to "") to the UI invoker 0x00222A8B (int-return pin) with
// kind 2, returning the invoker's result.
// The formatted string is a temporary of the call expression: retail reads
// its data through the returned pointer and destroys it after the invoke
// (unwind state 0), and keeps the invoker's result in esi across that
// teardown. The banked 0.93 attempt used a named local, an extern empty
// string and a void return.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


AsciiString Rva00222834Get(int val);
AsciiString Rva002228E8Get(float val);

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int kind, const char *value, void *a4, void *a5, void *a6, void *a7);
};

int Rva002D43EFFire(Rva00222A8BTarget *target, void *owner, const char *name, int *value, const AsciiString *text)
{
	return target->invoke(owner, name, 2, Rva00222834Get(*value).str(), (void *)text->str(), 0, 0, 0);
}

// Native [0x002D4464,0x002D4531), 205B, cdecl RET0. Both radar callers
// pass target/level/name/int*/float*/float*. The native formatting calls
// evaluate float2, float1, then int; their returned strings remain alive
// through the eight-argument invoke and are destroyed in reverse order.
// The consumed types and lifetime are target evidence. The original helper
// name remains unknown. This immediately follows the 117B sibling above.
int Rva002D4464Fire(Rva00222A8BTarget *target, void *level, const char *name,
                    int *intParam, float *float1, float *float2)
{
	return target->invoke(level, name, 3, Rva00222834Get(*intParam).str(),
	    (void *)Rva002228E8Get(*float1).str(),
	    (void *)Rva002228E8Get(*float2).str(), 0, 0);
}

// ?DoMove@RadarPing@Impl@Palantir@@QAEXMM@Z, retail 0x002D4AEF..0x002D4BA5
// (182 bytes, RET 8): WorldBuilder's Palantir::Impl::RadarPing::DoMove
// (Palantir.cpp). A move of half a unit or more from the last position
// (+0x1C/+0x20) is sent, while the ping is shown (+0x14) and has an owner
// (+0x08), to the movie as "MoveRadarPing" with the ping's +0x18 id and the
// position scaled by the Apt player's slot-16 scale, through the helper
// above; the position is then remembered. Retail's second test is on a
// difference that is always zero, which the compiler folds to fabs(0).
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern "C" double __cdecl fabs(double x);

class Rva00222A8BTargetScaleView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual const float *getScale();		// slot 16
};

struct PalantirRadarPingOwner
{
	unsigned char m_pad00[0x5C];
	void *m_level5C;
};

class Palantir
{
public:
	class Impl
	{
	public:
		class RadarPing
		{
		public:
			void DoMove(float x, float y);
		private:
			unsigned char m_pad00[0x08];
			PalantirRadarPingOwner *m_owner08;	// +0x08
			unsigned char m_pad0C[0x14 - 0x0C];
			bool m_shown14;						// +0x14
			unsigned char m_pad15[3];
			int m_id18;							// +0x18
			float m_x1C;						// +0x1C
			float m_y20;						// +0x20
		};
	};
};

void Palantir::Impl::RadarPing::DoMove(float x, float y)
{
	if (fabs(x - m_x1C) >= 0.5f || fabs(y - y) >= 0.5f)
	{
		if (m_shown14 && m_owner08)
		{
			const float *scale = reinterpret_cast<Rva00222A8BTargetScaleView *>(TheRva00222A8BTarget)->getScale();
			float scaledY = scale[1] * y;
			float scaledX = scale[0] * x;
			Rva002D4464Fire(TheRva00222A8BTarget, m_owner08->m_level5C, "MoveRadarPing", &m_id18, &scaledX, &scaledY);
		}
		m_x1C = x;
		m_y20 = y;
	}
}
