// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// W3DScriptedModelDraw::getAnimationFrameCount, the model variant resolver
// rva000C2E3A and the two numbering helpers they call, which share this unit:
// retail keeps the module's state pointer (getAnimationFrameCount) and the
// drawable (rva000C2E3A) in EDX across a helper call, which cl only does for
// callees it has already compiled in the same unit.
// processAnimations (BFDFE) and adjustAnimation (BEE25, named in WB 92BE60)
// share it for the same reason: adjustAnimation's frame homes and register
// choices hold only when B2E4C (private ECX/ESI ABI) and the numbering
// helpers B2BA3/B2BE5 are compiled earlier here, so both former units are one
// TU, as in retail's W3DScriptedModelDraw.cpp. The inline ~AsciiString is
// retail's: BEE25 calls StringBase::releaseBuffer directly at its scope ends.
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <set>
#include <vector>
#include "ascii_string.h"

// Retail's copies live in stlport_vector_asciistring_copy_backward.cpp.
namespace _STL {
template <> AsciiString *__uninitialized_fill_n<AsciiString *, unsigned int, AsciiString>(AsciiString *, unsigned int, const AsciiString &, const __false_type &);
template <> AsciiString *__uninitialized_copy<AsciiString *, AsciiString *>(AsciiString *, AsciiString *, AsciiString *, const __false_type &);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString *, const AsciiString &, const __false_type &, unsigned int, bool);
// Rows in Upgrade.cpp (push_back) and MapMetaDataCopy.cpp (~_Rb_tree): rva000C2CBF and the
// static sets' set::~set reach them out of line.
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString &);
template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::~_Rb_tree();
}

class Team;enum Relationship{ENEMIES,NEUTRAL,ALLIES};
class Player {public:Relationship getRelationship(const Team*)const;};
class PlayerList{char prefix[16];public:Player *local;};extern PlayerList *ThePlayerList;
struct Rva000B5FE6Template {char prefix[0x64];AsciiString name;char prefix68[0x108-0x68];unsigned flags[19];char gap[0x632-0x154];bool special632;};
class Weapon;enum WeaponSlotType {WS0};
class Object{public:Weapon*getCurrentWeapon(WeaponSlotType*);__forceinline const Rva000B5FE6Template*getTemplate()const{return definition;}char prefix[4];Rva000B5FE6Template *definition;char pad8[0x304-8];Team *team;char pad308[0x437-0x308];unsigned char state437,state438;bool isLocallyControlled()const;};
struct Rva000B5FE6Drawable{char prefix[4];Rva000B5FE6Template *definition;char pad8[0xfc-8];Object *object;char pad100[0x258-0x100];unsigned status258[19]; __forceinline bool testStatus(int n)const {return (status258[n>>5] & (1U<<(n&31)))!=0;}};
class Rva000B5FE6Render {
public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void v020();
 virtual void v021();
 virtual void v022();
 virtual void v023();
 virtual void v024();
 virtual void v025();
 virtual void v026();
 virtual void v027();
 virtual void v028();
 virtual void v029();
 virtual void v030();
 virtual void v031();
 virtual void v032();
 virtual void v033();
 virtual void v034();
 virtual void v035();
 virtual void v036();
 virtual void v037();
 virtual void v038();
 virtual void v039();
 virtual void v040();
 virtual void v041();
 virtual void v042();
 virtual void v043();
 virtual void v044();
 virtual void v045();
 virtual void v046();
 virtual void v047();
 virtual void v048();
 virtual void v049();
 virtual void v050();
 virtual void v051();
 virtual void v052();
 virtual void v053();
 virtual void v054();
 virtual void v055();
 virtual void v056();
 virtual void v057();
 virtual void v058();
 virtual void v059();
 virtual void v060();
 virtual void v061();
 virtual void v062();
 virtual void v063();
 virtual void v064();
 virtual void v065();
 virtual void v066();
 virtual void v067();
 virtual void v068();
 virtual void v069();
 virtual void v070();
 virtual void v071();
 virtual void v072();
 virtual void v073();
 virtual void v074();
 virtual void v075();
 virtual void v076();
 virtual void v077();
 virtual void v078();
 virtual void v079();
 virtual void v080();
 virtual void v081();
 virtual void v082();
 virtual void v083();
 virtual void v084();
 virtual void v085();
 virtual void v086();
 virtual void v087();
 virtual void v088();
 virtual void v089();
 virtual void v090();
 virtual void v091();
 virtual void v092();
 virtual void v093();
 virtual void v094();
 virtual void v095();
 virtual void v096();
 virtual void v097();
 virtual void v098();
 virtual void v099();
 virtual void v100();
 virtual void v101();
 virtual void v102();
 virtual void v103();
 virtual void v104();
 virtual void v105();
 virtual void v106();
 virtual void v107();
 virtual void v108();
 virtual void v109();
 virtual void v110();
 virtual void v111();
 virtual void v112();
 virtual void v113();
 virtual void v114();
 virtual void v115();
 virtual void v116();
 virtual void v117();
 virtual void v118();
 virtual void v119();
 virtual unsigned flags(); virtual void addFlags(unsigned,bool);
};

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
	class Format {public:Format(const char*,...);char text[512];};
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

