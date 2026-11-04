// cl: /DNDEBUG /MD /EHsc /Ob2

// Open-BFME5: DefaultColorModuleInfo default constructor @0x55BC39.
// Retail: own vtable, eight RGBColorKeyframe elements at +4 built by the
// rowed vector_constructor_iterator helper through the rowed element
// default at 0x00001E67, then an inline-zeroed trailing random variable.
// The element's declared (never defined) destructor carries the EH frame.

class Rva0049B47C
{
public:
	Rva0049B47C() {}
	virtual ~Rva0049B47C();
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

#include "../../../../Include/GameClient/GameClientRandomVariable.h"
#include "../../../../Include/GameClient/GameClientRandomVariableInlines.h"

class DefaultColorModuleInfo : public ::Rva0049B47C
{
public:
	DefaultColorModuleInfo();
	virtual ~DefaultColorModuleInfo();
	virtual void LoadPostProcess(); // slot 1: the exported empty callback FXParticleSystem.cpp rows at 0x000B3FD0
	virtual const char *GetSnapshotName();

private:
	RGBColorKeyframe m_keys[8];
	GameClientRandomVariable m_trailing;
};

// ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@XZ
DefaultColorModuleInfo::DefaultColorModuleInfo()
{
}

}
