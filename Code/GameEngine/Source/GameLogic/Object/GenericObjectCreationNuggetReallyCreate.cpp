// cl: /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /ICode/Libraries/Include /ICode/GameEngine/Include /DNDEBUG /MD /EHs
// stlport
//
// GenericObjectCreationNugget::reallyCreate, retail 0x001F1634..0x001F206E
// (2618 B, thiscall, ret 0x18, FuncInfo 0x00D10624 with 9 states via handler
// 0x0076B194).
//
// Target evidence: the result is a 12-byte vector<Object*> returned through a
// hidden pointer (copy constructor 0x001F206E into [ebp+8] at every return,
// result flag at [ebp-0x28]); the debris loop picks with GetGameLogicRandomValue
// at lines 0x67D and 0x710 of ObjectCreationList.cpp. WorldBuilder 0x00B050F0
// (GenericObjectCreationNugget::reallyCreate, asserts 1592..1808) gives the
// statement order. Offsets are retail facts; member names are descriptive.
// Donor: Zero Hour ObjectCreationList.cpp reallyCreate (debris loop, container,
// spread formation, fade in and out) is the semantic guide; the hidden vector
// result, live-player gate, owner team by name, terrain-object placement,
// build limits, clear-for-construction, waypoint start, creation flag, experience,
// pathfind registration and horde fade-in are read from retail and WorldBuilder.
//
// Codegen notes, each measured against retail:
//  - the allocator destructor carries STLport's disabled leak bookkeeping, so the
//    front end keeps EH states for the default-argument allocator temporary that
//    the back end then empties (states 3 and 4); the horde member list's dead
//    branch does the same for state 7;
//  - vector<Object*>(const allocator&) stays opaque so the storage constructor is
//    the out-of-line call to 0x00211E58 and the frame is retail's 0x1F0;
//  - KindOf is tested word by word through a const-reference getWord;
//  - the pick's upper bound is its own local: computed inline, `dec eax` is
//    scheduled after `push file` and isDebrisSkipped takes eax for its and.

#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <string.h>
#include <vector>
#include <list>
#include "../../Common/PartitionRangeQueryCallView.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
class Team;
class Drawable;
class GeometryInfo;
struct CreateMask { UnsignedInt m_bits[4]; };

// Compare concrete iterators directly; the native loops compare their nodes.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                             const _List_iterator<T, RightTraits>& b)
{
    return a._M_node != b._M_node;
}
}

namespace _STL {
enum { _STLP_LEAKS_CHECK = 0 };
template <> allocator<Object *>::~allocator() _STLP_NOTHROW { if (_STLP_LEAKS_CHECK) free(this); }
template<> vector<Object*>::vector(const vector<Object*> &);
template<> _Vector_base<Object*,allocator<Object*> >::_Vector_base(const allocator<Object*> &);
template<> _Vector_base<Object*,allocator<Object*> >::~_Vector_base();
template<> void vector<Object*>::push_back(Object * const &);
}

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
NameKeyType NAMEKEY(const AsciiString &name);

struct Vector4
{
	Vector4() {}
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	Real &operator[](int i) { return (&X)[i]; }
	Real X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &matrix3D) { Row[0] = matrix3D.Row[0]; Row[1] = matrix3D.Row[1]; Row[2] = matrix3D.Row[2]; }
	Vector4 &operator[](int i) { return Row[i]; }
	Vector4 Row[3];
};

// The template's 218 KindOf bits, tested word by word like STLport's bitset.
struct KindOfMaskType
{
	static UnsignedInt whichWord(UnsignedInt pos) { return pos >> 5; }
	static UnsignedInt whichBit(UnsignedInt pos) { return pos & 31; }
	static UnsignedInt maskBit(UnsignedInt pos) { return 1u << whichBit(pos); }
	const UnsignedInt &getWord(UnsignedInt pos) const { return m_w[whichWord(pos)]; }
	__forceinline Bool test(UnsignedInt pos) const { return (getWord(pos) & maskBit(pos)) != 0; }
	UnsignedInt m_w[7];
};

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(Int k) const { return m_kindOf.test(k); }
	const GeometryInfo &getTemplateGeometryInfo() const { return *(const GeometryInfo *)m_geometry; }
	Real getPlacementScale() const { return m_4e0; }
	// Inline field view only: the full ThingTemplate implementation has extra logic.
	__declspec(dllimport) __forceinline UnsignedInt getMaxSimultaneousOfType() const { return m_maxSimultaneousOfType; }