// ModelConditionFlags (BitFlags<591> in ZH): 19 words of condition bits.
class ModelConditionFlags
{
public:
	Bool test(Int i) const { return (m_bits[i >> 5] >> (i & 31)) & 1; }
	bool rva000B3EB3() const;

private:
	unsigned int m_bits[19];
};

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
	char m_pad000[0x6a];
	bool hidden;
	char m_pad06B[0x134-0x6b];
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

class HAnimClass;
class W3DScriptedModelDraw : public Rva000BF953Module, public Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames);
	AsciiString rva000C2E3A(const AsciiString &modelName);
	void rva000B5FE6();
	void processAnimations();
	int rva000B3E96(int);
	void rva000B5D7F(HAnimClass*,unsigned char,int,float,float,float,unsigned char,float);
	void rva000C2CBF(int count, _STL::vector<AsciiString> *originals, _STL::vector<AsciiString> *replacements);
	// The one-character append retail expands in place (StringBase concat
	// 0x000369A0 on a stack copy of the character).
	static __forceinline void appendChar(AsciiString &asciiString, char c)
	{
		((StringBase<char> *)&asciiString)->concat(&c, 1);
	}

private:
	char m_pad10[0x14 - 0x10];
	Rva000BF953State *m_state14; // +0x14
	char m_pad18[0x50 - 0x18];
	Rva000B5FE6Render *render;
	char m_pad54[0xBC - 0x54];
	int m_index0BC;              // +0xBC
	char m_pad0C0[0x17C - 0xC0];
	ModelConditionFlags m_conditions17C; // +0x17C
	char m_pad1C8[0x214-0x1C8];
	int mode;
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

