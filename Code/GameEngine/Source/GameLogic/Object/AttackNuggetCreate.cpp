// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/ocls /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// ?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1M@Z, retail 0x001F0AD4, 262 bytes.
// Gap in ObjectCreationList.cpp between the two addObjectCreationNugget rows.
// Direct port of that TU's AttackNugget::create with BFME2 deltas proven by retail:
// setWeaponLock slot+0x40 then inline aiAttackPosition (parms ctor 0x351BD0 builds
// 0xC0 block, 3x movsd pos, int at +0x34, slot-0 aiDoCommand, inline free teardown),
// static NAMEKEY RadiusDecalUpdate via TheNameKeyGenerator, findModule, createRadiusDecal.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#pragma warning(disable : 4716)

struct Coord3D { Real x; Real y; Real z; };

class Object;
class Team;
class Waypoint;
class PolygonTrigger;

enum AICommandType { AICMD_ATTACK_POSITION = 0x0E };
enum CommandSourceType { CMD_FROM_AI = 2 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum WeaponLockType { LOCKED_TEMPORARILY = 1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

typedef int NameKeyTypeHack;

extern "C" void free(void *block);

class Rva003427DD { public: Rva003427DD &operator=(const Rva003427DD &src); private: char m_data[0x7C]; };
class Rva0035149F { public: void *m_start; void *m_finish; void *m_end; };

struct AICommandParms {
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms();
	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const void *m_team;
	void *m_coordsStart;
	void *m_coordsFinish;
	void *m_coordsEnd;
	const Waypoint *m_waypoint;
	const void *m_polygon;
	Int m_intValue;
	float m_float38;
	Rva003427DD m_3C;
	char m_tailPad[0xC0 - 0x3C - 0x7C];
};

class AICommandInterface {
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiAttackPositionInlined(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);	// retail inlines aiAttackPosition here; a unit-local name keeps a second copy of it out of the link
};

// ?aiAttackPositionInlined@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z absent-from-retail
__forceinline void AICommandInterface::aiAttackPositionInlined(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_ATTACK_POSITION, cmdSource);
	parms.m_pos = *pos;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

class AIUpdateInterface : public AICommandInterface {};

class RadiusDecalTemplate {
public:
	static void parseRadiusDecalTemplate(void*, void*, void*, const void*);
private:
	unsigned char m_opaque[0x34];
};

class RadiusDecalUpdate;
class Module {};

class Object {
public:
	char *getContainer258() { return *(char**)((char*)this + 0x258); }
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
protected:
	Module *findModule(NameKeyType key) const;
};
struct ObjectHack : public Object {
	static Module *find(const Object *o, NameKeyType k) { return ((ObjectHack*)o)->findModule(k); }
};

class NameKeyGenerator {
public:
	NameKeyType nameToKey(const char *str);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern unsigned int g_Va00DFDCD8;
extern unsigned int g_00DFDCD4;

class RadiusDecalUpdate : public Module {
public:
	void createRadiusDecal(const RadiusDecalTemplate &tmpl, Real radius, const Coord3D &pos);
	void killWhenNoLongerAttacking(bool k) { m_kill = k; }
private:
	unsigned char m_pad[0x30];
	bool m_kill;
};

class NuggetBase { public: virtual ~NuggetBase(); };

class AttackNugget : public NuggetBase {
public:
	virtual Object *create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, Real angle) const;
private:
	RadiusDecalTemplate m_template;
	Real m_radius;
	Int m_shots;
	WeaponSlotType m_slot;
};

Object *AttackNugget::create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, Real angle) const
{
	if (primaryObj && primary && secondary)
	{
		Object *obj = const_cast<Object*>(primaryObj);
		char *container = obj->getContainer258();
		if (container) {
			obj->setWeaponLock(m_slot, LOCKED_TEMPORARILY);
			Int shots = m_shots;
			AIUpdateInterface *ai = (AIUpdateInterface*)(container + 0x20);
			ai->aiAttackPositionInlined(secondary, shots, CMD_FROM_AI);
		}
		static NameKeyType key_RadiusDecalUpdate = TheNameKeyGenerator->nameToKey("RadiusDecalUpdate");
		RadiusDecalUpdate *rd = (RadiusDecalUpdate*)ObjectHack::find(obj, key_RadiusDecalUpdate);
		if (rd) {
			rd->createRadiusDecal(m_template, m_radius, *secondary);
			rd->killWhenNoLongerAttacking(true);
		}
	}
}
