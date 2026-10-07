// cl: /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva002B6E8ACalc@@YGXPAVRva003F287F@@HPAH1@Z @ 0x002B6E8A, 167 bytes.
// The five-argument stack cleanup proves stdcall. Target calls the rowed int getter on each ModuleData record and uses its 32-bit result as a virtual receiver; the zero-offset Rva004E0632 base view is a structural inference from those bytes.

#include <vector>

class Rva004E0632
{
public:
	int rva004E0632() const;
};

class ModuleData : public Rva004E0632
{
};

class Rva002B6E8AView
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
};

class Rva003F287F
{
public:
	void rva003F28DB(_STL::vector<const ModuleData *> &out);
	char m_pad00[0x13C];
	int m_selector;
};

void __stdcall Rva002B6E8ACalc(Rva003F287F *owner, int selector, int *firstTotal, int *secondTotal)
{
	*firstTotal = 0;
	*secondTotal = 0;
	if (owner->m_selector != selector)
		return;

	_STL::vector<const ModuleData *> modules;
	owner->rva003F28DB(modules);
	for (unsigned i = 0; i < modules.size(); ++i) {
		const ModuleData *module = modules[i];
		int value = module->rva004E0632();
		Rva002B6E8AView *view = reinterpret_cast<Rva002B6E8AView *>(value);
		*firstTotal += view->slot08();
		*secondTotal += view->slot00();
	}
}