// ZH W3DModelDraw.cpp parseBoneNameKey is the semantic guide; WB925020
// and retail C2BD1 independently prove the token/registration/key path.
#include <vector>
class INI {
public:
 const char *getNextToken(const char *separators = 0);
 static void Rva000C2C5FParseBoneRecord(INI *, void *, void *, const void *);
 static void Rva000C2CA4ParseTurretPitch(INI *, void *, void *, const void *);
};
class Rva000C2AA4 {
public: void rva000C2AA4(const AsciiString &);
private: char unmodelled[0x78]; AsciiString *begin; AsciiString *end; void *storage;
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator {
public: NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
static __declspec(noinline) void parseBoneNameKey(INI *ini, void *instance, void *store, const void *)
{
 Rva000C2AA4 *self = static_cast<Rva000C2AA4 *>(instance);
 NameKeyType *key = static_cast<NameKeyType *>(store);
 AsciiString tmp(ini->getNextToken());
 ((StringBase<char> &)(tmp)).toLower();
 if (self) self->rva000C2AA4(tmp);
 if (tmp.isEmpty() || tmp.isNone()) *key = NAMEKEY_INVALID;
 else *key = TheNameKeyGenerator->nameToKey(((const StringBase<char> *)&tmp)->str());
}
struct BfmePod24 { int a[6]; };
// Row in stlport_vector_pod24_overflow.cpp; Rva000C2C5FParseBoneRecord calls it out of line.
namespace _STL { template <> void vector<BfmePod24, allocator<BfmePod24> >::push_back(const BfmePod24 &); }
struct Rva000C2C5FRecord {
 int key, at04; float at08, at0C; int at10, at14;
 Rva000C2C5FRecord() : key(0), at04(0), at08(0.0f), at0C(0.0f), at10(0), at14(0) {}
};
struct Rva000C2C5FOwner {
 char unmodelled[0xD0]; _STL::vector<BfmePod24> records;
};
void INI::Rva000C2C5FParseBoneRecord(INI *ini, void *instance, void *, const void *userData)
{
 Rva000C2C5FRecord record;
 parseBoneNameKey(ini, instance, &record.key, userData);
 static_cast<Rva000C2C5FOwner *>(instance)->records.push_back(
  reinterpret_cast<const BfmePod24 &>(record));
}

// Native379B C2CBF..C2E3A; same-valued finish expression keeps native prepass registers.
// Semantic guide: BF1 f98983a7 TextureSelection007781C0.cpp. Retail379
// changes the receiver offsets and returns two AsciiString vectors; WB932920
// additionally proves the equal-length synchronization pass.
struct Rva000C2CBFTextureEntry {
 AsciiString name; _STL::vector<AsciiString> choices; int unmodelled10;
};
struct Rva000C2CBFData {
 char at00[0x7C]; _STL::vector<Rva000C2CBFTextureEntry> textures;
 bool synchronized; char at89[0xB8-0x89]; bool useRelatedSeed;
};
struct Rva000C2CBFObject {
 char at00[0xFC]; char *related; char at100[0x364-0x100]; int seed;
};
static inline int clampTexturePick(int value, int low, int high)
{
 if (value < low) return low;
 if (value > high) return high;
 return value;
}
void W3DScriptedModelDraw::rva000C2CBF(int count, _STL::vector<AsciiString> *originals, _STL::vector<AsciiString> *replacements)
{
 replacements->clear(); originals->clear();
 Rva000C2CBFData *data = reinterpret_cast<Rva000C2CBFData *>(m_moduleData);
 Rva000C2CBFObject *object = reinterpret_cast<Rva000C2CBFObject *>(m_drawable);
 int seed;
 if (data->useRelatedSeed) seed = *reinterpret_cast<int *>(object->related + 0x78);
 else seed = object->seed;
 int ordinal = 0;
 bool synchronized = data->synchronized;
 if (synchronized) {
  int length = -1;
  for (_STL::vector<Rva000C2CBFTextureEntry>::const_iterator it = data->textures.begin(); it != data->textures.end(); ++it) {
   int n = static_cast<int>((synchronized ? it->choices.end() : it->choices.end())-it->choices.begin());
   if (n != length) {
    if (length != -1) { synchronized = false; break; }
    length = n;
   }
  }
 }
 int pick = 0;
 bool selected = false;
 for (_STL::vector<Rva000C2CBFTextureEntry>::const_iterator it = data->textures.begin(); it != data->textures.end(); ++it, ++ordinal) {
  int upper = clampTexturePick(count - 1, 0, static_cast<int>(it->choices.size()) - 1);
  if (!it->choices.empty()) {
   if (!synchronized || !selected) {
    int value = (seed + seed/3 + seed/5 + ordinal + (seed & 15)*(ordinal+1)) % it->choices.size();
    pick = clampTexturePick(value, 0, upper);
    selected = true;
   }
   if (it->choices[pick].compareNoCase(it->name) != 0) {
    replacements->push_back(it->choices[pick]);
    originals->push_back(it->name);
   }
  }
 }
}

// Native C2CA4..C2CBF, 27B: TurretPitch FieldParse at BCAD00 selects
// word+4 in the last24B turret record. The same-unit private bone-key
// helper retains its proven ECX/EDI ABI; no new helper alias is introduced.
void INI::Rva000C2CA4ParseTurretPitch(INI *ini, void *instance, void *, const void *userData)
{
 Rva000C2C5FOwner *owner = static_cast<Rva000C2C5FOwner *>(instance);
 parseBoneNameKey(ini, instance, &owner->records.back().a[1], userData);
}

// Retail 0x000B5FE6..0x000B61AB (453B), same-this collision-type updater
// called by scripted/horde model-state changes and the +0x50-guarded vslot.
// WB 0x00949620 preserves the branches and calls; its BitFlags label belongs
// to an inline assertion, not this function. The original method name is unknown.
// ZH W3DModelDraw.cpp supplies the collision-selection/rubble purpose; BFME2
// native accesses establish every offset and added condition used here.
// Keep local-control paths separate: joining them into else-if changes GRA.
// Named team/player snapshots preserve the native argument/receiver load order.
void W3DScriptedModelDraw::rva000B5FE6(){
 Rva000B5FE6Drawable *d=(Rva000B5FE6Drawable*)m_drawable;Rva000B5FE6Template *t=d->definition;
 if(!t)return;
 if(mode==-1){if((t->flags[0]&2)||(t->flags[1]&0x10000000))render->addFlags(4,true);}else if(mode==1)render->addFlags(4,true);
 if(t->flags[0]&0x40)render->addFlags(8,true);
 else if((t->flags[3]&2)||(t->flags[4]&0x100))render->addFlags(0x200,true);
 Object *o=d->object;
 if(render->flags()&4){
  unsigned f=4;
  if((t->flags[2]&0x4000000)||(t->flags[0]&0x400)||(t->flags[5]&0x1000))f|=0x80;
  if(o){Team *team=o->team; Player *player=ThePlayerList->local;Relationship r=player->getRelationship(team);
   bool local=o->isLocallyControlled(); if(local)f|=0x100;
   if(!local && r==ENEMIES && !(o->definition->flags[1]&0x10000000))f|=0x10;
  }
  render->addFlags(f,true);
 }
 if(t->flags[2]&0x10)render->addFlags(0x20,true);
 if(t->flags[2]&0x1000)render->addFlags(0,true);
 if(o){
  if(o->state437&0x10)render->addFlags(0x40,true);
  Rva000B5FE6Template *ot=o->definition;
  if(!(ot->flags[0]&0x400000) && !(o->definition->flags[0]&0x1000000) && !o->definition->special632) {
    if((o->definition->flags[0]&0x80) && d->testStatus(5))render->addFlags(0,true);
    else if(o->state438&1)render->addFlags(0,true);
  }
 }
 if(m_moduleData->hidden)render->addFlags(0,true);
}

// Primary semantic references: pinned BF1 575ba2b04 ZH W3DModelDraw::doDrawModule
// completion/state selection and WW3D animobj.cpp::Compute_Current_Frame.
// Target-specific three-slot animation/blend handling is independently present
// in named WB944C80 W3DScriptedModelDraw::processAnimations and native BFDFE.
// Every accessed layout below is a scoped native ABI view; original field and
// secondary class names are unknown. Existing address-derived adjustment and
// state-application keys preserve their opaque argument contracts.
// The local completion function is compiled together with its caller: retail
// proves ECX object / ESI slot / caller-cleaned bool stack ABI, chosen by MSVC
// for this file-static C++ function. No ABI emulation or assembly is used.
// Volatile existing last-frame operand in the backward loop preserves retail's
// multiply then add and stack homes, without introducing an extra memory read.
// Named ping-pong intermediate and per-branch blend stores preserve native order;
// forceinline drawable getter retains pause payload DL and saved vtable EAX.
#include <math.h>
// File-static float min/max used by the frame-limit clamps below. MSVC emits
// them out of line (B2B87 min, B2B95 max, 14B each, the only copies in the
// image, no callers) with its private XMM0 + stack float ABI, beside this
// unit's other static helper B2E4C. Original names unknown.
static inline float Rva000B2B87FloatMin(float a,float b){return a<b?a:b;}
static inline float Rva000B2B95FloatMax(float a,float b){return a>b?a:b;}
extern int g_bfmeDisplayAnimationSyncClock;
class WW3D{static unsigned SyncTime,PreviousSyncTime;public:static unsigned Delta(){return SyncTime-PreviousSyncTime;}};
class AnimationMotion{public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual int NumFrames();virtual float FrameRate();};
class RenderAnimationObj{public:virtual void v0();virtual void v1();virtual void v2();virtual int ClassID();};
class PauseAnimationIface{public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void v24();virtual void v25();virtual void v26();virtual void v27();virtual void Pause(bool);};

struct AnimSlot{AnimationMotion*motion;float frame,previous,unused;int mode,direction;bool completed,flag;char pad[2];};
static __declspec(noinline) bool Rva000B2E4CComplete(RenderAnimationObj*obj,AnimSlot*s,bool finish){
 if(obj && obj->ClassID()==25 && s->motion){
 switch(s->mode){case 0:case 1:case 3:case 5:return finish?s->completed:false;case 2:if(s->frame>=s->motion->NumFrames()-1.0f)return true;return false;case 6:if(s->frame<=0.0f)return true;return false;}
 }return true;
}
class Rva000B4BED{public:void*rva000B4BED(const void*);};
class Rva0027532F{public:bool rva0027532F(bool);};
class Rva000B3C61{public:void rva000B3C61(int);void rva000B3CCF(int,int);};
class Rva000B3A68{public:unsigned char rva000B3A68();};
struct Arg000B5A72;
// BFE24 calls the recovered distance-opacity provider at B5A72. Its existing
// neutral argument type names the ABI only; this view does not assert layout.
class Rva000B5C41{public:void rva000B5C41();void rva000B5A72(Arg000B5A72*);}; // rva000B5A72 rowed 0x000B5A72
class Rva000B7074{public:void rva000B7074();};
struct ModelStateView{int pad;ModelConditionFlags flags;char rest[0x5c-0x50];unsigned stateFlags;};
struct ModelDataView{char pad[0x6b];bool requirePower;};
__forceinline unsigned char Flag(unsigned value){return (value>>5)&1;}
class Rva000B8F5AOuter{public:bool rva000BF9FC(void*,bool,int);void adjustAnimation(void*,float,bool,bool,bool);};
class HAnimClass;
// Field view of the draw module for processAnimations (offsets from retail).
class ScriptedDrawView{public:__forceinline Rva0027532F*GetDrawable(){return drawable;}
 char pad0[4];ModelDataView*data;Rva0027532F*drawable;char padc[0xc];ModelStateView*state;
 char pad1c[0x44-0x1c];int whichAnimation;bool changed;char pad49[7];RenderAnimationObj*render;
 char pad54[0x90-0x54];float blend,blendTotal,speed,multiplier;char pada0[0xb8-0xa0];unsigned lastSync;char padbc[0x110-0xbc];AnimSlot slots[3];
 char pad164[0x17c-0x164];char signature[0x4c];char pad1c8[3];bool transition;int nextState;char pad1d0[0x25c-0x1d0];bool firstFrame;char pad25d[0x28c-0x25d];bool pending;
 char pad28d[0x2d8-0x28d];bool reselect;
};
void W3DScriptedModelDraw::processAnimations(){
 ScriptedDrawView*scriptedDrawView=(ScriptedDrawView*)this;
 if(!scriptedDrawView->render || !scriptedDrawView->state)return;
 ModelDataView*module=scriptedDrawView->data;
 ((Rva000B5C41*)this)->rva000B5A72((Arg000B5A72*)module);
 if(!scriptedDrawView->slots[0].motion && !scriptedDrawView->slots[1].motion){
  if(scriptedDrawView->transition){void*next=((Rva000B4BED*)module)->rva000B4BED(scriptedDrawView->signature);if(next){scriptedDrawView->pending=false;((Rva000B8F5AOuter*)this)->rva000BF9FC(next,0,0);}scriptedDrawView->transition=false;scriptedDrawView->nextState=0;}return;
 }
 unsigned delta=(unsigned)g_bfmeDisplayAnimationSyncClock-scriptedDrawView->lastSync;scriptedDrawView->lastSync=g_bfmeDisplayAnimationSyncClock;
 if(scriptedDrawView->firstFrame){scriptedDrawView->firstFrame=false;delta=WW3D::Delta();}
 ((PauseAnimationIface*)((char*)this+0xc))->Pause(!scriptedDrawView->GetDrawable()->rva0027532F(module->requirePower));
 if(!scriptedDrawView->slots[0].motion && scriptedDrawView->slots[1].motion){
  ((Rva000B3C61*)this)->rva000B3CCF(0,1);
  if(scriptedDrawView->slots[2].motion){
   ((Rva000B3C61*)this)->rva000B3CCF(1,2);
   float limit=scriptedDrawView->slots[1].unused;
   float duration;
   if(limit>0.0f){float last=scriptedDrawView->slots[1].motion->NumFrames()-1.0f;duration=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(limit,last));}
   else{float last=scriptedDrawView->slots[1].motion->NumFrames()-1.0f;duration=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(5.0f,last));}
   scriptedDrawView->blend=scriptedDrawView->blendTotal=duration;
  }
 }
 for(int i=0;i<3;++i){AnimSlot&animSlot=((ScriptedDrawView*)this)->slots[i];if(animSlot.motion){
  float step=animSlot.motion->FrameRate()*scriptedDrawView->multiplier*scriptedDrawView->speed*delta*0.001f;
  float last=animSlot.motion->NumFrames()-1.0f;
  animSlot.previous=animSlot.frame;animSlot.completed=false;
  switch(animSlot.mode){
  case 1:animSlot.frame=step+animSlot.frame;if(animSlot.frame>last){animSlot.frame-=int(animSlot.frame/last)*last;animSlot.completed=true;}break;
  case 2:animSlot.frame=step+animSlot.frame;if(animSlot.frame>last){animSlot.frame=last;animSlot.completed=true;}break;
  case 3:{float frame=animSlot.frame+animSlot.direction*step;animSlot.frame=frame;if(animSlot.direction==1){if(frame>last){animSlot.direction=-1;float repeated=int(frame/last)*last;repeated+=last;animSlot.frame=repeated-frame;animSlot.completed=true;}}else if(animSlot.frame<0.0f){int repeats=(int)(fabs((double)animSlot.frame)/last);if(repeats>0)animSlot.frame+=repeats*last;animSlot.frame=-animSlot.frame;animSlot.direction=1;animSlot.completed=true;}break;}
  case 5:{animSlot.frame-=step;if(animSlot.frame<0.0f){float repeated=(int)(fabs((double)animSlot.frame)/last)*(*(volatile float*)&last);repeated+=last;animSlot.frame+=repeated;animSlot.completed=true;}break;}
  case 6:animSlot.frame-=step;if(animSlot.frame<0.0f){animSlot.frame=0.0f;animSlot.completed=true;}break;
  }
 }}
 if(scriptedDrawView->slots[0].motion && scriptedDrawView->slots[1].motion){
  float step=scriptedDrawView->slots[1].motion->FrameRate()*scriptedDrawView->multiplier*scriptedDrawView->speed*delta;
  scriptedDrawView->blend-=step*0.001f;
  if(scriptedDrawView->blend<0.0f){((Rva000B3C61*)this)->rva000B3CCF(0,1);if(scriptedDrawView->slots[2].motion){
   ((Rva000B3C61*)this)->rva000B3CCF(1,2);
   float limit=scriptedDrawView->slots[1].unused;
   if(limit>0.0f){float last=scriptedDrawView->slots[1].motion->NumFrames()-1.0f;scriptedDrawView->blend=scriptedDrawView->blendTotal=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(limit,last));}
   else{float last=scriptedDrawView->slots[1].motion->NumFrames()-1.0f;scriptedDrawView->blend=scriptedDrawView->blendTotal=Rva000B2B95FloatMax(1.0f,Rva000B2B87FloatMin(5.0f,last));}
  }else scriptedDrawView->blend=0.0f;}
 }
 if(!((Rva000B3A68*)this)->rva000B3A68() && Rva000B2E4CComplete(scriptedDrawView->render,&scriptedDrawView->slots[0],scriptedDrawView->transition) && scriptedDrawView->render && scriptedDrawView->state && scriptedDrawView->whichAnimation!=-1){
  if(scriptedDrawView->transition){void*next=((Rva000B4BED*)module)->rva000B4BED(scriptedDrawView->signature);if(next){scriptedDrawView->nextState=0;scriptedDrawView->pending=false;((Rva000B8F5AOuter*)this)->rva000BF9FC(next,0,0);if(!scriptedDrawView->nextState)scriptedDrawView->transition=false;return;}else{scriptedDrawView->transition=false;scriptedDrawView->nextState=0;}}
  ModelStateView*cur=scriptedDrawView->state;
  if(!cur->flags.rva000B3EB3())((Rva000B8F5AOuter*)this)->adjustAnimation(cur,-1.0f,false,false,false);
  else if(Flag(cur->stateFlags)){((Rva000B8F5AOuter*)this)->adjustAnimation(cur,-1.0f,false,false,false);scriptedDrawView->changed=true;}
 }
 if(scriptedDrawView->reselect){scriptedDrawView->reselect=false;((Rva000B8F5AOuter*)this)->adjustAnimation(0,-1.0f,false,false,false);}
 ((Rva000B5C41*)this)->rva000B5C41();((Rva000B7074*)this)->rva000B7074();
}


