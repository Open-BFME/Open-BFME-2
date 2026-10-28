// cl: /DNDEBUG /MD
//
// ?isValidContainerFor@HordeTransportContain@@UAE_NPAVObject@@_N1@Z, retail
// 0x004771EB, 147 bytes. Slot 38 of HordeTransportContain's +0x20 interface
// vftable 0x00C45D30 (the slot beside the matched rva0050B238 slot 27 in
// HordeTransportContainIface20.cpp), so this is the +0x20 subobject. The
// OpenContain base admission (0x00462977) runs first; a rider without a
// horde member (+0x250) that carries status 0x26 is admitted when the +0x11D
// helper can start a member for it (0x00588BF3). Otherwise a capacity check
// adds interface slots 0x114(0) and 0xCC to the rider's rowed 0x0028FBBE
// count and refuses above the module data's +0x98 limit. Only the layout
// this body touches is modelled.

class Rva00588E44Contain;

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	int getTransportSlotCount();
	unsigned char m_unmodelled000[0x250];
	void *m_hordeMember;	// +0x250
};

struct Coord3D;
class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *);
	void rva00588BA8(Object *obj, bool flag);
	Object *rva00588C4E(void *contain, const struct Coord3D *obj);
	void rva00588F61(void *contain, Object *owner, enum CommandSourceType obj);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	Rva00588E44Contain *rva00588BF3(void *contain, Object *obj);
	bool rva00588D24(void *owner, Object *obj);
	void rva00588E44(void *argument);
};

struct HordeTransportContainModuleData
{
	unsigned char m_unmodelled00[0x98];
	unsigned int m_maxSlots;	// +0x98
};

#define SLOTS08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class OpenContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
};

struct HordeTransportContainPrimary
{
	virtual void p00();
	const HordeTransportContainModuleData *m_moduleData;	// +0x04
	unsigned char m_unmodelled08[0x20 - 0x08];
};

struct HordeTransportContainIface20
{
	SLOTS08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOTS08(s08,s09,s10,s11,s12,s13,s14,s15)
	SLOTS08(s16,s17,s18,s19,s20,s21,s22,s23)
	SLOTS08(s24,s25,s26,s27,s28,s29,s30,s31)
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);	// slot 38
	virtual void s39();
	SLOTS08(s40,s41,s42,s43,s44,s45,s46,s47)
	virtual void s48(); virtual void s49(); virtual void s50();
	virtual int getContainCount();	// slot 51 (+0xCC)
	SLOTS08(s52,s53,s54,s55,s56,s57,s58,s59)
	SLOTS08(s60,s61,s62,s63,s64,s65,s66,s67)
	virtual void s68();
	virtual int getReservedCount(int kind);	// slot 69 (+0x114)
	unsigned char m_unmodelled04[0x11C - 0x24];
};

class HordeTransportContain : public HordeTransportContainPrimary, public HordeTransportContainIface20
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);

private:
	unsigned char m_11C;	// +0x11C
	Rva0047A040Base9E0 m_helper;	// +0x11D
};

// ?isValidContainerFor@HordeTransportContain@@UAE_NPAVObject@@_N1@Z @0x004771EB
bool HordeTransportContain::isValidContainerFor(Object *obj, bool checkCapacity, bool testPath)
{
	if (!reinterpret_cast<OpenContain *>(reinterpret_cast<char *>(this) + 0x20)->OpenContain::isValidContainerFor(obj, checkCapacity, testPath))
		return false;
	if (obj->m_hordeMember == 0 && obj->testStatus(OBJECT_STATUS_26))
	{
		bool ok = m_helper.rva00588BF3(this, obj) != 0;
		return ok;
	}
	if (checkCapacity == true)
	{
		const HordeTransportContainModuleData *data = m_moduleData;
		if (getReservedCount(0) + getContainCount() + obj->getTransportSlotCount() > data->m_maxSlots)
			return false;
	}
	return true;
}
