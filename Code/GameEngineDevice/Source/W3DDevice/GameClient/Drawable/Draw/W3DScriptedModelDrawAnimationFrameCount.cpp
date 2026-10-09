// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// W3DScriptedModelDraw::getAnimationFrameCount, the model variant resolver
// rva000C2E3A and the two numbering helpers they call, which share this unit:
// retail keeps the module's state pointer (getAnimationFrameCount) and the
// drawable (rva000C2E3A) in EDX across a helper call, which cl only does for
// callees it has already compiled in the same unit.
//
// ?Rva000B2BA3Get@@YAHPBURva000B2BE5Src@@PA_N@Z, retail 0x000B2BA3..0x000B2BE5
// (66 bytes), cdecl: the animation numbering mode from TheGameLODManager's
// +0x1774 setting. Unless that is 3, a drawable with the 0x20 status bit
// (+0x114) forces mode 0 and reports it through the optional flag. Mode 0
// answers 2, mode 1 answers 1, anything else 0. Sibling of the rowed
// Rva000B2BE5Get (0x000B2BE5), which tests the same bit; WorldBuilder twin
// 0x0091E640 unnamed.
//
// ?getAnimationFrameCount@W3DScriptedModelDraw@@UAE_NABVAsciiString@@PAH@Z,
// retail 0x000BF953..0x000BF9FC (169 bytes, ret 8), named by its
// WorldBuilder twin 0x00930960 (W3DScriptedModelDraw.cpp). It overrides an
// interface virtual whose subobject sits at +0x0C, so this points there:
// module data at -8, drawable at -4, the current state at +8 and an index at
// +0xB0. Without an output it fails. Otherwise it looks the animation up
// through the rowed 0x000BF7E8 with the state's base (+0x58) and model
// (+0x70) names:
//  - numbered by Rva000B2BA3Get when the module data's +0x135 flag is set;
//  - numbered by Rva000B2BE5Get when its +0x134 flag is set;
//  - unnumbered otherwise.
// It stores the clip's frame count, reads its frame rate (unused), releases
// it and succeeds.
#include <set>
#include "ascii_string.h"

class HTreeClass;

HTreeClass *Rva000BF7E8FindAnimTree(const AsciiString &pattern, const AsciiString &base,
	const AsciiString &model, bool numbered, int number);

struct Rva000B2BE5Src
{
	char pad[0x114];
	unsigned char flag;
};


class GameLODManager;
extern GameLODManager *TheGameLODManager;

struct Rva000B2BA3LOD
{
	char m_pad0000[0x1774];
	int m_mode1774; // +0x1774
};

int __cdecl Rva000B2BA3Get(const Rva000B2BE5Src *p, bool *forced)
{
	int mode = reinterpret_cast<Rva000B2BA3LOD *>(TheGameLODManager)->m_mode1774;
	if (mode != 3 && p && (p->flag & 0x20))
	{
		if (forced)
			*forced = true;
		mode = 0;
	}
	switch (mode)
	{
	case 0:
		return 2;
	case 1:
		return 1;
	case 2:
	case 3:
		return 0;
	}
	return 0;
}

// ?Rva000B2BE5Get@@YAHPBURva000B2BE5Src@@H@Z, retail 0x000B2BE5..0x000B2BFF
// (26 bytes), cdecl: 2 for a drawable with the 0x20 status bit, else the
// fallback (callers 0x000BF33F 0x000BF4D2 0x000BF996 0x000C2ECC).
int __cdecl Rva000B2BE5Get(const Rva000B2BE5Src *p, int fallback)
{
	if (p && (p->flag & 0x20))
		return 2;
	return fallback;
}

typedef bool Bool;
typedef int Int;

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug &operator<<(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};

template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &text);

extern Debug *theDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

Bool Render_Obj_Exists(const char *name);

AsciiString Rva000B69EAGet(const AsciiString &name, int kind);

struct W3DScriptedModelDrawTemplateView
{
	const StringBase<char> &getName() const { return *(const StringBase<char> *)&m_name; }
	unsigned char m_unmodelled00[0x64];
	AsciiString m_name;
};

class Drawable
{
public:
	const W3DScriptedModelDrawTemplateView *getTemplate() const { return m_template; }

	void *m_vtable;
	const W3DScriptedModelDrawTemplateView *m_template;
};

