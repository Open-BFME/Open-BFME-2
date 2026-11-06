// cl: /MD
// ??0Rva003AE683@@QAE@ABV0@@Z @0x003AE683 38B
// Derived copy ctor calling rowed base 0x003AE6A9 then installing own 3 vptrs
// at +0/+0x14/+0x18 DIR32 and returning this. No EH (base handles its own).
// Evidence: chain lane after landing 0x003AE6A9; caller 0x003AE64C installs
// next vptrs; unblocks 0x003AE64C.
class RvaSmartPtr12_3AE683
{
public:
	RvaSmartPtr12_3AE683(const RvaSmartPtr12_3AE683 &that);
	~RvaSmartPtr12_3AE683();
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class ModuleInfoSecondBase_3AE683
{
public:
	virtual ~ModuleInfoSecondBase_3AE683();
};
class ModuleInfoHeadBase_3AE683
{
public:
	ModuleInfoHeadBase_3AE683(const ModuleInfoHeadBase_3AE683 &other)
		: m_smart(other.m_smart)
		, m_int10(other.m_int10)
	{
	}
	virtual ~ModuleInfoHeadBase_3AE683();
	RvaSmartPtr12_3AE683 m_smart;
	int m_int10;
};
class Rva003AF50D : public ModuleInfoHeadBase_3AE683, public ModuleInfoSecondBase_3AE683
{
public:
	Rva003AF50D(const Rva003AF50D &other);
	virtual ~Rva003AF50D();
};
class Intermediate3AE683 : public Rva003AF50D
{
public:
	__forceinline Intermediate3AE683(const Intermediate3AE683 &other)
		: Rva003AF50D(other)
	{
	}
	virtual ~Intermediate3AE683();
};
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectDrawModuleInfo.h"
namespace FXParticleSystem {
}
class Rva003AE6A9 : public Intermediate3AE683, public FXParticleSystem::RenderObjectDrawModuleInfo
{
public:
	Rva003AE6A9(const Rva003AE6A9 &other);
	virtual ~Rva003AE6A9();
private:
	int m_58;
};
// Slot 0 of this class's table 0x0081CD14 is ??_GRva003ACED6 (0x003ACEBA),
// which calls the rowed ~Rva003ACED6 (0x003ACED6, a jmp to ~Rva003AB9FF).
// Modelled as a novtable Rva003ACED6 view over Rva003AE6A9 so the implicit
// ~Rva003AE683 calls it (real base or ICF-folded dtor name: not settled).
class __declspec(novtable) Rva003ACED6 : public Rva003AE6A9
{
public:
	__forceinline Rva003ACED6(const Rva003ACED6 &other)
		: Rva003AE6A9(other)
	{
	}
	virtual ~Rva003ACED6();
};
class Rva003AE683 : public Rva003ACED6
{
public:
	Rva003AE683(const Rva003AE683 &other);
};
Rva003AE683::Rva003AE683(const Rva003AE683 &other)
	: Rva003ACED6(other)
{
}
