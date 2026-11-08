// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// SpecialAbilityUpdate base slot 8 of the +0x20 interface table (retail
// 0x0044EDA6, 97 bytes; the teleport, give-upgrade, weapon-fire and
// toggle-deploy subclasses call it from their own slot-8 overrides, rowed
// elsewhere). With a module data and a passing 0x0044E7A8 kind check, the
// final override of the module data's +0x38 entry decides: values other than
// 0x28/0x27 accept; those two additionally compare two object-interface
// counts (+0x250 interface slots 69 and 28). The redundant m_moduleData
// self-compare around the body (tautology carrier, zero bytes) keeps the
// native block layout of the early null returns.
typedef bool Bool;
class Object;
class Rva0044EDA6ModuleData;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerUpdateInterface.h"
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/SpecialPower.h"

class Rva0044E7A8
{
public:
	bool rva0044E7A8(int arg);
};

class Rva0044EDA6Virt
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual unsigned int s28();
	virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
	virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
	virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
	virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
	virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
	virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual unsigned int s69(int v);
};

struct Rva0044EDA6Outer
{
	char m_pad00[0x38];
	const SpecialPowerTemplate *m_specialPowerTemplate; // +0x38
};


extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Bool SpecialAbilityUpdate::vslot08(int targetPos)
{
if ((m_moduleData != 0 || m_moduleData == 0)) {
 const Rva0044EDA6Outer *data=(const Rva0044EDA6Outer *)m_moduleData;
 if (!data || !((Rva0044E7A8 *)this)->rva0044E7A8(targetPos)) return false;
 int value=data->m_specialPowerTemplate->getFO()->m_type;
 if(value!=0x28 && value!=0x27) {_ReadWriteBarrier(); return true;}
 Rva0044EDA6Virt *virt=*(Rva0044EDA6Virt **)((char *)m_object+0x250);
 if(!virt)return false;
 unsigned containCount=virt->s69(0);unsigned m_containMax=virt->s28();
 if(containCount>=m_containMax)return false;
 _ReadWriteBarrier(); return true;
}
}

// The +0x20 interface's slots 6 and 7 are bodies retail folded across SpecialAbilityUpdate's
// subclasses (rows 0x0044EECA and 0x0044F09F own them).
struct Rva0044F09FData
{
	char m_pad00[0x38];
	int m_38; // +0x38
};
Bool SpecialAbilityUpdate::vslot07(int value)
{
	return value == ((const Rva0044F09FData *)m_moduleData)->m_38;
}

struct Rva0044EECAParam
{
	unsigned char m_pad00[0x1D];
	unsigned char m_flags1D;
	unsigned char m_pad1E[0x44 - 0x1E];
	const SpecialPowerTemplate *m_over44;
};
Bool SpecialAbilityUpdate::isPowerCurrentlyInUse(const CommandButton *command) const
{
	const Rva0044EECAParam *p = (const Rva0044EECAParam *)command;
	if (p != 0) {
		const SpecialPowerTemplate *overridable = p->m_over44;
		if (overridable != 0) {
			const SpecialPowerTemplate *f = overridable->getFO();
			if (f->m_type == 0x16 && (p->m_flags1D & 2) == 0)
				return m_68 == 0;
		}
	}
	int v = m_packingState;
	if (v != 0) {
		if (v == 1 || v == 3) {
			if (p != 0) {
				const SpecialPowerTemplate *f2 = p->m_over44->getFO();
				if (f2->m_reloadTime == 0)
					return false;
			}
		}
		if (m_withinStartAbilityRange != 0)
			return true;
	}
	return false;
}
