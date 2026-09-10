// cl: /O1 /MD
//
// DieModuleData::DieModuleData, retail 0x006054E7, 29 bytes. Dedicated TU so
// EjectPilotDie.cpp keeps its matched bodies. Base ctor then three zeroed
// pointers at +0x14 and the DieModuleData vtable.

class ModuleData
{
public:
	ModuleData();
	virtual ~ModuleData();

private:
	int _pad[4];
};

class DieModuleData : public ModuleData
{
public:
	DieModuleData();

private:
	void *_a;
	void *_b;
	void *_c;
};

DieModuleData::DieModuleData()
	: _a(0), _b(0), _c(0)
{
}
