// ?isFlankedBy@HordeContain@@UAE_NPAVObject@@@Z
// partial score=0.85 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
// stlport
//
#include "ascii_string.h"
#include <list>
#include <map>
#include <set>
#include <vector>
#include <math.h>
struct Coord3D
{
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
	float Normalize();
	void set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
	float x;
	float y;
	float z;
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum ObjectID
{
	INVALID_ID = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
extern const int g_009BA4E4;
float Sin(float x);
float Cos(float x);
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class Object;
class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void rva0037379B(Object *obj, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(int a1, CommandSourceType cmdSource);
	void rva0026C2D9(Object *obj, int a2, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
};
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
#define HORDECONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
class Player;
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
struct Rva002A8AB1Record
{
	void rva002C6AA8(int value, Object *obj);
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;
class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *object);
	void RemoveObjectGoalFromPathfindMap(Object *object);
};
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};
class AIGroup
{
public:
	void add(Object *obj);
	void rva00372571(Rva00372571Params *params, int source);
};
class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *group);
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class Team;
struct Vector4
{
	Vector4() {}
	__forceinline Vector4 &operator=(const Vector4 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
		return *this;
	}
	float X;
	float Y;
	float Z;
	float W;
};
class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
	}
	Vector4 Row[3];
};
class Drawable
{
public:
	void rva00272BE7();
	void rva00272BAB(int a1, int a2);
};
class Thing
{
public:
	void setOrientation(float angle);
	const Coord3D *getUnitDirectionVector2D() const;
	Drawable *getDrawable() const;
};
class GlobalData
{
public:
	unsigned char m_pad000[0x9A6];
	bool m_9A6; // +0x9A6
};
extern GlobalData *TheWritableGlobalData;
class Player;
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;
class BfmeThingTFB
{
public:
	void bfmeTwoTFB(int a1, int a2);
};
class BfmeArg985
{
public:
	char bfmeHas985C(int a1);
};
struct Rva003642DFNode;
struct Rva003642DFResult;
struct Rva00468C37Holder;
class Rva003638BA
{
public:
	bool rva003638BA();
	bool rva00363AD7();
	Rva003642DFResult rva00364521(Rva00468C37Holder *holder);
};
struct Rva003642DFResult
{
	Rva003642DFNode *m_node; // +0x00
	Coord3D m_pos; // +0x04
};
struct Rva003642DFNode
{
	unsigned char m_pad00[0x08];
	int m_08; // +0x08
};
class Rva001E3511
{
public:
	int rva001E3511();
};
struct Rva00468C37Template
{
	unsigned char m_pad000[0x150];
	unsigned char m_150; // +0x150
};
struct Rva00468C37Holder
{
	unsigned char m_pad0[0x4];
	const Rva00468C37Template *m_4; // +0x04
};
template <int N> class Rva00468D11Slots : public Rva00468D11Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00468D11Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
class TerrainLogic : public Rva00468D11Slots<35>
{
public:
	virtual int slot35(int level) = 0;
};
extern TerrainLogic *TheTerrainLogic;
class Rva0028C197Slot149 : public Rva00468D11Slots<149>
{
public:
	virtual bool slot149() = 0;
};
class AIUpdateInterfaceSlots : public Rva00468D11Slots<110>
{
public:
	virtual bool rva0047306ESlot110() = 0;
	virtual bool rva0046A46FSlot111() = 0;
	virtual void gap112() = 0;
	virtual bool rva0047306ESlot113() = 0;
	virtual bool rva00468D11Slot114() = 0;
	virtual bool rva00468D2CSlot115() = 0;
	virtual void gap116() = 0; virtual void gap117() = 0; virtual void gap118() = 0; virtual void gap119() = 0;
	virtual void gap120() = 0; virtual void gap121() = 0; virtual void gap122() = 0; virtual void gap123() = 0;
	virtual void gap124() = 0; virtual void gap125() = 0; virtual void gap126() = 0; virtual void gap127() = 0;
	virtual void gap128() = 0; virtual void gap129() = 0; virtual void gap130() = 0; virtual void gap131() = 0;
	virtual void gap132() = 0; virtual void gap133() = 0;
	virtual void rva0046DDC5Slot134(int a1, int a2) = 0;
};
class AIUpdateInterface : public AIUpdateInterfaceSlots
{
public:
	bool isMoving() const;
	void rva00262D2D();
	Object *getCurrentVictim() const;
	int rva00260DED() const;
	unsigned char m_pad004[0x20 - 0x04];
	AICommandInterface m_command; // +0x20
	void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }
	unsigned char m_pad024[0x140 - 0x24];
	Rva003638BA *m_140; // +0x140
	unsigned char m_pad144[0x1F0 - 0x144];
	Rva00468C37Holder *m_1F0; // +0x1F0
	unsigned char m_pad1F4[0x1FC - 0x1F4];
	int m_1FC; // +0x1FC
};
class ModuleData;
class ModuleInfo
{
public:
	struct Entry
	{
		unsigned char m_pad[0x14];
	};
	int getCount() const { return m_end - m_begin; }
	const ModuleData *getNthData(int i) const;
	Entry *m_begin; // vector<Entry>
	Entry *m_end;
	Entry *m_cap;
};
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x114];
	unsigned int m_kindOf[4]; // +0x114
	unsigned char m_pad124[0x2E4 - 0x124];
	ModuleInfo m_moduleInfo; // +0x2E4
	unsigned char m_pad2F0[0x5D8 - 0x2F0];
	short m_5D8; // +0x5D8
};
struct Rva00469689Body
{
	unsigned char m_pad00[0x10];
	float m_10; // +0x10
};
class Rva0046B850Module : public Rva00468D11Slots<5>
{
public:
	virtual float slot5() = 0;
	virtual void m254gap6() = 0; virtual void m254gap7() = 0; virtual void m254gap8() = 0; virtual void m254gap9() = 0;
	virtual void m254gap10() = 0; virtual void m254gap11() = 0; virtual void m254gap12() = 0; virtual void m254gap13() = 0;
	virtual void m254gap14() = 0; virtual void m254gap15() = 0; virtual void m254gap16() = 0; virtual void m254gap17() = 0;
	virtual ObjectID slot18() = 0;
};
class Rva0046A2ECContain : public Rva00468D11Slots<58>
{
public:
	virtual bool slot58(Object *other) = 0;
};
class Object
{
public:
	int getID() const { return m_74; }
	__forceinline unsigned int testCondition(int bit) const
	{
		return m_conditionWords[bit >> 5] & (1U << (bit & 0x1f));
	}
	__forceinline void clearCondition(int bit)
	{
		m_conditionWords[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	bool test110(int bit) const { return ((m_110 >> bit) & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	void *rva0028C197() const;
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	int m_74; // +0x74
	unsigned char m_pad078[0xB8 - 0x78];
	float m_B8; // +0xB8
	unsigned char m_padBC[0x10C - 0xBC];
	union
	{
		unsigned int m_conditionWords[2]; // +0x10C (model-condition bits)
		struct
		{
			unsigned int m_10C;
			unsigned int m_110; // +0x110
		};
	};
	unsigned char m_pad114[0x250 - 0x114];
	Rva0046A2ECContain *m_250; // +0x250
	Rva0046B850Module *m_254; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x264 - 0x25C];
	const Rva00469689Body *m_264; // +0x264
	unsigned char m_pad268[0x274 - 0x268];
	Object *m_274; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	int m_304; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_438; // +0x438
	unsigned char m_pad439[0x44C - 0x439];
	int m_44C; // +0x44C
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Object *rva002931F5(bool flag);
	bool rva0028D9E5(int a1) const;
	void setTeam(Team *team);
	bool testStatus(ObjectStatusTypes bit) const;
	void clearModelConditionStateForHorde(ModelConditionFlagType flag);
	void setModelConditionStateForHorde(ModelConditionFlagType flag);
	void rva001E42F2(const int *value);
	void rva0028B95F();
	unsigned char rva00290FBB() const;
	void rva0028AE6D();
	void setTransformMatrix(const Matrix3D *mtx);
	float GetRelativeAngle(const Coord3D *pos) const;
	bool rva0028C264(int *out, int a2);
	Player *getControllingPlayer() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern class ThingFactory *TheThingFactory;
struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};
struct Rva00462D35Mapped
{
	unsigned int m_bits;
};
class Rva00469294
{
public:
	void *rva00469294(int key);
};
struct Rva00472329Record
{
	int m_key; // +0x00
	unsigned char m_pad04[0x1C - 0x04];
};
class Rva004695DA
{
public:
	unsigned char rva004695DA();
};
class Rva0046247D
{
public:
	void rva0046247D(Rva0046247DPair &p);
};
class Rva00468FDCHelper : public Rva00468D11Slots<3>
{
public:
	virtual void slot3(Object *target) = 0;
	virtual void rva00468FDCSlot4() = 0;
	virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0; virtual void gap8() = 0;
	virtual void gap9() = 0; virtual void gap10() = 0; virtual void gap11() = 0; virtual void gap12() = 0;
	virtual void gap13() = 0;
	virtual bool rva00468DCDSlot14(Object *obj) = 0;
};
struct Rva00468CA3Arg
{
	unsigned char m_pad00[0x38];
	void *m_38; // +0x38
};
class HordeContainModuleData
{
public:
	unsigned char m_pad[0xA4];
	_STL::list<AsciiString> m_A4; // +0xA4
};
struct Rva004698BCVector
{
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	void **m_begin;
	void **m_end;
	void **m_cap;
};
struct Rva00469851Names
{
	const AsciiString *begin() const { return m_begin; }
	const AsciiString *end() const { return m_end; }
	const AsciiString *m_begin;
	const AsciiString *m_end;
	const AsciiString *m_cap;
};
struct HordeContainModuleDataFields
{
	unsigned char m_pad000[0x98];
	int m_98; // +0x98
	unsigned char m_pad09C[0x18C - 0x9C];
	unsigned char m_18C[0x0C]; // +0x18C (address handed out by slot 129)
	unsigned char m_pad198[0x1A4 - 0x198];
	Rva004698BCVector m_1A4; // +0x1A4
	AsciiString m_1B0; // +0x1B0
	unsigned char m_pad1B4[0x1B8 - 0x1B4];
	_STL::map<int, int> m_1B8; // +0x1B8
	unsigned char m_pad1C4[0x1D8 - 0x1C4];
	bool m_1D8; // +0x1D8
	unsigned char m_pad1D9[0x224 - 0x1D9];
	union
	{
		struct
		{
			const AsciiString *m_224Begin; // +0x224 (vector)
			const AsciiString *m_224End;
			const AsciiString *m_224Cap;
		};
		Rva00469851Names m_224;
	};
	bool m_230; // +0x230
	unsigned char m_pad231[0x254 - 0x231];
	bool m_254; // +0x254
	unsigned char m_pad255[0x25C - 0x255];
	float m_25C; // +0x25C (a flank arc, degrees)
	unsigned char m_pad260[0x264 - 0x260];
	unsigned int m_264; // +0x264 (a frame count)
	unsigned int m_268; // +0x268
	float m_26C; // +0x26C
	float m_270; // +0x270
};
struct HordeContainModuleDataFields;
class ModuleData : public Rva00468D11Slots<21>
{
public:
	virtual const HordeContainModuleDataFields *slot21() const = 0;
};
template <int N> class Rva0046BB38Slots : public Rva0046BB38Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046BB38Slots<0>
{
};
class Rva0046BB38Iface6 : public Rva0046BB38Slots<0>
{
public:
	virtual void rva00472329(const Coord3D *pos, int unused) = 0;
	virtual void gap1() = 0; virtual void gap2() = 0; virtual void rva0046E253() = 0; virtual void gap4() = 0; virtual void gap5() = 0;
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void assignSpotToUnit(Object *obj) = 0; virtual void gap12() = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void slot16() = 0; virtual void rva0046FE99(_STL::list<Object *> &out) = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual void gap20() = 0; virtual Object *rva0046CBCA() = 0;
	virtual void *rva004696CD() = 0; virtual bool rva0046CDC9() = 0; virtual void rva004696E5() = 0; virtual bool rva0046CCEF(const ThingTemplate *tmpl) = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup) = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void gap30() = 0; virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3) = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual bool rva0046A2A7() = 0;
	virtual void gap38() = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void slot42(const Object *obj) = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void gap46() = 0; virtual void gap47() = 0; virtual void gap48() = 0; virtual void gap49() = 0;
	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void gap53() = 0;
	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual void gap62() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual void gap66() = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual void gap69() = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void startMeleeAttack(Object *target) = 0;
	virtual void rva00468FDC() = 0; virtual void rva00473ADF() = 0; virtual bool rva0046A381(Object *target) = 0; virtual bool rva0046A46F() = 0;
	virtual bool rva0046A2EC(Object *target) = 0; virtual bool rva0046A416() = 0; virtual bool canEngageInMelee(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void rva004730B0(Object *target) = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual void gap99() = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void rva0046A78F(const Matrix3D *mtx) = 0;
	virtual void rva0046A712(int unused) = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
	virtual void rva0046DB6D(const AsciiString &name, int a2, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, int a2) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
	virtual void rva00469851() = 0; virtual void rva0046DE2D(const FXList *fx) = 0; virtual void gap124() = 0; virtual bool rva0046992C() = 0;
	virtual void gap126() = 0; virtual bool rva004698BC() = 0; virtual const void *rva004698D6() = 0; virtual const void *rva004698E2() = 0;
	virtual void gap130() = 0; virtual void gap131() = 0; virtual void rva004690A9(const Coord3D *pos) = 0; virtual void gap133() = 0;
	virtual void gap134() = 0; virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after) = 0; virtual bool rva0046F8CD() = 0; virtual void gap137() = 0;
	virtual ObjectID rva0046DEA1(ObjectID want) = 0; virtual void gap139() = 0; virtual bool rva0046E113(Coord3D *center) = 0; virtual void rva004690D0(int value) = 0;
	virtual bool rva00468C37() = 0; virtual void rva00468BDC(int on) = 0;
	virtual float rva00468B5B(float value) = 0;
	virtual void rva00468C60(const Coord3D *pos) = 0;
	virtual bool rva00468C7B(Coord3D *pos) = 0;
	virtual bool isFlankedBy(Object *attacker) = 0;
	virtual void rva0046E2BC() = 0;
	virtual void gap149() = 0;
	virtual float rva0046F8DA() = 0;
	virtual float rva0046F8E7() = 0;
	virtual void gap152() = 0;
	virtual float rva0046B850() = 0;
	virtual void endMove() = 0;
};
class UpdateModule : public Rva00468D11Slots<32>
{
public:
	virtual void slot32(Object *obj) = 0;
	virtual void slot33(int a1) = 0;
	virtual void rva0046AF85() = 0;
	virtual void gap35() = 0;
	virtual void gap36() = 0;
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
	unsigned char m_pad14[0x20 - 0x14];
};
typedef void (*ContainIterateFunc)(Object *obj, void *userData);
class ContainModuleInterface : public Rva00468D11Slots<38>
{
public:
	virtual bool slot38(Object *obj, int a2, int a3) = 0;
	virtual void cgap39() = 0; virtual void cgap40() = 0; virtual void slot41(const Object *obj, int a2) = 0; virtual void cgap42() = 0; virtual void cgap43() = 0; virtual void cgap44() = 0; virtual void cgap45() = 0; virtual void cgap46() = 0; virtual void cgap47() = 0; virtual void cgap48() = 0; virtual void cgap49() = 0; virtual void cgap50() = 0; virtual void cgap51() = 0; virtual void cgap52() = 0; virtual void cgap53() = 0; virtual void cgap54() = 0; virtual void cgap55() = 0; virtual void cgap56() = 0; virtual void cgap57() = 0; virtual void cgap58() = 0; virtual void cgap59() = 0; virtual void cgap60() = 0; virtual void cgap61() = 0; virtual void cgap62() = 0; virtual void cgap63() = 0; virtual void cgap64() = 0; virtual void cgap65() = 0; virtual void cgap66() = 0; virtual void cgap67() = 0;
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);	// slot 68; the base body is 0x004635EC
	virtual int slot69(int a1) = 0;
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
};
class TransportContain : public UpdateModule, public BehaviorModuleInterface, public UpdateModuleInterface, public ContainModuleInterface
{
public:
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual void gatherUnitBack(Object *obj) = 0;
private:
	unsigned char m_pad024[0x11C - 0x24];
};
struct HordeBannerCarrierUpdateData
{
	unsigned char m_pad00[0x10];
	int m_value;						// +0x10
};
struct HordeBannerCarrierUpdate
{
	void *m_vtbl;
	const HordeBannerCarrierUpdateData *m_data;		// +0x04
};
class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
	void rva00468B24(float value);
	void checkSpecialUnitDeath(Object *obj);
	void *rva0046AF12();
	int getBannerCarrierIndexToUse(const Object *obj, const ThingTemplate **outTemplate);
	HordeBannerCarrierUpdate *rva00468E26(Object *obj);	// 0x00468E26, banner carrier update lookup
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);
	virtual bool rva0046BB38(Object *other);
	virtual void rva0046FE99(_STL::list<Object *> &out);
	virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after);
	virtual bool isFlankedBy(Object *attacker);
	virtual AsciiString rva0046D1AC();
	virtual void rva0046F7C9(Object *obj);
	virtual int rva0046979B();
	virtual void *rva004696CD();
	virtual void rva004696E5();
	virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource);
	virtual bool rva00468D11();
	virtual bool rva00468D2C();
	virtual bool rva0046F8A5();
	virtual bool rva0046F8F4();
	virtual Object *rva0046D372();
	virtual void rva0046F8B2();
	virtual int rva004697CD();
	virtual int rva00468F68();
	virtual int rva00468F7E();
	virtual bool rva004698BC();
	virtual const void *rva004698D6();
	virtual const void *rva004698E2();
	virtual void rva004690A9(const Coord3D *pos);
	virtual bool rva0046F8CD();
	virtual bool rva00468C37();
	virtual void rva00468C60(const Coord3D *pos);
	virtual bool rva00468C7B(Coord3D *pos);
	virtual float rva0046F8DA();
	virtual float rva0046F8E7();
	virtual bool rva0046C6E7();
	virtual void rva00468FDC();
	virtual bool rva0046A46F();
	virtual bool rva0046A416();
	virtual bool canEngageInMelee(Object *obj, int a2);
	virtual bool rva00468DCD(Object *obj);
	virtual bool rva0046A4C8();
	virtual void rva00468D7D(Object *obj);
	virtual void rva0046981C();
	virtual void rva00469851();
	virtual void rva00468BDC(int on);
	virtual void rva0046AF85();
	virtual void rva00473ADF();
	virtual bool rva0046A6C1();
	virtual bool rva0046A677();
	virtual Object *rva0046D27A();
	virtual void rva0046D7AF(int a1);
	virtual void rva0046DDC5(int a1, int a2);
	virtual void rva0046D384(Team *team);
	virtual void rva004730B0(Object *target);
	virtual void rva0046DE2D(const FXList *fx);
	virtual void rva0046A712(int unused);
	virtual bool rva0046C5D7(int value);
	virtual bool rva0046A2EC(Object *target);
	virtual bool rva0046A381(Object *target);
	virtual void rva0046BD70();
	virtual void rva0046BE0E();
	virtual void rva0046D8AE();
	virtual Object *rva0046CB2C();
	virtual bool rva0046D80B();
	virtual bool rva0046BB6F(int *out, unsigned int frame);
	virtual int rva0046D3FC(Rva2225E0Filter *filter);
	virtual bool rva0046A2A7();
	virtual void rva0046E2BC();
	virtual void endMove();
	virtual bool rva0046992C();
	virtual Object *rva0046CBCA();
	virtual void rva0046C327();
	virtual void rva0046C20B();
	virtual ObjectID rva0046DEA1(ObjectID want);
	virtual void rva0046A78F(const Matrix3D *mtx);
	virtual void rva00472329(const Coord3D *pos, int unused);
	virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3);
	virtual void slot42(const Object *obj);
	virtual void assignSpotToUnit(Object *obj);
	virtual void startMeleeAttack(Object *target);
	virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup);
	virtual float rva0046B850();
	virtual void rva0046D1F7(_STL::list<const Object *> &out);
	virtual void rva0046E253();
	virtual bool rva0046CDC9();
	virtual bool rva0046CCEF(const ThingTemplate *tmpl);
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual bool rva0046B9DC(int a1);
	virtual bool rva0046B95E(int a1);