private:
	char m_pad000[0xA0];
	char m_geometry[0x108 - 0xA0];		// +0xA0
	KindOfMaskType m_kindOf;		// +0x108
	char m_pad124[0x4E0 - 0x124];
	Real m_4e0;				// +0x4E0
	char m_pad4e4[0x5E0 - 0x4E4];
	unsigned short m_maxSimultaneousOfType;	// +0x5E0
};

// Folded byte setter 0x0039B780 (rowed under this name): the flag at +0x110.
class W3DBridge
{
public:
	void setEnabled(Bool enabled);
	Bool isEnabled() const { return m_enabled; }
	char m_pad[0x110];
	Bool m_enabled;
};

struct Rva002A7557In;
class Rva002A7461
{
public:
	Bool rva002A7557(Rva002A7557In *tmpl, Int count);
};

class Player
{
public:
	Bool isPlayerActive() const;
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate *const *things, Bool justBuilt, Int *counts, Bool ignoreUnderConstruction) const;
	// The rowed out-of-line getter has a different compiler shape.
	__declspec(dllimport) __forceinline Team *getDefaultTeam() { return m_defaultTeam; }
	W3DBridge *getCreationFlag() { return &m_3bc; }
	char m_pad000[0x60];
	Rva002A7461 m_60;			// +0x60
	char m_pad061[0x2EC - 0x61];
	Team *m_defaultTeam;			// +0x2EC
	char m_pad2f0[0x3BC - 0x2F0];
	W3DBridge m_3bc;			// +0x3BC
};

#include "../../../Include/Common/TeamBFME2.h"

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};

class Drawable
{
public:
	void fadeIn(UnsignedInt frames);
	void fadeOut(UnsignedInt frames);
	void rva00274176(Bool b);
};

class Thing
{
public:
	Drawable *getDrawable() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
};

// Horde member list returned by value: owner word, then the member list.
struct OclMemberOwner { virtual void destroy(int); };
enum { OCL_MEMBER_CHECK = 0 };
struct OclMemberList
{
	~OclMemberList() { if (OCL_MEMBER_CHECK && m_owner) m_owner->destroy(0); }
	OclMemberOwner *m_owner;
	_STL::list<Object *> *m_list;
};

class OclMemberSource
{
public:
#define OCL_SLOT(n) virtual void slot##n();
	OCL_SLOT(00) OCL_SLOT(01) OCL_SLOT(02) OCL_SLOT(03) OCL_SLOT(04) OCL_SLOT(05) OCL_SLOT(06) OCL_SLOT(07)
	OCL_SLOT(08) OCL_SLOT(09) OCL_SLOT(10) OCL_SLOT(11) OCL_SLOT(12) OCL_SLOT(13) OCL_SLOT(14) OCL_SLOT(15)
	OCL_SLOT(16) OCL_SLOT(17) OCL_SLOT(18) OCL_SLOT(19) OCL_SLOT(20) OCL_SLOT(21) OCL_SLOT(22) OCL_SLOT(23)
	OCL_SLOT(24) OCL_SLOT(25) OCL_SLOT(26) OCL_SLOT(27) OCL_SLOT(28) OCL_SLOT(29) OCL_SLOT(30) OCL_SLOT(31)
	OCL_SLOT(32) OCL_SLOT(33) OCL_SLOT(34) OCL_SLOT(35) OCL_SLOT(36) OCL_SLOT(37) OCL_SLOT(38) OCL_SLOT(39)
	OCL_SLOT(40) OCL_SLOT(41) OCL_SLOT(42) OCL_SLOT(43) OCL_SLOT(44) OCL_SLOT(45) OCL_SLOT(46) OCL_SLOT(47)
	OCL_SLOT(48) OCL_SLOT(49) OCL_SLOT(50) OCL_SLOT(51) OCL_SLOT(52) OCL_SLOT(53) OCL_SLOT(54) OCL_SLOT(55)
	OCL_SLOT(56) OCL_SLOT(57) OCL_SLOT(58) OCL_SLOT(59) OCL_SLOT(60) OCL_SLOT(61) OCL_SLOT(62) OCL_SLOT(63)
	OCL_SLOT(64) OCL_SLOT(65)
	virtual OclMemberList getMemberList();	// +0x108
};

