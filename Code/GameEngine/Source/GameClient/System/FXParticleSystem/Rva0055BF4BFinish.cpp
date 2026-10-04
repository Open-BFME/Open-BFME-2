// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE /Ireference/shims/moduledata
// ??0Rva0055BF4B@@QAE@ABVRvaSmartPtr12@@PBURva0055BF4BSrc@@@Z @0x0055BF4B 181B
// Derived module ctor: second base FXParticleSystem::DefaultColorModuleInfo at
// +0x1c, its eight RGBColorKeyframe elements copied from src+0xc, then the
// trailing random variable set from src+0x90/0x94 scaled by g_00BBB8F0.
// Evidence: thiscall 2 args ret 8; calls rowed ??0Rva0055BF21@@QAE@ABVRvaSmartPtr12@@H@Z 0x0055BF21
// and ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@XZ 0x0055BC39 and
// ?setRange@GameClientRandomVariable@@QAEXMMW4DistributionType@1@@Z 0x002341E7;
// caller 0x003ABCC0; neighbours 0x0055BF21 0x0055C000 same FXParticleSystem.

#include "Common/Snapshot.h"

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12();
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

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

class DefaultModuleHeadBase
{
public:
	DefaultModuleHeadBase(const RvaSmartPtr12 &smart, int i);
	virtual ~DefaultModuleHeadBase();

	RvaSmartPtr12 m_smart;
	int m_int10;
};

class Rva003AEEB3 : public DefaultModuleHeadBase, public DefaultModuleSecondBase,
	public DefaultModuleThirdBase
{
public:
	Rva003AEEB3(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva003AEEB3();
};

class Rva0055BF21 : public Rva003AEEB3
{
public:
	Rva0055BF21(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055BF21();
};

class GameClientRandomVariable
{
public:
	enum DistributionType { CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS };
	GameClientRandomVariable();
	void setRange(float low, float high, DistributionType type = UNIFORM);
private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

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

extern const float g_00BBB8F0;

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
	m_trailing.setRange(src->m_f90 * g_00BBB8F0, src->m_f94 * g_00BBB8F0);
}
