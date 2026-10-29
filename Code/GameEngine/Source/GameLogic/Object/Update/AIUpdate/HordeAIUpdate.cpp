// cl: /DNDEBUG /MD
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
class Object
{
public:
	unsigned char m_pad000[0x250];
	Rva0049A8FAContain *m_250;
};
struct B00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
struct B20 { virtual void f20(); };
struct B24 { virtual void f24(); unsigned char m_pad[0x3E4 - 0x28]; };
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
class HordeAIUpdate : public B00, public B0C, public B10, public B20, public B24, public Iface3E4
{
public:
	virtual bool isClearToApproach(int docker);
	virtual bool reserveApproachPosition(int a, Coord3D *pos, int *out);
	virtual void getEnterPosition(int docker, Coord3D *out);
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