class ContainModuleInterface
{
public:
	OCL_SLOT(00) OCL_SLOT(01) OCL_SLOT(02) OCL_SLOT(03) OCL_SLOT(04) OCL_SLOT(05) OCL_SLOT(06) OCL_SLOT(07)
	OCL_SLOT(08) OCL_SLOT(09) OCL_SLOT(10) OCL_SLOT(11) OCL_SLOT(12) OCL_SLOT(13) OCL_SLOT(14) OCL_SLOT(15)
	OCL_SLOT(16) OCL_SLOT(17) OCL_SLOT(18) OCL_SLOT(19) OCL_SLOT(20) OCL_SLOT(21) OCL_SLOT(22) OCL_SLOT(23)
	OCL_SLOT(24) OCL_SLOT(25) OCL_SLOT(26) OCL_SLOT(27) OCL_SLOT(28) OCL_SLOT(29)
	virtual OclMemberSource *getMemberSource();	// +0x78
	OCL_SLOT(31) OCL_SLOT(32) OCL_SLOT(33) OCL_SLOT(34) OCL_SLOT(35) OCL_SLOT(36) OCL_SLOT(37)
	virtual Bool isValidContainerFor(const Object *obj, Bool checkCapacity, Int unused);	// +0x98
	virtual void addToContain(Object *obj);	// +0x9C
};

class ExperienceTracker
{
public:
	Bool rva0039B4EC(Int levels, Bool a, Bool b);
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setProducer(Object *obj);
	Int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	Int getID() const { return m_id; }
	const AsciiString &getName() const { return m_name; }
	ContainModuleInterface *getContain() const { return m_contain; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }

	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	char m_pad044[0x74 - 0x44];
	Int m_id;				// +0x74
	char m_pad078[0x88 - 0x78];
	AsciiString m_name;			// +0x88
	char m_pad08c[0x250 - 0x8C];
	ContainModuleInterface *m_contain;	// +0x250
	char m_pad254[0x264 - 0x254];
	ExperienceTracker *m_experienceTracker;	// +0x264
};

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID b);
};

class BuildAssistant
{
public:
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle, Player *playerToBuild);
};

class TerrainLogic
{
public:
	void addTree(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void rva00280176(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void rva0027D3D9(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle);
};

class GameLODManager
{
public:
	Bool isDebrisSkipped() { return ((++m_numDebrisGenerations) & m_debrisSkipMask) != m_debrisSkipMask; }
	char m_pad[0x1794];
	Int m_numDebrisGenerations;		// +0x1794
	Int m_debrisSkipMask;			// +0x1798
};

#include "../../../Include/GameLogic/ScriptEngine.h"

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
};

class AI;
struct AIView
{
	Pathfinder *pathfinder() { return m_pathfinder; }
	char m_pad[0x10];
	Pathfinder *m_pathfinder;		// +0x10
};

// The audio event's owner-ID setter 0x002D9531, rowed under an address name.
class Rva002D9531
{
public:
	void rva002D9531(Int objID);
};

class AudioManager
{
public:
	OCL_SLOT(00) OCL_SLOT(01) OCL_SLOT(02) OCL_SLOT(03) OCL_SLOT(04) OCL_SLOT(05) OCL_SLOT(06) OCL_SLOT(07)
	OCL_SLOT(08) OCL_SLOT(09) OCL_SLOT(10) OCL_SLOT(11) OCL_SLOT(12) OCL_SLOT(13) OCL_SLOT(14) OCL_SLOT(15)
	OCL_SLOT(16) OCL_SLOT(17) OCL_SLOT(18) OCL_SLOT(19) OCL_SLOT(20) OCL_SLOT(21) OCL_SLOT(22) OCL_SLOT(23)
	OCL_SLOT(24)
	virtual Int addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd);	// +0x64
};

extern ThingFactory *TheThingFactory;
extern PlayerList *ThePlayerList;
extern BuildAssistant *TheBuildAssistant;
extern TerrainLogic *TheTerrainLogic;
extern GameLODManager *TheGameLODManager;
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern AudioManager *TheAudio;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

#define OCL_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp"
#define GameLogicRandomValue(lo, hi, line) GetGameLogicRandomValue((lo), (hi), OCL_FILE, (line))
#define GameLogicRandomValueReal(lo, hi, line) GetGameLogicRandomValueReal((lo), (hi), OCL_FILE, (line))

