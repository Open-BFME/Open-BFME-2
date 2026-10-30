// cl: /DNDEBUG /MD
enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};

//
// ?getEnterPosition@HordeAIUpdate@@UAEXHPAUCoord3D@@@Z @0x0049A8FA 65B.
// Target evidence: the only reference to this body is slot 5 of the vtable
// 0x00C50868 that the matched HordeAIUpdate dtor 0x0049A64B installs at
// +0x3E4, the trailing interface base of this AIUpdate-family class (vptrs
// at +0, +0xC, +0x10, +0x20, +0x24 as the dtor stores them); the slot's name
// is not established, hence the address name. cl 7.1 compiles an override of
// a non-primary base's virtual with the base subobject's this and folds the
// adjustment into the member accesses: the Object pointer at +8 is read as
// [ecx-0x3DC]. Body: asks the object's +0x250 module (the contain slot the
// matched evaluateIsBuildingEmpty reads) for a provider through vslot +0x7C
// and, when it and the out pointer exist, copies the Coord3D that provider
// returns by value from vslot +0x1C (first argument forwarded, an int out
// parameter whose meaning is not asserted). Structural inference: the int is
// declared at function scope, which gives it its own frame slot as retail
// (declared in the if block it reuses the dead out-pointer argument slot).
#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"

class Thing;
class ModuleData;
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
class Rva0049A8FAProvider
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual bool rva18(int a) = 0; // +0x18
	virtual Coord3D rva1C(int a, int *extra) = 0; // +0x1C
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void rva2C(int a) = 0; // +0x2C
};
class Rva0049A8FAContain
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual Rva0049A8FAProvider *rva7C() = 0; // +0x7C
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_5A = 0x5A
};

class ContainModuleInterface;
class AIUpdateInterface;
class Rva0049A8FAContain;