// ZH ModelState.h ModelConditionFlagType, the bits this body tests.
enum
{
	MODELCONDITION_DAMAGED = 3,
	MODELCONDITION_REALLY_DAMAGED = 4,
	MODELCONDITION_RUBBLE = 5,
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8
};

template <size_t NUMBITS> class BitFlags
{
public:
	Bool test(Int i) const { return (m_bits[i >> 5] >> (i & 31)) & 1; }

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<591> ModelConditionFlags;

// The loaded clip: Delete_This (slot 0), frame count (slot 5), frame rate
// (slot 6) and its reference count at +4.
class Rva000BF953Clip
{
public:
	virtual void deleteThis();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual int getNumFrames();
	virtual float getFrameRate();

	void releaseRef()
	{
		if (--m_refs == 0)
			deleteThis();
	}

private:
	int m_refs; // +0x04
};

struct Rva000BF953ModuleData
{
	char m_pad000[0x134];
	bool m_numberByStatus134; // +0x134
	bool m_numberByLOD135;    // +0x135
	bool m_136;               // +0x136
	bool m_findVariant137;    // +0x137
};

struct Rva000BF953State
{
	char m_pad00[0x58];
	AsciiString m_base58;     // +0x58
	char m_pad5C[0x70 - 0x5C];
	AsciiString m_model70;    // +0x70
};

class Rva000BF953Module
{
public:
	virtual void m00();

	const Rva000B2BE5Src *getDrawable() const { return m_drawable; }

protected:
	Rva000BF953ModuleData *m_moduleData; // +0x04
	Rva000B2BE5Src *m_drawable;          // +0x08
};

class Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames) = 0;
};

class W3DScriptedModelDraw : public Rva000BF953Module, public Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames);
	AsciiString rva000C2E3A(const AsciiString &modelName);
	// The one-character append retail expands in place (StringBase concat
	// 0x000369A0 on a stack copy of the character).
	static __forceinline void appendChar(AsciiString &s, char c)
	{
		((StringBase<char> *)&s)->concat(&c, 1);
	}

private:
	char m_pad10[0x14 - 0x10];
	Rva000BF953State *m_state14; // +0x14
	char m_pad18[0xBC - 0x18];
	int m_index0BC;              // +0xBC
	char m_pad0C0[0x17C - 0xC0];
	ModelConditionFlags m_conditions17C; // +0x17C
};

bool W3DScriptedModelDraw::getAnimationFrameCount(const AsciiString &name, int *frames)
{
	if (frames == 0)
		return false;

	HTreeClass *found;
	if (m_moduleData->m_numberByLOD135)
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, true,
			Rva000B2BA3Get(getDrawable(), 0));
	else if (m_moduleData->m_numberByStatus134)
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, true,
			Rva000B2BE5Get(getDrawable(), m_index0BC));
	else
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, false, 0);

	if (found == 0)
		return false;
	Rva000BF953Clip *clip = reinterpret_cast<Rva000BF953Clip *>(found);
	*frames = clip->getNumFrames();
	clip->getFrameRate();
	clip->releaseRef();
	return true;
}