enum FindPositionFlags
{
	FPF_NONE = 0x00000000,
	FPF_IGNORE_WATER = 0x00000001,
	FPF_USE_HIGHEST_LAYER = 0x00000080
};

struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = FPF_NONE;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}
	Int flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

class GenericObjectCreationNugget
{
public:
	virtual ~GenericObjectCreationNugget();
	_STL::vector<Object *> reallyCreate(const Coord3D *pos, const Matrix3D *mtx, Real orientation,
		const Object *sourceObj, UnsignedInt lifetimeFrames) const;
protected:
	void doStuffToObj(Object *obj, const AsciiString &modelName, const Coord3D *pos,
		const Matrix3D *mtx, Real orientation, const Object *sourceObj,
		UnsignedInt lifetimeFrames, Int radialIndex) const;
	void rva001F21E8(Coord3D *pos) const;
private:
	_STL::vector<AsciiString> m_names;	// +0x04
	AsciiString m_putInContainer;		// +0x10
	char m_pad14[0x28 - 0x14];
	Int m_debrisToGenerate;			// +0x28
	char m_pad2c[0x40 - 0x2C];
	UnsignedInt m_disposition;		// +0x40
	char m_pad44[0x78 - 0x44];
	UnsignedInt m_fadeFrames;		// +0x78
	OpaqueRefElement4 m_fadeSound;		// +0x7C
	Real m_minDistanceAFormation;		// +0x80
	Real m_minDistanceBFormation;		// +0x84
	Real m_maxDistanceFormation;		// +0x88
	char m_pad8c[0x90 - 0x8C];
	Bool m_requiresLivePlayer;		// +0x90
	Bool m_ignoreBuildLimits;		// +0x91
	Bool m_92;				// +0x92
	Bool m_inheritScriptingName;		// +0x93
	char m_pad94[0x9D - 0x94];
	Bool m_preserveLayer;			// +0x9D
	Bool m_9e;				// +0x9E
	Bool m_9f;				// +0x9F
	Bool m_a0;				// +0xA0
	char m_pada1[0xA8 - 0xA1];
	Bool m_nameAreObjects;			// +0xA8
	char m_pada9[0xAB - 0xA9];
	Bool m_spreadFormation;			// +0xAB
	Bool m_fadeIn;				// +0xAC
	Bool m_fadeOut;				// +0xAD
	char m_padae[0xB0 - 0xAE];
	Int m_experienceLevels;			// +0xB0
	char m_padb4[0x108 - 0xB4];
	AsciiString m_teamOwnerName;		// +0x108
	AsciiString m_waypointPrefix;		// +0x10C
	char m_pad110;
	Bool m_clearForConstruction;		// +0x111
};