private:
	__forceinline const _STL::list<Object *> *containedItems()
	{
		Rva0046247DPair p;
		((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
		return p.m04;
	}
	const HordeContainModuleDataFields *fields() const { return (const HordeContainModuleDataFields *)m_moduleData; }
	bool m_120; // +0x120
	bool m_121; // +0x121
	unsigned char m_pad122[0x170 - 0x122];
	_STL::set<int> m_170; // +0x170 (Object IDs)
	_STL::map<int, int> m_17C; // +0x17C
	Rva00472329Record *m_188Begin; // +0x188 (vector of 0x1C-byte records)
	Rva00472329Record *m_188End;
	Rva00472329Record *m_188Cap;
	_STL::list<int> m_194; // +0x194 (free +0x188 record indices)
	bool m_198; // +0x198
	unsigned char m_pad199[0x19C - 0x199];
	int m_19C; // +0x19C
	unsigned char m_pad1A0[0x1AC - 0x1A0];
	ObjectID m_1AC; // +0x1AC
	ObjectID m_1B0; // +0x1B0
	int m_1B4; // +0x1B4
	unsigned char m_pad1B8[0x200 - 0x1B8];
	int m_200; // +0x200
	unsigned char m_pad204[0x24C - 0x204];
	_STL::map<int, void *> m_24C; // +0x24C
	unsigned char m_pad258[0x264 - 0x258];
	void *m_264; // +0x264
	unsigned char m_pad268[0x26C - 0x268];
	ObjectID m_26C; // +0x26C
	struct BannerIndexEntry
	{
		const ThingTemplate *m_template;
		int m_index;
	};
	_STL::vector<BannerIndexEntry *> m_bannerIndices; // +0x270
	int m_27C; // +0x27C (the banner carrier's value)
	unsigned char m_pad280[0x288 - 0x280];
	int m_288; // +0x288 (an Object ID)
	unsigned int m_28C; // +0x28C (a logic frame)
	unsigned char m_pad290[0x294 - 0x290];
	bool m_294; // +0x294
	unsigned char m_pad295[0x298 - 0x295];
	unsigned int m_298; // +0x298 (a frame count, -1 for none)
	int m_29C; // +0x29C
	int m_2A0; // +0x2A0
	bool m_2A4; // +0x2A4
	unsigned char m_pad2A5[0x2B8 - 0x2A5];
	Coord3D m_2B8; // +0x2B8
	bool m_2C4; // +0x2C4
	unsigned char m_pad2C5[0x2C8 - 0x2C5];
	Rva00468FDCHelper *m_2C8; // +0x2C8
	float *m_2CCBegin; // +0x2CC (vector<float> of angles)
	float *m_2CCEnd;
	float *m_2CCCap;
	unsigned char m_pad2D8[0x2DC - 0x2D8];
	_STL::map<int, Rva00462D35Mapped> m_2DC; // +0x2DC
	bool m_2E8; // +0x2E8
	unsigned char m_pad2E9[0x2EC - 0x2E9];
	float m_2EC; // +0x2EC
	int m_2F0; // +0x2F0
	unsigned char m_pad2F4[0x2F8 - 0x2F4];
	Coord3D m_2F8; // +0x2F8
	bool m_304; // +0x304
};
bool HordeContain::rva0046BB38(Object *other)
{
	if (other->m_274 == m_object)
		return true;
	if (m_170.find(other->getID()) != m_170.end())
		return true;
	return false;
}
AsciiString HordeContain::rva0046D1AC()
{
	const HordeContainModuleData *data = (const HordeContainModuleData *)m_moduleData;
	return data->m_A4.size() == 1 ? data->m_A4.front() : AsciiString::TheEmptyString;
}
void HordeContain::rva0046F7C9(Object *obj)
{
	gatherUnitBack(obj);
}
int HordeContain::rva0046979B()
{
	return fields()->m_98;
}
void *HordeContain::rva004696CD()
{
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
}
void HordeContain::rva004696E5()
{
	void *thingTemplate = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
	if (thingTemplate)
		rva00472D43(thingTemplate);
}
void HordeContain::rva00472C8E(Object *obj, CommandSourceType cmdSource)
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (ai)
		ai->m_command.rva0037379B(obj, cmdSource);
}
bool HordeContain::rva00468D11()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (!ai)
		return false;
	return ai->rva00468D11Slot114();
}
bool HordeContain::rva00468D2C()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (!ai)
		return false;
	return ai->rva00468D2CSlot115();
}
bool HordeContain::rva0046F8A5()
{
	return fields()->m_1D8;
}
bool HordeContain::rva0046F8F4()
{
	return fields()->m_230;
}
Object *HordeContain::rva0046D372()
{
	return TheGameLogic->findObjectByID(m_26C);
}
void HordeContain::rva0046F8B2()
{
	m_2A4 = false;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
int HordeContain::rva004697CD()
{
	const HordeContainModuleDataFields *data = fields();
	if (data)
		return data->m_98;
	return 0;
}
int HordeContain::rva00468F68()
{
	int count = 0;
	if (m_264)
		++count;
	if (m_26C)
		++count;
	return count;
}
int HordeContain::rva00468F7E()
{
	return rva0046D3FC(0) - rva00468F68();
}
bool HordeContain::rva004698BC()
{
	return fields()->m_1A4.size() > 0 ? true : false;
}
const void *HordeContain::rva004698D6()
{
	return &fields()->m_1A4;
}
const void *HordeContain::rva004698E2()
{
	return fields()->m_18C;
}
void HordeContain::rva004690A9(const Coord3D *pos)
{
	m_2B8 = *pos;
	m_2C4 = true;
	m_120 = true;
}
bool HordeContain::rva0046F8CD()
{
	return fields()->m_254;
}
bool HordeContain::rva00468C37()
{
	return m_object->m_ai->m_1F0->m_4->m_150 && m_2F0;
}
void HordeContain::rva00468C60(const Coord3D *pos)
{
	m_2F8 = *pos;
	m_304 = true;
}
bool HordeContain::rva00468C7B(Coord3D *pos)
{
	if (m_304)
	{
		m_304 = false;
		*pos = m_2F8;
		return true;
	}
	return false;
}
float HordeContain::rva0046F8DA()
{
	return fields()->m_26C;
}
float HordeContain::rva0046F8E7()
{
	return fields()->m_270;
}
bool HordeContain::rva0046C6E7()
{
	for (_STL::set<int>::iterator it = m_170.begin(); it != m_170.end(); ++it)
	{
		if (TheGameLogic->findObjectByID((ObjectID)*it))
			return true;
	}
	return false;
}
void HordeContain::rva00468FDC()
{
	m_2A0 = 0;
	m_288 = 0;
	m_28C = 0;
	m_294 = true;
	m_2C8->rva00468FDCSlot4();
	if (m_120)
		m_121 = true;
}
bool HordeContain::rva0046A46F()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && ai->rva0046A46FSlot111())
				return true;
		}
	}
	return false;
}
bool HordeContain::rva0046A416()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && !ai->rva0046A46FSlot111())
				return false;
		}
	}
	return true;
}
bool HordeContain::rva0046A4C8()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai && ai->rva0046A46FSlot111() && obj->testStatus((ObjectStatusTypes)0x1C))
			return true;
	}
	return false;
}
bool HordeContain::canEngageInMelee(Object *obj, int)
{
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return false;
	if (ai->rva0047306ESlot113())
	{
		ai->aiIdle(CMD_FROM_AI);
		return true;
	}
	return ai->rva0047306ESlot110() ? true : false;
}
bool HordeContain::rva00468DCD(Object *obj)
{
	if (!obj)
		return false;
	int id = obj->m_74;
	Object *other = obj->rva002931F5(false);
	if (other)
		id = other->m_74;
	if ((obj->m_74 == m_288 || id == m_288) && TheGameLogic->m_frame < m_28C)
		return true;
	return m_2C8->rva00468DCDSlot14(obj);
}
void HordeContain::rva00468D7D(Object *obj)
{
	if (!obj)
		return;
	int id = obj->m_74;
	unsigned int delay = g_009BA4E4 * 3;
	Object *other = obj->rva002931F5(false);
	if (other)
		id = other->m_74;
	if (obj->m_74 == m_288 || id == m_288)
		m_28C = TheGameLogic->m_frame + delay;
}
void HordeContain::rva0046981C()
{
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	for (const AsciiString *it = data->m_224Begin; it != data->m_224End; ++it)
		rva0046DB6D(*it, 0, -1);
}
void HordeContain::rva00469851()
{
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	const AsciiString *it = data->m_224Begin;
	const AsciiString *const *end = &data->m_224End;
	for (; it != *end; ++it)
		rva0046DC92(*it, 0);
}
void HordeContain::rva00468BDC(int on)
{
	Object *obj = m_object;
	if (!obj || !obj->m_ai)
		return;
	if (on)
	{
		if (!m_2F0)
			obj->setModelConditionStateForHorde((ModelConditionFlagType)0x1BA);
	}
	else
	{
		obj->clearModelConditionStateForHorde((ModelConditionFlagType)0x1BA);
		obj->clearModelConditionStateForHorde((ModelConditionFlagType)0x1BB);
	}
	m_2F0 = on;
}
void HordeContain::rva0046AF85()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_17C.find(obj->getID()) == m_17C.end())
			assignSpotToUnit(obj);
	}
}
void HordeContain::rva00473ADF()
{
	if (m_2A0)
		rva00468FDC();
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		AIUpdateInterface *ai = (*it)->m_ai;
		if (ai)
			ai->m_command.rva0045003E(0, CMD_FROM_AI);
	}
}
bool HordeContain::rva0046A6C1()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Rva003638BA *member = obj->m_ai->m_140;
			if (member && member->rva003638BA())
				return true;
		}
	}
	return false;
}
bool HordeContain::rva0046A677()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai->m_140 && ai->m_1FC == 4)
				return false;
		}
	}
	return true;
}
Object *HordeContain::rva0046D27A()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	if (!p.m04->empty())
		return p.m04->front();
	_STL::set<int>::iterator it = m_170.begin();
	if (it != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)*it);
	return 0;
}
void HordeContain::rva0046D7AF(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_170.find(obj->getID()) == m_170.end())
			((BfmeThingTFB *)obj)->bfmeTwoTFB(a1, 0);
	}
}
void HordeContain::rva0046DDC5(int a1, int a2)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); )
	{
		Object *obj = *it;
		int id = obj->getID();
		++it;
		if (m_170.find(id) == m_170.end())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
				ai->rva0046DDC5Slot134(a1, a2);
		}
	}
}
void HordeContain::rva0046D384(Team *team)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
			obj->setTeam(team);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			obj->setTeam(team);
	}
}
bool HordeContain::rva0046B9DC(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if (((BfmeArg985 *)*it)->bfmeHas985C(a1))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (((BfmeArg985 *)obj)->bfmeHas985C(a1))
			return true;
	}
	return false;
}
bool HordeContain::rva0046B95E(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if ((*it)->rva0028D9E5(a1))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->rva0028D9E5(a1))
			return true;
	}
	return false;
}
void HordeContain::rva004730B0(Object *target)
{
	if (!target)
		return;
	if (!m_object->testStatus((ObjectStatusTypes)0x4B))
		return;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		AIUpdateInterface *ai = (*it)->m_ai;
		if (ai && !ai->rva0046A46FSlot111())
			ai->m_command.rva0026C2D9(target, 0x7FFFFFFF, CMD_FROM_AI);
	}
}
void HordeContain::rva0046DE2D(const FXList *fx)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		FXList::doFXObj(fx, *it, 0);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
		FXList::doFXObj(fx, TheGameLogic->findObjectByID((ObjectID)*k), 0);
}
void HordeContain::rva0046A712(int)
{
	slot16();
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		float angle;
		Coord3D pos;
		pos = slot7(obj, &angle);
		((BfmeThingTFB *)obj)->bfmeTwoTFB((int)&pos, 0);
		((Thing *)obj)->setOrientation(angle);
	}
}
bool HordeContain::rva0046C5D7(int value)
{
	if (!value)
		return false;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && obj->m_44C == value)
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->m_44C == value)
			return true;
	}
	return false;
}
bool HordeContain::rva0046A2EC(Object *target)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				if (!ai->rva0046A46FSlot111())
					return false;
				Object *victim = ai->getCurrentVictim();
				if (!victim)
					return false;
				if (victim->getID() != target->getID())
					return false;
				if (target->isKindOf(13) && !target->m_250->slot58(victim))
					return false;
			}
		}
	}
	return true;
}
bool HordeContain::rva0046A381(Object *target)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && ai->rva0046A46FSlot111())
			{
				Object *victim = ai->getCurrentVictim();
				if (victim)
				{
					if (victim->getID() == target->getID())
						return true;
					if (target->isKindOf(13) && target->m_250->slot58(victim))
						return true;
				}
			}
		}
	}
	return false;
}
void HordeContain::rva0046BD70()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectFromPathfindMap(obj);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectFromPathfindMap(obj);
	}
}
void HordeContain::rva0046BE0E()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectGoalFromPathfindMap(obj);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectGoalFromPathfindMap(obj);
	}
}
void HordeContain::rva0046D8AE()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		(*it)->rva001E42F2(&m_200);
	m_24C.clear();
	GameLogic *logic = TheGameLogic;
	Object *first = logic->findObjectByID(m_1AC);
	Object *second = logic->findObjectByID(m_1B0);
	if (first)
		first->rva001E42F2(&m_1B4);
	if (second)
		second->rva001E42F2(&m_1B4);
	m_1AC = INVALID_ID;
}
Object *HordeContain::rva0046CB2C()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	if (p.m04->empty())
	{
		if (m_170.size() == 0)
			return 0;
		_STL::set<int>::iterator k = m_170.begin();
		for (int n = GetGameLogicRandomValue(0, m_170.size() - 1, HORDECONTAIN_SOURCE_FILE, 5377); n != 0; --n)
			++k;
		return TheGameLogic->findObjectByID((ObjectID)*k);
	}
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	for (int n = GetGameLogicRandomValue(0, p.m04->size() - 1, HORDECONTAIN_SOURCE_FILE, 5383); n != 0; --n)
		++it;
	return *it;
}
bool HordeContain::rva0046D80B()
{
	const _STL::list<Object *> *items = containedItems();
	const Coord3D *src = m_object->getPosition();
	Coord3D pos;
	pos.x = src->x;
	pos.y = src->y;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_170.find(obj->getID()) == m_170.end())
		{
			float dx = pos.x - obj->getPosition()->x;
			float dy = pos.y - obj->getPosition()->y;
			if (dy * dy + dx * dx > 100.0f)
				return false;
		}
	}
	return true;
}
bool HordeContain::rva0046BB6F(int *out, unsigned int frame)
{
	*out = 0;
	unsigned int now = TheGameLogic->m_frame;
	if (frame >= now)
		return false;
	if (m_298 != (unsigned int)-1 && m_298 + frame >= now)
	{
		*out = m_29C;
		return true;
	}
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj && obj->rva0028C264(out, 4))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->rva0028C264(out, 4))
			return true;
	}
	return false;
}
int HordeContain::rva0046D3FC(Rva2225E0Filter *filter)
{
	if (!filter)
		return m_170.size() + slot69(0);
	int count = 0;
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if (filter->accepts(*it, self->getControllingPlayer()))
			++count;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && filter->accepts(obj, self->getControllingPlayer()))
			++count;
	}
	return count;
}
bool HordeContain::rva0046A2A7()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	const _STL::list<Object *> *items = p.m04;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && obj->test110(29))
			return true;
	}
	return false;
}
void HordeContain::rva0046E2BC()
{
	m_2E8 = true;
	m_2DC.clear();
}
void HordeContain::endMove()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (!ai->isMoving())
		return;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		(*it)->m_ai->rva00262D2D();
	ai->rva00262D2D();
}
struct Rva004698EEData
{
	bool m_differs; // +0x00
	short m_value; // +0x02
};
void rva004698EE(Object *obj, void *userData)
{
	if (!obj)
		return;
	const ThingTemplate *tmpl = obj->m_template;
	if (!tmpl || tmpl->isKindOf(68))
		return;
	Rva004698EEData *data = (Rva004698EEData *)userData;
	if (data->m_value == 0)
	{
		data->m_value = tmpl->m_5D8;
		return;
	}
	if (tmpl->m_5D8 != data->m_value)
		data->m_differs = true;
}
bool HordeContain::rva0046992C()
{
	if (!rva004698BC())
		return false;
	Rva004698EEData data;
	data.m_value = 0;
	data.m_differs = false;
	iterateContained(rva004698EE, &data, 1);
	return data.m_differs;
}
struct Rva00469689Data
{
	float m_best; // +0x00
	ObjectID m_id; // +0x04
};
void rva00469689(Object *obj, void *userData)
{
	if (!obj)
		return;
	const ThingTemplate *tmpl = obj->m_template;
	if (!tmpl || tmpl->isKindOf(68))
		return;
	Rva00469689Data *data = (Rva00469689Data *)userData;
	if (data->m_id != INVALID_ID && !(obj->m_264->m_10 > data->m_best))
		return;
	data->m_best = obj->m_264->m_10;
	data->m_id = (ObjectID)obj->getID();
}
Object *HordeContain::rva0046CBCA()
{
	Rva00469689Data data;
	data.m_best = -1.0f;
	data.m_id = INVALID_ID;
	iterateContained(rva00469689, &data, 1);
	return TheGameLogic->findObjectByID(data.m_id);
}
bool HordeContain::slot38(Object *obj, int a2, int a3)
{
	if (obj->m_template->isKindOf(13))
		return false;
	return TransportContain::slot38(obj, a2, a3);
}
void HordeContain::rva0046C327()
{
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	Player *local = ThePlayerList->getLocalPlayer();
	bool others = false;
	if (self && self->getControllingPlayer() == local)
	{
		Drawable *draw = ((Thing *)self)->getDrawable();
		if (TheWritableGlobalData->m_9A6)
		{
			if (draw)
				draw->rva00272BE7();
		}
		else
			others = true;
	}
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BE7();
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BE7();
		}
	}
}
float HordeContain::rva0046B850()
{
	float sum = 0.0f;
	float count = 0.0f;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			sum += obj->m_254->slot5();
			count += 1.0f;
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			sum += obj->m_254->slot5();
			count += 1.0f;
		}
	}
	if (count > 0.0f)
		sum /= count;
	return sum;
}
void HordeContain::rva0046D1F7(_STL::list<const Object *> &out)
{
	out.clear();
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
		out.push_back(*it);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		const Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			out.push_back(obj);
	}
}
void HordeContain::rva0046E253()
{
	m_object->rva0028B95F();
	_STL::list<const Object *> objects;
	rva0046D1F7(objects);
	for (_STL::list<const Object *>::iterator it = objects.begin(); it != objects.end(); ++it)
		const_cast<Object *>(*it)->rva0028B95F();
}
bool HordeContain::rva0046CDC9()
{
	_STL::list<const Object *> objects;
	rva0046D1F7(objects);
	unsigned int count = objects.size();
	if (count >= 1)
	{
		const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
		if (tmpl)
		{
			const ModuleInfo *info = &tmpl->m_moduleInfo;
			int n = info->getCount();
			for (int i = 0; i < n; ++i)
			{
				const ModuleData *data = info->getNthData(i);
				if (data)
				{
					const HordeContainModuleDataFields *horde = data->slot21();
					if (horde)
					{
						if (!horde->m_1D8 && count < horde->m_268)
							return false;
						return true;
					}
				}
			}
			return true;
		}
	}
	return false;
}
bool HordeContain::rva0046CCEF(const ThingTemplate *want)
{
	_STL::list<const Object *> objects;
	rva0046D1F7(objects);
	unsigned int count = objects.size();
	if (count < 1)
		return false;
	const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
	if (!tmpl || want != tmpl)
		return false;
	const ModuleInfo *info = &tmpl->m_moduleInfo;
	int n = info->getCount();
	for (int i = 0; i < n; ++i)
	{
		const ModuleData *data = info->getNthData(i);
		if (data)
		{
			const HordeContainModuleDataFields *horde = data->slot21();
			if (horde)
			{
				if (!horde->m_1D8 && count < horde->m_268)
					return false;
				return true;
			}
		}
	}
	return true;
}
void HordeContain::rva0046C20B()
{
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	Player *local = ThePlayerList->getLocalPlayer();
	bool others = false;
	if (self && self->getControllingPlayer() == local)
	{
		Drawable *draw = ((Thing *)self)->getDrawable();
		if (TheWritableGlobalData->m_9A6)
		{
			if (draw)
				draw->rva00272BAB(rva0046D3FC(0), slot101(self));
		}
		else
			others = true;
	}
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BAB(1, slot101(obj));
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BAB(1, slot101(obj));
		}
	}
}
ObjectID HordeContain::rva0046DEA1(ObjectID want)
{
	const _STL::list<Object *> *items = containedItems();
	ObjectID result = INVALID_ID;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Rva0046B850Module *module = (*it)->m_254;
		if (module)
		{
			ObjectID id = module->slot18();
			if (id != INVALID_ID)
			{
				Object *obj = TheGameLogic->findObjectByID(id);
				if (obj && obj->m_274)
				{
					ObjectID other = (ObjectID)obj->m_274->getID();
					if (other == want)
						id = other;
				}
				if (id == want || result == INVALID_ID)
					result = id;
			}
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
		Rva0046B850Module *module = member->m_254;
		if (module)
		{
			ObjectID id = module->slot18();
			Object *obj = TheGameLogic->findObjectByID(id);
			if (obj && obj->m_274)
			{
				ObjectID other = (ObjectID)obj->m_274->getID();
				if (other == want)
					id = other;
			}
			if (id != INVALID_ID && (id == want || result == INVALID_ID))
				result = id;
		}
	}
	return result;
}
void HordeContain::rva0046A78F(const Matrix3D *mtx)
{
	slot16();
	const _STL::list<Object *> *items = containedItems();
	Matrix3D transform = *mtx;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		float angle;
		Coord3D pos;
		pos = slot7(obj, &angle);
		transform.Row[0].W = pos.x;
		transform.Row[1].W = pos.y;
		transform.Row[2].W = pos.z;
		obj->setTransformMatrix(&transform);
	}
}
void HordeContain::rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3)
{
	_STL::list<const Object *> copy;
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
		copy.push_back(*it);
	AIGroup *group = TheAI->createGroup();
	for (_STL::list<const Object *>::iterator o = copy.begin(); o != copy.end(); ++o)
		slot42(*o);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			group->add(obj);
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && ai->rva0047306ESlot113())
				ai->m_command.aiIdle(cmdSource);
		}
	}
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	params.m_pos = pos;
	params.m_08 = a3;
	params.m_04 = false;
	group->rva00372571(&params, cmdSource);
	TheAI->destroyGroup(group);
}
void HordeContain::slot42(const Object *obj)
{
	m_170.insert(obj->getID());
	slot41(obj, 0);
}
void HordeContain::assignSpotToUnit(Object *obj)
{
	if (!m_198)
		((UpdateModule *)this)->slot33(1);
	for (_STL::list<int>::iterator it = m_194.begin(); it != m_194.end(); ++it)
	{
		int index = *it;
		char *entry = (char *)((Rva00469294 *)m_moduleData)->rva00469294(m_188Begin[index].m_key);
		if (entry && obj->m_template->isEquivalentTo(
			(const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)(entry + 4))))
		{
			m_17C[obj->getID()] = index;
			m_194.erase(it);
			m_170.insert(obj->getID());
			return;
		}
	}
}
void HordeContain::startMeleeAttack(Object *target)
{
	if (!target)
		return;
	if (target->getID() == m_2A0)
		return;
	m_2A0 = target->getID();
	m_121 = false;
	Object *aim = target;
	if (target->m_274)
		aim = target->m_274;
	Object *self = m_object;
	float angle = self->GetRelativeAngle(aim->getPosition());
	((Thing *)self)->setOrientation(angle + self->m_orientation);
	if (fabs(angle) > 0.5235f)
		slot16();
	m_2C8->slot3(target);
}
void HordeContain::rva00472329(const Coord3D *pos, int)
{
	if (((Rva004695DA *)(UpdateModule *)this)->rva004695DA())
		return;
	Rva0046247DPair p;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
	const _STL::map<int, int> *keys = &fields()->m_1B8;
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	while (it != p.m04->end())
	{
		const unsigned int id = (*it)->getID();
		if (m_17C.find(id) != m_17C.end())
		{
			AIUpdateInterface *ai = (*it)->m_ai;
			if (ai)
			{
				unsigned int key = m_188Begin[m_17C.find(id)->second].m_key;
				if (keys->find(key) != keys->end())
					ai->m_command.aiAttackPosition(pos, 0x7FFFFFFF, CMD_FROM_AI);
			}
		}
		++it;
	}
}
bool HordeContain::rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup)
{
	if (a2 != 0)
		return false;
	bool objHas = obj->testStatus((ObjectStatusTypes)0x3E);
	Object *self = m_object;
	bool selfHas = self->testStatus((ObjectStatusTypes)0x3E);
	if (objHas || selfHas)
	{
		if (!sameGroup || obj->m_304 != self->m_304 || objHas != selfHas)
			return false;
	}
	short key = obj->m_template->m_5D8;
	for (const AsciiString *name = names->begin(); name != names->end(); ++name)
	{
		const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(name);
		if (tmpl && tmpl->m_5D8 == key)
			return true;
	}
	return false;
}
void HordeContain::rva00468B24(float value)
{
	if (value > m_2EC)
		m_2EC = value;
	extern float g_00BC5CD4;
	if (m_2EC > g_00BC5CD4)
		m_2EC = g_00BC5CD4;
}
class Rva0046966C;
template <> class StringBase<unsigned short>
{
	friend class Rva0046966C;
	void validate() const;
};
class Rva0046966C
{
public:
	void rva0046966C();
};
void Rva0046966C::rva0046966C()
{
	((StringBase<unsigned short> *)this)->validate();
	HordeContainModuleDataFields *outer = *(HordeContainModuleDataFields **)((char *)this - 0x30);
	*(bool *)((char *)this + 0x291) = (outer->m_1D8 == 0);
}
void HordeContain::iterateContained(ContainIterateFunc func, void *userData, int a3)
{
	if (a3 & 0x10)
	{
		for (_STL::set<int>::iterator it = m_170.begin(); it != m_170.end(); )
		{
			Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
			++it;
			func(obj, userData);
		}
	}
	else
	{
		ContainModuleInterface::iterateContained(func, userData, a3);
	}
}
static inline bool clearSpecialUnitID(ObjectID &slot, ObjectID id)
{
	if (slot == id)
	{
		slot = INVALID_ID;
		return true;
	}
	return false;
}
void HordeContain::checkSpecialUnitDeath(Object *obj)
{
	ObjectID id = (ObjectID)obj->getID();
	if (clearSpecialUnitID(*(ObjectID *)&m_264, id))
		return;
	if (clearSpecialUnitID(m_26C, id))
	{
		HordeBannerCarrierUpdate *update = rva00468E26(obj);
		if (update)
			m_27C = update->m_data->m_value;
	}
}
int HordeContain::getBannerCarrierIndexToUse(const Object *obj, const ThingTemplate **outTemplate)
{
	const ThingTemplate *tmpl = obj->m_template;
	const _STL::vector<BannerIndexEntry *> &indexVec = m_bannerIndices;
	if (indexVec.empty())
		return -1;
	if (tmpl->isKindOf(13))
	{
		*outTemplate = indexVec[0]->m_template;
		return indexVec[0]->m_index;
	}
	for (unsigned int i = 0; i < indexVec.size(); ++i)
	{
		if (indexVec[i]->m_template == tmpl)
		{
			*outTemplate = indexVec[i]->m_template;
			return indexVec[i]->m_index;
		}
	}
	*outTemplate = indexVec[0]->m_template;
	return indexVec[0]->m_index;
}
void *HordeContain::rva0046AF12()
{
	if (m_194.empty())
		return 0;
	int n = GetGameLogicRandomValue(0, m_194.size() - 1, HORDECONTAIN_SOURCE_FILE, 1148);
	_STL::list<int>::iterator it = m_194.begin();
	for (; n > 0; --n)
		++it;
	char *entry = (char *)((Rva00469294 *)m_moduleData)->rva00469294(m_188Begin[*it].m_key);
	if (entry)
		return ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)(entry + 4));
	return 0;
}
void HordeContain::rva0046FE99(_STL::list<Object *> &out)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
		out.push_back(*it);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			out.push_back(obj);
	}
	_STL::list<const Object *> copy;
	for (_STL::list<Object *>::const_iterator c = p.m04->begin(); c != p.m04->end(); ++c)
		copy.push_back(*c);
	{
		void *unused = p.m00;
		p.m00 = unused;
		p.m00 = NULL;
	}
	_STL::list<const Object *>::iterator o;
	for (o = copy.begin(); o != copy.end(); ++o)
		slot42(*o);
}
void HordeContain::ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (!obj)
			continue;
		AIUpdateInterface *ai = obj->m_ai;
		if (!ai)
			continue;
		Rva003638BA *path = ai->m_140;
		if (path)
		{
			Rva003642DFResult point = path->rva00364521(ai->m_1F0);
			if (point.m_node && point.m_node->m_08)
			{
				int level = ((Rva001E3511 *)&point)->rva001E3511();
				if (level != 0x7fffffff && !TheTerrainLogic->slot35(level))
				{
					on.push_back((ObjectID)obj->getID());
					continue;
				}
				if (path->rva00363AD7())
				{
					before.push_back((ObjectID)obj->getID());
					continue;
				}
			}
		}
		after.push_back((ObjectID)obj->getID());
	}
}
// HordeContain::isFlankedBy, retail 0x00473D55 (446 bytes; slot 147 of the
bool HordeContain::isFlankedBy(Object *attacker)
{
	const HordeContainModuleDataFields *data = fields();
	if (data->m_25C >= 360.0f)
		return false;
	if (attacker->m_template->isKindOf(13))
	{
		Rva0028C197Slot149 *provider = (Rva0028C197Slot149 *)attacker->rva0028C197();
		if (provider && provider->slot149())
		{
			_STL::map<int, Rva00462D35Mapped> &flanks = m_2DC;
			_STL::map<int, Rva00462D35Mapped>::iterator it = flanks.find(attacker->getID());
			if (it != flanks.end())
				return TheGameLogic->m_frame < (*it).second.m_bits;
			float halfArc = (float)cos(data->m_25C * 0.008725f);
			const Coord3D *ourPos = m_object->getPosition();
			Coord3D dir;
			dir.x = attacker->m_position.x - ourPos->x;
			dir.y = attacker->m_position.y - ourPos->y;
			dir.z = 0.0f;
			dir.Normalize();
			const Coord3D *facing = ((const Thing *)m_object)->getUnitDirectionVector2D();
			bool flanked = halfArc > facing->y * dir.y + facing->z * dir.z + facing->x * dir.x;
			if (!flanked)
			{
				for (float *angle = m_2CCBegin; angle != m_2CCEnd; ++angle)
				{
					if (halfArc > Sin(*angle) * dir.y + Cos(*angle) * dir.x)
					{
						flanked = true;
						break;
					}
				}
			}
			if (flanked)
			{
				unsigned int frame = TheGameLogic->m_frame;
				flanks[attacker->getID()].m_bits = frame + data->m_264;
				m_2E8 = false;
				return true;
			}
			flanks[attacker->getID()].m_bits = 0;
		}
	}
	return false;
}