// ?rva000C2E3A@W3DScriptedModelDraw@@QAE?AVAsciiString@@ABV2@@Z
// retail 0x000C2E3A..0x000C32C7 (1165 bytes).
// Model variant resolver called twice by W3DScriptedModelDraw::setModelState
// (0x000C4E23 at 0x000C4FDC; WorldBuilder twin 0x00932CA0) and from
// 0x0007A9A6: the model name with its level-of-detail suffix (0x000B69EA on
// the kind from 0x000B2BA3 or 0x000B2BE5), reporting once per name a model
// that falls back to low detail without StaticModelLODMode and once per name
// a missing low detail model (which falls back to the plain name), then, when
// the module data asks (+0x137), the first existing "_[n][d|e|r][s]" variant
// for the current model condition flags at +0x17C (NIGHT 7 DAMAGED 3
// REALLY_DAMAGED 4 RUBBLE 5 SNOW 8 in Zero Hour's ModelConditionFlagType
// order).
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// Drawable/Draw/Rva007739F0ModelVariant.cpp (BFME1 0x007739F0, /O2); the
// control flow, statics, report text and suffix loops carry over. Target
// facts: module data flags +0x134/+0x135/+0x137, the kind member +0xBC, the
// condition flags +0x17C, the template name at +0x64 of the drawable's
// template, the three-argument debug stream opener and the out-of-line kind
// helper 0x000B2BE5 (BFME1 inlined that choice). WorldBuilder twin 0x00948520
// (4052 bytes) has the same calls, strings and order.
AsciiString W3DScriptedModelDraw::rva000C2E3A(const AsciiString &modelName)
{
	AsciiString name = modelName;
	if (name.isEmpty())
		return name;

	const Rva000BF953ModuleData *data = m_moduleData;
	// forcedLow lives in this block only: retail reuses its frame slot for
	// the appended character below.
	{
		Bool forcedLow = false;
		Int kind = Rva000B2BA3Get(m_drawable, &forcedLow);

		if (data->m_numberByLOD135 || forcedLow)
			name = Rva000B69EAGet(modelName, kind);
		else if (data->m_numberByStatus134)
			name = Rva000B69EAGet(modelName, Rva000B2BE5Get(m_drawable, m_index0BC));

		if (!data->m_numberByLOD135 && forcedLow)
		{
			static _STL::set<AsciiString> s_reportedStaticLOD;
			_STL::set<AsciiString>::iterator found = s_reportedStaticLOD.find(name);
			if (found == s_reportedStaticLOD.end())
			{
				s_reportedStaticLOD.insert(name);
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					theDebug->slot60();
					(theDebug->slot6C(0, 0, 0) << *(const StringBase<char> *)&name
						<< " INI setting required: Model "
						<< ((const Drawable *)getDrawable())->getTemplate()->getName()
						<< " does not have StaticModelLODMode = Yes entry... Please correct this. Still attempting low detail use.")
						.slot4C(2);
				}
			}
		}

		if (!Render_Obj_Exists(name.str()))
		{
			if (forcedLow)
			{
				static _STL::set<AsciiString> s_reportedMissing;
				_STL::set<AsciiString>::iterator found = s_reportedMissing.find(name);
				if (found == s_reportedMissing.end())
				{
					s_reportedMissing.insert(name);
					if (_bfme_debugReportingEnabled())
					{
						_bfme_debugRecordCallsite(1);
						theDebug->slot60();
						(theDebug->slot6C(0, 0, 0) << *(const StringBase<char> *)&name
							<< " MISSING: Model " << ((const Drawable *)getDrawable())->getTemplate()->getName()
							<< " requires low detail model " << *(const StringBase<char> *)&name
							<< " but doesn't exist, so using regular model " << *(const StringBase<char> *)&modelName
							<< ". Please add this model for horde performance reasons.")
							.slot4C(2);
					}
				}
			}
			name = modelName;
		}
	}

	if (data->m_findVariant137)
	{
		Bool snow = m_conditions17C.test(MODELCONDITION_SNOW);
		Bool night = m_conditions17C.test(MODELCONDITION_NIGHT);
		if (!m_conditions17C.test(MODELCONDITION_RUBBLE)
			&& !m_conditions17C.test(MODELCONDITION_REALLY_DAMAGED)
			&& !m_conditions17C.test(MODELCONDITION_DAMAGED)
			&& !night && !snow)
			return name;

		for (Int damage = 3; damage >= 0; --damage)
		{
			switch (damage)
			{
			case 3:
				if (!m_conditions17C.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			case 2:
				if (!m_conditions17C.test(MODELCONDITION_REALLY_DAMAGED)
					&& !m_conditions17C.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			case 1:
				if (!m_conditions17C.test(MODELCONDITION_REALLY_DAMAGED)
					&& !m_conditions17C.test(MODELCONDITION_DAMAGED)
					&& !m_conditions17C.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			}

			for (Int n = 1; n >= 0; --n)
			{
				if (n && !night)
					continue;
				for (Int s = 1; s >= 0; --s)
				{
					if (s && !snow)
						continue;

					AsciiString candidate = name;
					appendChar(candidate, '_');
					if (n)
						appendChar(candidate, 'n');
					switch (damage)
					{
					case 1:
						appendChar(candidate, 'd');
						break;
					case 2:
						appendChar(candidate, 'e');
						break;
					case 3:
						appendChar(candidate, 'r');
						break;
					}
					if (s)
						appendChar(candidate, 's');
					if (Render_Obj_Exists(candidate.str()))
						return candidate;
				}
			}
		}
	}
	return name;
}
