// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE
//
// doSpecialPowerAtLocation overrides of four BFME2 area powers: slot 12 of
// each class's +0x10 special-power interface vftable (the slot
// InvisibilitySpecialPower's rowed doSpecialPowerAtLocation fills), so `this`
// is that subobject (module data at -0x0C, Object at -0x08). All four follow
// the Zero Hour override shape: nothing while the Object is disabled
// (Object +0x1C8, the rowed BitFlags<11>::any) or without a location, then
// SpecialPowerModule::doSpecialPowerAtLocation 0x004949D8, then the class's
// own placement helper on the primary this (pinned by address on their
// bodies, each taking the location).
//
// DarknessSpecialPower 0x004C4F1C (71 bytes, vftable 0x00C5D7F0): helper
// 0x004C4E93, then clears +0x98 of the g_00DFEC68 manager.
// TaintSpecialPower 0x004C4B3C (74 bytes, vftable 0x00C5D568): also nothing
// while the module data's +0x7C name is empty; helper 0x004C49AE.
// FreezingRainSpecialPower 0x004C4D22 (79 bytes, vftable 0x00C5D700):
// helper 0x004C4C99, then hands the module data's +0x84 value to the
// g_00DFEC68 manager (0x00287519).
// CloudBreakSpecialPower 0x004C482B (80 bytes, vftable 0x00C5D3C8): helpers
// 0x004C4621 (with the location) and 0x004C4582, then clears +0x98 of the
// g_00DFEC68 manager.
struct Coord3D
{
	float x;
	float y;
	float z;
};

template <int N> class BitFlags
{
public:
	bool any() const;	// 0x0023C58B for N = 11
private:
	unsigned int m_bits[1];
};

#include "string_base.h"

class Object;

// Object's disabled mask is at +0x1C8. Retail forms its address (and the
// Taint module data's +0x7C name) by adding the offset to the pointer loaded
// straight into ecx (mov ecx, [esi-8] / add ecx, 0x1C8); cl 7.1 emits that for
// byte-pointer arithmetic written in the body, while a typed member access
// or an inline accessor gives lea from another register instead.

class Rva00285D34
{
public:
	void rva00287519(int value);	// 0x00287519
	void clear98() { m_98 = 0; }
private:
	unsigned char m_pad00[0x98];
	int m_98;			// +0x98
};
extern Rva00285D34 *g_00DFEC68;

class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s0A() = 0;
	virtual void s0B() = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

class DarknessSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4E93(const Coord3D *loc);
};

class TaintSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C49AE(const Coord3D *loc);
};

struct FreezingRainSpecialPowerModuleData
{
	unsigned char m_pad00[0x84];
	int m_84;			// +0x84
};

class FreezingRainSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4C99(const Coord3D *loc);
	const FreezingRainSpecialPowerModuleData *getData() const
	{
		return (const FreezingRainSpecialPowerModuleData *)m_moduleData;
	}
};

class CloudBreakSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4621(const Coord3D *loc);
	void rva004C4582();
};

void DarknessSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C4E93(loc);
	g_00DFEC68->clear98();
}

void TaintSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	const void *data = m_moduleData;
	const StringBase<char> *name = (const StringBase<char> *)((const char *)data + 0x7C);
	if (name->isEmpty())
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C49AE(loc);
}

void FreezingRainSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C4C99(loc);
	g_00DFEC68->rva00287519(getData()->m_84);
}

void CloudBreakSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C4621(loc);
	rva004C4582();
	g_00DFEC68->clear98();
}