class Object
{
public:
	void *rva0028C197() const;
	ContainModuleInterface *getContain() const { return reinterpret_cast<ContainModuleInterface *>(m_250); }
	AIUpdateInterface *getAI() const { return m_ai; }
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	int rva0028AF76() const;
	char m_pad00[0x250];
	Rva0049A8FAContain *m_250; // +0x250
	char m_pad254[0x4];
private:
	AIUpdateInterface *m_ai; // +0x258
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

struct B24
{
	virtual void f24();
	unsigned char m_pad[0x3E4 - 0x28];
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public B24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();
	virtual void a011();
	virtual void a012();
	virtual void a013();
	virtual void a014();
	virtual void a015();
	virtual void a016();
	virtual void a017();
	virtual void a018();
	virtual void a019();
	virtual void a020();
	virtual void a021();
protected:
	virtual void bfmePrivateCommand42(Object *, CommandSourceType);
public:
	virtual void a023();
	virtual void a024();
	virtual void a025();
	virtual void a026();
	virtual void a027();
	virtual void a028();
	virtual void a029();
	virtual void a030();
	virtual void a031();
	virtual void a032();
	virtual void a033();
	virtual void a034();
	virtual void a035();
	virtual void a036();
	virtual void a037();
	virtual void a038();
	virtual void a039();
	virtual void a040();
	virtual void a041();
	virtual void a042();
	virtual void a043();
	virtual void a044();
	virtual void a045();
	virtual void a046();
	virtual void a047();
	virtual void a048();
	virtual void a049();
	virtual void a050();
	virtual void a051();
	virtual void a052();
	virtual void a053();
	virtual void a054();
	virtual void a055();
	virtual void a056();
	virtual void a057();
	virtual void a058();
	virtual void a059();
	virtual void a060();
	virtual void a061();
	virtual void a062();
	virtual void a063();
	virtual void a064();
	virtual void a065();
	virtual void a066();
	virtual void a067();
	virtual void a068();
	virtual void a069();
	virtual void a070();
	virtual void a071();
	virtual void a072();
	virtual void a073();
	virtual void a074();
	virtual void a075();
	virtual void a076();
	virtual void a077();
	virtual void a078();
	virtual void a079();
	virtual void a080();
	virtual void a081();
	virtual void a082();
	virtual void a083();
	virtual void a084();
	virtual void a085();
	virtual void a086();
	virtual void a087();
	virtual void a088();
	virtual void a089();
	virtual void a090();
	virtual void a091();
	virtual void a092();
	virtual void a093();
	virtual void a094();
	virtual void a095();
	virtual void a096();
	virtual void a097();
	virtual void a098();
	virtual void a099();
	virtual void a100();
	virtual void a101();
	virtual void a102();
	virtual void a103();
	virtual void a104();
	virtual void a105();
	virtual void a106();
	virtual void a107();
	virtual void a108();
	virtual bool isIdle() const; // primary slot 110
	bool isMoving() const;
protected:
	virtual ~AIUpdateInterface();
	Object *getObject() const { return m_object; } // native module owner at +8
};

class Iface3E4
{
public:
	virtual bool isClearToApproach(int a) = 0;
	virtual bool reserveApproachPosition(int a, Coord3D *pos, int *out) = 0;
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void getEnterPosition(int a, Coord3D *out) = 0;
};
class HordeAIUpdate : public AIUpdateInterface, public Iface3E4
{
public:
	HordeAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeAIUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual bool isClearToApproach(int docker);
	virtual bool reserveApproachPosition(int a, Coord3D *pos, int *out);
	virtual void getEnterPosition(int docker, Coord3D *out);
protected:
	virtual void bfmePrivateCommand42(Object *, CommandSourceType);
};

void HordeAIUpdate::getEnterPosition(int docker, Coord3D *out)
{
	int extra;
	Rva0049A8FAProvider *provider = m_object->m_250->rva7C();
	if (provider && out)
	{
		*out = provider->rva1C(docker, &extra);
	}
}

// ?reserveApproachPosition@HordeAIUpdate@@UAE_NHPAUCoord3D@@PAH@Z @0x0049A8A1 89B: slot 1
// of the same +0x3E4 table (0x00C50868). No provider from the object's +0x250
// module (vslot +0x7C): false. Otherwise the provider is asked about the first
// argument (vslot +0x18) and, if it says no, given it (vslot +0x2C); then
// slot 5 above fills the position, the out word is cleared and the answer is
// true. Names stay address-derived.
bool HordeAIUpdate::reserveApproachPosition(int a, Coord3D *pos, int *out)
{
	Rva0049A8FAProvider *provider = m_object->m_250->rva7C();
	if (!provider)
		return false;
	if (!provider->rva18(a))
		provider->rva2C(a);
	getEnterPosition(a, pos);
	if (out)
		*out = 0;
	return true;
}

// Retail table C50868 slot 0 uses the same +3E4 interface receiver as
// slots 1 and 5. Its whole 33B span ends at the following slot-1 body.
// The Object member at +8 is therefore [secondary-this - 3DC].
bool HordeAIUpdate::isClearToApproach(int docker)
{
 Rva0049A8FAProvider *provider = m_object->m_250->rva7C();
 if (!provider) return false;
 return provider->rva18(docker);
}

// The two rowed Horde constructors install this entire 20-entry secondary
// interface table at +3E4. Each DIR32 target below is its existing retail
// code owner; folded constant/no-op bodies retain that owner's name without
// inferring an interface-method identity from the fold. Native C50868..C508B8.
extern "C" {
void __identifier("?isClearToApproach@HordeAIUpdate@@UAE_NH@Z")();
void __identifier("?reserveApproachPosition@HordeAIUpdate@@UAE_NHPAUCoord3D@@PAH@Z")();
void __identifier("?rva0049A6D7@Rva0049A6D7@@QAE_NHHH@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?getEnterPosition@HordeAIUpdate@@UAEXHPAUCoord3D@@@Z")();
void __identifier("??_9@$BBE@AE")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?rva0049A973@HordeAIUpdate@@UAE_NPAVObject@@H@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00C50868[20] = {
 (const void *)&__identifier("?isClearToApproach@HordeAIUpdate@@UAE_NH@Z"),
 (const void *)&__identifier("?reserveApproachPosition@HordeAIUpdate@@UAE_NHPAUCoord3D@@PAH@Z"),
 (const void *)&__identifier("?rva0049A6D7@Rva0049A6D7@@QAE_NHHH@Z"),
 (const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"),
 (const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"),
 (const void *)&__identifier("?getEnterPosition@HordeAIUpdate@@UAEXHPAUCoord3D@@@Z"),
 (const void *)&__identifier("??_9@$BBE@AE"),
 (const void *)&__identifier("??_9@$BBE@AE"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?rva0049A973@HordeAIUpdate@@UAE_NPAVObject@@H@Z"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"),
 (const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
 (const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"),
 (const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
};
