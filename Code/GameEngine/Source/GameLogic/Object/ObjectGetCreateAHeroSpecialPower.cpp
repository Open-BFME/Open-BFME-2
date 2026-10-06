// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Object::GetCreateAHeroSpecialPower, retail 0x002912DC (48B), and the module
// lookup it calls, retail 0x0028F2C4 (34B).
//
// Target facts: 0x0028F2C4 walks the null-terminated behavior pointer list at
// Object +0x244 (the list Object::findModule 0x0028B6D6 walks) and returns the
// first module whose module data (+4) holds the int argument at +4, else NULL.
// GetCreateAHeroSpecialPower bounds-checks its index against the pointer-sized
// vector at Object +0x4A4 (its size is also read by 0x0028F2E6), looks the
// entry up through 0x0028F2C4 and returns what rowed 0x004B554F reports for the
// found module (module data +0x118 behind +4), or NULL when out of range.
//
// Donor/lead facts: the name GetCreateAHeroSpecialPower and the "Index out of
// range" assertion (line 12750, compiled out of retail) come from the
// WorldBuilder lead for Object.cpp. Structural inference: the +4 data field is
// a module tag key compared like ZH's ModuleData::getModuleTagNameKey; the
// lookup keeps its address-derived name because no target evidence names it.

#include <vector>

class SpecialPowerTemplate;

class Rva004B554FHolder
{
public:
	int rva004B554F() const;
};

class ModuleData
{
public:
	int getTagKey() const { return m_tagKey; }

private:
	void *m_vtbl;
	int m_tagKey; // +0x04
};

class BehaviorModule
{
public:
	const ModuleData *getModuleData() const { return m_data; }

private:
	void *m_vtbl;
	ModuleData *m_data; // +0x04
};

class Object
{
public:
	const SpecialPowerTemplate *GetCreateAHeroSpecialPower(unsigned int index);
	BehaviorModule *rva0028F2C4(int key) const;

private:
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x4A4 - 0x248];
	_STL::vector<int> m_createAHeroPowers; // +0x4A4
};

BehaviorModule *Object::rva0028F2C4(int key) const
{
	BehaviorModule **b = m_behaviors;
	for (; *b != 0; b++)
	{
		BehaviorModule *m = *b;
		if (key == m->getModuleData()->getTagKey())
			return m;
	}
	return 0;
}

const SpecialPowerTemplate *Object::GetCreateAHeroSpecialPower(unsigned int index)
{
	const SpecialPowerTemplate *result = 0;
	if (index < m_createAHeroPowers.size())
	{
		int entry = m_createAHeroPowers[index];
		result = (const SpecialPowerTemplate *)((const Rva004B554FHolder *)rva0028F2C4(entry))->rva004B554F();
	}
	return result;
}
