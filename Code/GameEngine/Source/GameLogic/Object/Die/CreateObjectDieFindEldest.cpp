// cl: /O1 /DNDEBUG /MD
// findEldest::func, retail 0x004859A2 (72 bytes):
// ?func@findEldest@@SAHPAVObject@@PAX@Z (an int-returning iteration callback)
// Identity (target): WorldBuilder's debug CreateObjectDie.cpp:198..204
// findEldest::func ("findEldest:func - no module found for object match.",
// "... no EldestKindof module found ...") calls the object filter's accepts
// (0x00362437) and Object::findModule, then the module interface's slot
// 0xA0, as retail does.
// Body (target): an object-iteration callback that keeps, in its user data,
// the accepted object whose eldest-kindof record (first word) is lowest;
// it always continues the iteration. Layout (target): user data is
// (eldest object, lowest value, filter, module name key); the module's
// interface base sits at +0x0C.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object;
class Player;

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

struct EldestKindofRecord
{
	unsigned int m_value; // +0x00
};

class ModuleInterfaceAt0C
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual EldestKindofRecord *getEldestKindofRecord(); // slot 0xA0
};

class Module
{
public:
	ModuleInterfaceAt0C *getInterface() { return &m_interface; }

private:
	unsigned char m_pad00[0x0C];
	ModuleInterfaceAt0C m_interface; // +0x0C
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend struct findEldest;
};

struct findEldestData
{
	Object *m_eldest; // +0x00
	unsigned int m_lowest; // +0x04
	Rva2225E0Filter *m_filter; // +0x08
	NameKeyType m_moduleKey; // +0x0C
};

struct findEldest
{
	static int func(Object *obj, void *userData);
};

int findEldest::func(Object *obj, void *userData)
{
	findEldestData *data = (findEldestData *)userData;
	if (data->m_filter->accepts(obj, 0))
	{
		Module *module = obj->findModule(data->m_moduleKey);
		if (module)
		{
			EldestKindofRecord *record = module->getInterface()->getEldestKindofRecord();
			if (record && record->m_value < data->m_lowest)
			{
				data->m_lowest = record->m_value;
				data->m_eldest = obj;
			}
		}
	}
	return 1;
}
