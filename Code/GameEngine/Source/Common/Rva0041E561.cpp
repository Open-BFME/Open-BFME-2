// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0041E561@Rva0041E4A3@@UAEXXZ @0x0041E561 329B: vslot 1 of vtable 0x0083AEA8.
// Evidence: this+0xC vector push_back x6 of new ModuleData ctors 0x57379B 0x5734D7
// 0x5730FF 0x572EC4 0x572DD4 0x572C5A via rowed push_back 0x004DFCB0 and rowed
// operator new 0x0002FDA0; EH states 0-5 with -1 before each push_back.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData
{
public:
	virtual ~ModuleData();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase() throw();
	virtual ~GameEngineDeletingBase();
private:
	char m_pad[8];
};

class Rva0041E4A3 : public GameEngineDeletingBase
{
public:
	virtual void rva0041E561();
private:
	_STL::vector<const ModuleData *> m_vec;
};

class AITargetHeuristicBaseDefense : public ModuleData
{
public:
	AITargetHeuristicBaseDefense();
private:
	int m_pad;
};

class Rva005734EB : public ModuleData
{
public:
	Rva005734EB();
private:
	int m_pad;
};

class Rva00573117 : public ModuleData
{
public:
	Rva00573117();
private:
	int m_pad[2];
};

class Rva00572ED8 : public ModuleData
{
public:
	Rva00572ED8();
private:
	int m_pad;
};

class Rva00572DE8 : public ModuleData
{
public:
	Rva00572DE8();
private:
	int m_pad;
};

class Rva00572C6E : public ModuleData
{
public:
	Rva00572C6E();
private:
	int m_pad;
};

void Rva0041E4A3::rva0041E561()
{
	m_vec.push_back(new AITargetHeuristicBaseDefense);
	m_vec.push_back(new Rva005734EB);
	m_vec.push_back(new Rva00573117);
	m_vec.push_back(new Rva00572ED8);
	m_vec.push_back(new Rva00572DE8);
	m_vec.push_back(new Rva00572C6E);
}