// Target BEE25..BF7E8/WB92BE60: BFME2 extends the ZH adjustAnimation
// selection spine with script transitions, three lanes and weapon timing.
#include "ascii_string.h"
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_create_node(AsciiString const &); }
namespace _STL { template <> void _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_erase(_Rb_tree_node<AsciiString> *); }
namespace _STL { template <> void vector<BfmePod24, allocator<BfmePod24> >::_M_insert_overflow(BfmePod24 *, BfmePod24 const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> AsciiString * vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *); }
namespace _STL { template <> pair<_Rb_tree_iterator<AsciiString, _Nonconst_traits<AsciiString> >, bool> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::insert_unique(AsciiString const &); }
// bfme link decl-only end
class AdjustReport {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual AdjustReport*text(const char*);virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void finish(int);
 AdjustReport&operator<<(const Debug::Format&v){text((const char*)&v);return *this;}
};
class AdjustDebug {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void begin();virtual void s25();virtual void s26();virtual AdjustReport*report(int,int,int);
};
extern Debug*theDebug;bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
#define ADDBG ((AdjustDebug*)theDebug)
#define ADSTART() _bfme_debugRecordCallsite(1);ADDBG->begin()
struct Coord3D;enum WeaponStatus {WSTATUS0};
#include "../../../../../../GameEngine/Include/GameLogic/Weapon.h"
class Rva002C9504BinarySubField {public:int get()const;};
struct AdjustDrawable {char pad[0xfc];Object*object;__forceinline Object*getObject()const{return object;}};
struct Rva00334133Context;
class LuaScriptEngine {public:AsciiString rva00334133(const char*,unsigned long,Rva00334133Context*);};extern LuaScriptEngine*TheLuaScriptEngine;
class Rva000B7539 {public:~Rva000B7539();AsciiString previous,transition,animation;void*source;float fraction;bool finish;Rva000B7539():source(0),fraction(0),finish(false){} };
class Rva000B4926 {public:const AsciiString&rva000B4926()const;};
class HTreeClass;
class Rva000BE027Anim {public:HTreeClass*rva000BE027(const AsciiString&,const AsciiString&,bool,int);};
class Rva000B9A0E {public:void rva000B9A0E(void*,int,int);};
class Rva000B49F9 {public:unsigned char rva000B49F9();};
class AnimConditionInfo {public:int rva000B495B();int pickRandomAnimation(int,int);};
float GetGameClientRandomValueReal(float,float,char*,int);
struct AdjustAnimation {char names[12];AsciiString name,previousName;char pad14[4];float duration;int mode;float blend,minSpeed,maxSpeed;unsigned char flag;bool weaponTiming;char pad2e[0x40-0x2e];};
template<class T>struct AdjustVector {T*first,*last,*capacity;int size()const{return last-first;}T&operator[](int i){return first[i];}};
struct AdjustState {AsciiString name;char pad4[0x50-4];_STL::vector<AdjustAnimation>animations;unsigned flags;char pad60[12];AsciiString script;char pad70[0x9c-0x70];bool restart,allowRepeat;char pad9e[0xf8-0x9e];};
struct AdjustData {char pad[0x24];AdjustState*first,*last;char pad2c[0x134-0x2c];bool numbered,fixedNumber;};
struct AdjustModel {char pad[0x58];AsciiString name;char pad5c[0x14];AsciiString variant;};
class AdjustRender {public:
virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();virtual void s30();virtual void s31();virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void s36();virtual void s37();virtual void s38();virtual void s39();virtual void s40();virtual void s41();virtual void s42();virtual void s43();virtual void s44();virtual void s45();virtual void clear();};
class AdjustVirtual {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();virtual void s30();virtual void s31();virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void s36();virtual void s37();virtual void s38();virtual void s39();virtual void s40();virtual void s41();virtual void s42();virtual void s43();virtual void s44();virtual void s45();virtual void s46();virtual void s47();virtual void s48();virtual void s49();virtual void s50();virtual void s51();virtual void s52();virtual void s53();virtual void s54();virtual void s55();virtual void s56();virtual void s57();virtual void s58();virtual void s59();virtual void s60();virtual void s61();virtual void s62();virtual void s63();virtual void s64();virtual void s65();virtual int maximum();virtual int randomFrame(int);};
class AdjustMotion {public:virtual void release();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual int frames();int refs;};
struct AdjustView {__forceinline AdjustDrawable*getDrawable()const{return drawable;}void*vptr;AdjustData*data;AdjustDrawable*drawable;char padc[8];AdjustModel*model;AdjustState*state;char pad1c[0x44-0x1c];int selected;char pad48[8];AdjustRender*render;char pad54[0x88-0x54];int lastSelected;char pad8c[0xbc-0x8c];int numbering;char padc0[0x110-0xc0];AnimSlot slots[3];char pad164[0x1cb-0x164];bool transition;AdjustState*next;char pad1d0[0x28c-0x1d0];bool sequential;};
struct AdjustLOD {char pad[0x1788];int limit;};
class HAnimClass;