_STL::vector<Object *> GenericObjectCreationNugget::reallyCreate(const Coord3D *pos, const Matrix3D *mtx,
	Real orientation, const Object *sourceObj, UnsignedInt lifetimeFrames) const
{
	static const ThingTemplate *debrisTemplate = TheThingFactory->findTemplate("GenericDebris");

	_STL::vector<Object *> objects;
	objects.clear();

	if (m_names.size() <= 0)
		return objects;

	if (m_requiresLivePlayer && (!sourceObj || !sourceObj->getControllingPlayer()->isPlayerActive()))
		return objects;

	Object *debris = 0;
	Team *debrisOwner = 0;
	if (!m_teamOwnerName.isEmpty())
	{
		Player *player = ThePlayerList->findPlayerWithNameKey(NAMEKEY(m_teamOwnerName));
		if (player)
			debrisOwner = player->getDefaultTeam();
	}
	else if (sourceObj)
	{
		debrisOwner = sourceObj->getControllingPlayer()->getDefaultTeam();
	}

	Object *container = 0;
	if (!m_putInContainer.isEmpty())
	{
		const ThingTemplate *containerTmpl = TheThingFactory->findTemplate(m_putInContainer);
		if (containerTmpl)
		{
			if (containerTmpl->isKindOf(0x64) || containerTmpl->isKindOf(0x5E) || containerTmpl->isKindOf(0x5F))
			{
				Matrix3D tmpMtx(*mtx);
				tmpMtx[2][3] = 0.0f;
				tmpMtx[1][3] = 0.0f;
				tmpMtx[0][3] = 0.0f;
				Real scale = containerTmpl->getPlacementScale();
				if (containerTmpl->isKindOf(0x5E))
					TheTerrainLogic->addTree(containerTmpl, pos, &tmpMtx, scale);
				else if (containerTmpl->isKindOf(0x5F))
					TheTerrainLogic->rva00280176(containerTmpl, pos, &tmpMtx, scale);
				else
					TheTerrainLogic->rva0027D3D9(containerTmpl, pos, &tmpMtx, scale);
			}
			else
			{
				if (m_clearForConstruction)
				{
					TheBuildAssistant->clearRemovableForConstruction(containerTmpl, pos, orientation);
					if (debrisOwner)
					{
						Player *owner = debrisOwner->getControllingPlayer();
						if (owner)
							TheBuildAssistant->moveObjectsForConstruction(containerTmpl, pos, orientation, owner);
					}
					TheTerrainLogic->rva0028449F(pos, containerTmpl->getTemplateGeometryInfo(), orientation);
				}
				CreateMask mask;
				memset(&mask, 0, sizeof(mask));
				container = TheThingFactory->newObject(containerTmpl, debrisOwner, &mask, (ObjectID)0);
				container->setProducer((Object *)sourceObj);
			}
		}
	}

	for (Int nn = 0; nn < m_debrisToGenerate; nn++)
	{
		Int hi = m_names.size() - 1;
		Int pick = GameLogicRandomValue(0, hi, 1661);

		const ThingTemplate *thingTemplate;
		if (m_nameAreObjects)
		{
			thingTemplate = TheThingFactory->findTemplate(m_names[pick]);
			if (!thingTemplate)
				continue;

			Player *player = sourceObj ? sourceObj->getControllingPlayer() : 0;
			if (!m_ignoreBuildLimits && player && !player->m_60.rva002A7557((Rva002A7557In *)thingTemplate, 1))
				return objects;

			if (player && thingTemplate->getMaxSimultaneousOfType())
			{
				Int count;
				player->countObjectsByThingTemplate(1, &thingTemplate, true, &count, false);
				if (count >= thingTemplate->getMaxSimultaneousOfType())
					return objects;
			}
		}
		else
		{
			if (TheGameLODManager->isDebrisSkipped())
				continue;
			thingTemplate = debrisTemplate;
		}

		if (!thingTemplate)
			continue;

		if (thingTemplate->isKindOf(0x64) || thingTemplate->isKindOf(0x5E) || thingTemplate->isKindOf(0x5F))
		{
			Matrix3D tmpMtx(*mtx);
			tmpMtx[2][3] = 0.0f;
			tmpMtx[1][3] = 0.0f;
			tmpMtx[0][3] = 0.0f;
			Real scale = thingTemplate->getPlacementScale();
			if (thingTemplate->isKindOf(0x5E))
				TheTerrainLogic->addTree(thingTemplate, pos, &tmpMtx, scale);
			else if (thingTemplate->isKindOf(0x5F))
				TheTerrainLogic->rva00280176(thingTemplate, pos, &tmpMtx, scale);
			else
				TheTerrainLogic->rva0027D3D9(thingTemplate, pos, &tmpMtx, scale);
			continue;
		}

		if (m_clearForConstruction)
		{
			TheBuildAssistant->clearRemovableForConstruction(thingTemplate, pos, orientation);
			if (debrisOwner)
			{
				Player *owner = debrisOwner->getControllingPlayer();
				if (owner)
					TheBuildAssistant->moveObjectsForConstruction(thingTemplate, pos, orientation, owner);
			}
			TheTerrainLogic->rva0028449F(pos, thingTemplate->getTemplateGeometryInfo(), orientation);
		}

		W3DBridge *ownerFlag = 0;
		Bool ownerFlagWas = false;
		if (sourceObj)
		{
			ownerFlag = sourceObj->getControllingPlayer()->getCreationFlag();
			ownerFlagWas = ownerFlag->isEnabled();
			ownerFlag->setEnabled(false);
		}

		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		debris = TheThingFactory->newObject(thingTemplate, debrisOwner, &mask, (ObjectID)0);
		objects.push_back(debris);

		if (ownerFlag)
			ownerFlag->setEnabled(ownerFlagWas);

		Drawable *draw = debris->getDrawable();
		if (m_92 && draw)
			draw->rva00274176(true);

		if (m_nameAreObjects && m_inheritScriptingName && sourceObj && !sourceObj->getName().isEmpty())
		{
			if (m_debrisToGenerate == 1)
				TheScriptEngine->rva00357960(sourceObj->getName(), debris);
		}

		if (m_preserveLayer && sourceObj && container == 0)
		{
			PathfindLayerEnum layer = (PathfindLayerEnum)sourceObj->rva0028B511();
			if (layer != LAYER_GROUND)
				debris->setLayer(layer);
		}

		if (container && container->getContain() && container->getContain()->isValidContainerFor(debris, true, 0))
			container->getContain()->addToContain(debris);

		if (!m_waypointPrefix.isEmpty())
		{
			Coord3D waypointPos;
			waypointPos.x = pos->x;
			waypointPos.y = pos->y;
			waypointPos.z = pos->z;
			rva001F21E8(&waypointPos);
			doStuffToObj(debris, m_names[pick], &waypointPos, mtx, orientation, sourceObj, lifetimeFrames, nn);
		}
		else if (m_spreadFormation)
		{
			Int flags = FPF_USE_HIGHEST_LAYER;
			Coord3D resultPos;
			FindPositionOptions fpOptions;
			fpOptions.minRadius = GameLogicRandomValueReal(m_minDistanceAFormation, m_minDistanceBFormation, 1808);
			fpOptions.maxRadius = m_maxDistanceFormation;
			if (m_9e)
				flags |= 0x04;
			if (m_a0)
				flags |= 0x20;
			if (m_9f)
				flags |= 0x08;
			if (m_disposition & 0x20000)
				flags |= FPF_IGNORE_WATER;
			if (m_disposition & 0x40000)
				flags |= 0x100;
			fpOptions.flags = flags;
			if (sourceObj)
			{
				if (!PartitionManager::findPositionAround(pos, &fpOptions, &resultPos))
					resultPos = *sourceObj->getPosition();
			}
			doStuffToObj(debris, m_names[pick], &resultPos, mtx, orientation, sourceObj, lifetimeFrames, nn);
		}
		else
		{
			doStuffToObj(debris, m_names[pick], pos, mtx, orientation, sourceObj, lifetimeFrames, nn);
		}

		W3DBridge *ownerFlag2 = sourceObj->getControllingPlayer()->getCreationFlag();
		Bool ownerFlagWas2 = ownerFlag2->isEnabled();
		ownerFlag2->setEnabled(false);
		((Rva0028CBFD *)debris)->rva0028CBFD();
		ownerFlag2->setEnabled(ownerFlagWas2);

		if (m_experienceLevels > 0)
			debris->getExperienceTracker()->rva0039B4EC(m_experienceLevels, true, false);

		debris->setProducer((Object *)sourceObj);

		if (debris->getTemplate()->isKindOf(7))
			((AIView *)TheAI)->pathfinder()->AddObjectToPathfindMap(debris);

		if (m_fadeIn)
		{
			BfmeAudioEventPrefix136 fadeAudioEvent(m_fadeSound, 0);
			if (sourceObj)
				((Rva002D9531 *)&fadeAudioEvent)->rva002D9531(sourceObj->getID());
			TheAudio->addAudioEvent(&fadeAudioEvent);
			if (debris->getTemplate()->isKindOf(0x6D))
			{
				ContainModuleInterface *contain = debris->getContain();
				if (contain)
				{
					OclMemberSource *source = contain->getMemberSource();
					if (source)
					{
						OclMemberList members = source->getMemberList();
						for (_STL::list<Object *>::const_iterator it = members.m_list->begin(); it != members.m_list->end(); ++it)
						{
							Object *member = *it;
							if (member)
								member->getDrawable()->fadeIn(m_fadeFrames);
						}
					}
				}
			}
			else
			{
				debris->getDrawable()->fadeIn(m_fadeFrames);
			}
		}

		if (m_fadeOut)
		{
			BfmeAudioEventPrefix136 fadeAudioEvent(m_fadeSound, 0);
			if (sourceObj)
				((Rva002D9531 *)&fadeAudioEvent)->rva002D9531(sourceObj->getID());
			TheAudio->addAudioEvent(&fadeAudioEvent);
			debris->getDrawable()->fadeOut(m_fadeFrames);
		}

		debris->getDrawable()->rva00274176(true);
	}

	if (container)
	{
		doStuffToObj(container, AsciiString::TheEmptyString, pos, mtx, orientation, sourceObj, lifetimeFrames, 0);
		container->setProducer((Object *)sourceObj);
	}

	return objects;
}
