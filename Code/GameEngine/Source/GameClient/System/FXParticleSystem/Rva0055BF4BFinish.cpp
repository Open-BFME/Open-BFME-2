// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/shims/moduledata
// ??0Rva0055BF4B@@QAE@ABVRvaSmartPtr12@@PBURva0055BF4BSrc@@@Z @0x0055BF4B 181B
// Derived module ctor: second base FXParticleSystem::DefaultColorModuleInfo at
// +0x1c, its eight RGBColorKeyframe elements copied from src+0xc, then the
// trailing random variable set from src+0x90/0x94 scaled by 1/255 (0.003921569f).
// Evidence: thiscall 2 args ret 8; calls rowed ??0Rva0055BF21@@QAE@ABVRvaSmartPtr12@@H@Z 0x0055BF21
// and ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@XZ 0x0055BC39 and
// ?setRange@GameClientRandomVariable@@QAEXMMW4DistributionType@1@@Z 0x002341E7;
// caller 0x003ABCC0; neighbours 0x0055BF21 0x0055C000 same FXParticleSystem.

#include "Common/Snapshot.h"

#include "../../../../Include/Common/RvaSmartPtr12.h"

class DefaultModuleSecondBase
{
public:
	virtual ~DefaultModuleSecondBase();
};

class DefaultModuleThirdBase
{
public:
	virtual ~DefaultModuleThirdBase();
};

#include "../../../../Include/GameClient/DefaultModuleHeadBase.h"

#include "../../../../Include/GameClient/Rva003AEEB3.h"

#include "../../../../Include/Common/Rva0055BF21.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

namespace FXParticleSystem
{
class RGBColorKeyframe
{
public:
	RGBColorKeyframe();
private:
	char m_data[0x10];
};
class DefaultColorModuleInfo : public Snapshot
{
public:
	DefaultColorModuleInfo();
	virtual ~DefaultColorModuleInfo();
public:
	RGBColorKeyframe m_keys[8];
	GameClientRandomVariable m_trailing;
};
}

struct Rva0055BF4BSrcElem
{
	char m_data[0x10];
};

struct Rva0055BF4BSrc
{
	char m_pad[0x0C];
	Rva0055BF4BSrcElem m_elems[8];
	char m_pad2[0x04];
	float m_f90;
	float m_f94;
};


class Rva0055BF4B : public Rva0055BF21, public FXParticleSystem::DefaultColorModuleInfo
{
public:
	Rva0055BF4B(const RvaSmartPtr12 &smart, const Rva0055BF4BSrc *src);
	virtual ~Rva0055BF4B();
};

Rva0055BF4B::Rva0055BF4B(const RvaSmartPtr12 &smart, const Rva0055BF4BSrc *src)
	: Rva0055BF21(smart, (int)src), FXParticleSystem::DefaultColorModuleInfo()
{
	for (int i = 0; i < 8; ++i)
		m_keys[i] = (const FXParticleSystem::RGBColorKeyframe &)src->m_elems[i];
	m_trailing.setRange(src->m_f90 * 0.003921569f, src->m_f94 * 0.003921569f);
}