static __forceinline unsigned char AdjustBit0(unsigned f){return f&1;}
static __forceinline unsigned char AdjustBit1(unsigned f){return (f>>1)&1;}
static __forceinline unsigned char AdjustBit2(unsigned f){return (f>>2)&1;}
void Rva000B8F5AOuter::adjustAnimation(void *old,float fraction,bool preserve,bool force,bool reset){
 AdjustView*adjustView=(AdjustView*)this;
 if(!adjustView->state||!adjustView->model)return;
 Object*object=adjustView->getDrawable()->getObject();AdjustData*data=adjustView->data;
 bool scripted=!((StringBase<char>*)&adjustView->state->script)->isEmpty();
 int oldIndex=adjustView->selected;
 if(reset){old=0;oldIndex=-1;adjustView->lastSelected=0;}
 int count=adjustView->state->animations.size();AdjustAnimation*info=0;
 if(count<=0&&!scripted){
  if(adjustView->render){((Rva000B3C61*)this)->rva000B3C61(0);((Rva000B3C61*)this)->rva000B3C61(1);adjustView->render->clear();}adjustView->selected=-1;return;
 }
 if(!preserve){
  if(adjustView->render&&count==0){((Rva000B3C61*)this)->rva000B3C61(0);((Rva000B3C61*)this)->rva000B3C61(1);adjustView->render->clear();}
  adjustView->selected=-1;
  if(scripted){
   int chosen=-1;Rva000B7539 context;context.source=adjustView->getDrawable();
   if(((AdjustState*)old)&&oldIndex>=0&&oldIndex<count)context.animation=((AdjustState*)old)->animations[oldIndex].previousName;
   if(((AdjustState*)old)&&((AdjustState*)old)!=adjustView->state){context.previous=((AdjustState*)old)->name;context.fraction=fraction;}
   AsciiString result=TheLuaScriptEngine->rva00334133(adjustView->state->script.str(),adjustView->state->script.getLength(),(Rva00334133Context*)&context);
   if(adjustView->transition&&!context.transition.isEmpty()){adjustView->transition=false;adjustView->next=0;}
   if(!context.transition.isEmpty()&&!adjustView->transition){
    AdjustState*it;
    for(it=data->first;it!=data->last;++it){if(it->name.compareNoCase(context.transition)==0){adjustView->transition=true;adjustView->next=adjustView->state;adjustView->sequential=false;rva000BF9FC(it,false,0);return;}}
    if(bfmeRva000387C0()){ADSTART();const char*objectName=object?object->getTemplate()->name.str():"NoObject";const char*stateName=context.transition.str();AdjustReport*out=ADDBG->report(0,0,0);(*out<<Debug::Format("W3DScriptedModelDraw::adjustAnimation: Unable to find transition state named '%s' in '%s'",stateName,objectName)).finish(2);}
   }
   AnimSlot*slot=&adjustView->slots[0];if(adjustView->slots[1].motion)slot=&adjustView->slots[1];
   if(((AdjustState*)old)&&context.finish&&!Rva000B2E4CComplete((RenderAnimationObj*)adjustView->render,slot,false)){
    adjustView->transition=true;adjustView->next=adjustView->state;slot->completed=false;
    ((Rva000B9A0E*)adjustView->state)->rva000B9A0E(adjustView->getDrawable()->getObject(),2,0);adjustView->state=((AdjustState*)old);
    ((Rva000B9A0E*)adjustView->state)->rva000B9A0E(adjustView->getDrawable()->getObject(),1,0);adjustView->selected=0;return;
   }
   if(!result.isEmpty()){
    for(int i=0;i<count;++i){const AsciiString&asciiString=adjustView->state->animations[i].name;if(asciiString.compareNoCase(result)==0){chosen=i;break;}}
    if(chosen==-1&&bfmeRva000387C0()){ADSTART();ADDBG->report(0,0,0)->text("Cannot find animation named ")->text(result.str())->finish(2);}
    if(chosen!=-1)adjustView->selected=chosen;else adjustView->selected=0;
   }
  }
  if(count<1){adjustView->selected=-1;return;}
  if(count==1)adjustView->selected=0;
  else if(adjustView->sequential&&count>1)adjustView->selected=(oldIndex+1)%count;
  else if(adjustView->selected<0){int avoid=-1;if(((AdjustState*)old)==adjustView->state&&!adjustView->state->allowRepeat)avoid=oldIndex;
   int maximum=((AdjustVirtual*)this)->maximum();AnimConditionInfo*current=(AnimConditionInfo*)adjustView->state;if(((Rva000B49F9*)current)->rva000B49F9())maximum=9999;
   adjustView->selected=current->pickRandomAnimation(avoid,maximum);
  }
 }
 info=&adjustView->state->animations[adjustView->selected];
 if(!force&&!preserve&&((AdjustState*)old)==adjustView->state&&!adjustView->state->restart&&adjustView->selected==oldIndex){if(((Rva000B3A68*)this)->rva000B3A68()||!Rva000B2E4CComplete((RenderAnimationObj*)adjustView->render,&adjustView->slots[0],false))return;}
 AdjustMotion*motion=0;
 if(data->fixedNumber)motion=(AdjustMotion*)((Rva000BE027Anim*)&adjustView->state->animations[adjustView->selected])->rva000BE027(adjustView->model->name,adjustView->model->variant,true,Rva000B2BA3Get((Rva000B2BE5Src*)adjustView->getDrawable(),0));
 else if(data->numbered)motion=(AdjustMotion*)((Rva000BE027Anim*)&adjustView->state->animations[adjustView->selected])->rva000BE027(adjustView->model->name,adjustView->model->variant,true,Rva000B2BE5Get((Rva000B2BE5Src*)adjustView->getDrawable(),adjustView->numbering));
 else motion=(AdjustMotion*)((Rva000BE027Anim*)&adjustView->state->animations[adjustView->selected])->rva000BE027(adjustView->model->name,adjustView->model->variant,false,0);
 if(!motion&&bfmeRva000387C0()){ADSTART();const char*objectName=object?object->definition->name.str():"NoObject";const char*modelName=adjustView->model->name.str();AdjustAnimation&adjustAnimation=adjustView->state->animations[adjustView->selected];const char*animName=((Rva000B4926*)&adjustAnimation)->rva000B4926().str();AdjustReport*out=ADDBG->report(0,0,0);(*out<<Debug::Format("Unable to locate asset: %s for Model %s in %s",animName,modelName,objectName)).finish(2);}
 if(!motion&&(unsigned)adjustView->state->animations.size()>1){
  for(unsigned i=0;i<(unsigned)adjustView->state->animations.size();++i){if(i!=(unsigned)adjustView->selected){
   if(data->fixedNumber)motion=(AdjustMotion*)((Rva000BE027Anim*)&adjustView->state->animations[i])->rva000BE027(adjustView->model->name,adjustView->model->variant,true,Rva000B2BA3Get((Rva000B2BE5Src*)adjustView->getDrawable(),0));
   else if(data->numbered)motion=(AdjustMotion*)((Rva000BE027Anim*)&adjustView->state->animations[i])->rva000BE027(adjustView->model->name,adjustView->model->variant,true,Rva000B2BE5Get((Rva000B2BE5Src*)adjustView->getDrawable(),adjustView->numbering));
   else motion=(AdjustMotion*)((Rva000BE027Anim*)&adjustView->state->animations[i])->rva000BE027(adjustView->model->name,adjustView->model->variant,false,0);
   if(motion){adjustView->selected=i;break;}
  }}
 }
 adjustView->lastSelected=adjustView->selected;
 if(!motion)return;
 int start=0,direction=1;
 if(preserve){start=(int)adjustView->slots[0].frame;direction=adjustView->slots[0].direction;}
 else {
  if(((AnimConditionInfo*)adjustView->state)->rva000B495B()==6||((AnimConditionInfo*)adjustView->state)->rva000B495B()==5){start=motion->frames()-1;direction=-1;}
  if(force&&fraction>=0.0)start=(int)(fraction*motion->frames());
  else{AdjustState*state=adjustView->state;
  if(AdjustBit0(state->flags)){if(((Rva000B49F9*)state)->rva000B49F9()&&((AdjustLOD*)TheGameLODManager)->limit>0)start=((W3DScriptedModelDraw*)this)->rva000B3E96(motion->frames());else start=((AdjustVirtual*)this)->randomFrame(motion->frames());}
  else if(AdjustBit1(state->flags))start=0;
  else if(AdjustBit2(state->flags))start=motion->frames()-1;
  else if((state->flags&0x1d0)&&((AdjustState*)old)&&((AdjustState*)old)!=state&&(((AdjustState*)old)->flags&0x1d0)&&(state->flags&((AdjustState*)old)->flags&0x1d0)&&fraction>=0.0)start=(int)(fraction*motion->frames());}
 }
 float rate=1.0f;
 if(info->minSpeed!=1.0f||info->maxSpeed!=1.0f)rate=GetGameClientRandomValueReal(info->minSpeed,info->maxSpeed,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp",0x1114);
 if(info->weaponTiming&&object){Weapon*weapon=object->getCurrentWeapon(0);if(weapon){int duration=(int)(info->duration*0.005f),time;if(weapon->computeStatus(0)==3)time=((Rva002C9504BinarySubField*)weapon)->get();else time=weapon->getPreAttackDelay(object,0,0)+weapon->rva002C9D3B(object,0);rate=(float)duration/(float)time;}}
 float blend=info->blend;int mode=info->mode;
 if(adjustView->sequential){rate=1;start=0;blend=0;if(mode==2&&count==1)mode=1;}
 float end=(float)direction*-0.00001f;end+=(float)start;
 ((W3DScriptedModelDraw*)this)->rva000B5D7F((HAnimClass*)motion,info->flag,mode,blend,(float)start,end,0,rate);
 if(--motion->refs==0)motion->release();
}
