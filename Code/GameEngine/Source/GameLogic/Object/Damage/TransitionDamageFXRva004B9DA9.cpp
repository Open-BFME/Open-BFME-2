// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Source/Common
// stlport
// ?rva004B9DA9@TransitionDamageFX@@QAEX_N@Z @0x004B9DA9 367B
// TransitionDamageFX walk over the 0x2C-byte records at +0xD4/+0xD8: each
// record's object (findObjectByID) supplies a status through the virtual at
// slot 8 of its +0x254 module; every AsciiString in the record's +4/+8 array
// goes to Drawable::rva002724FD with status != 3. When the bool argument is
// set the record object's own TransitionDamageFX (findModule with a static
// "TransitionDamageFX" key) recurses with false and a status-3 record with an
// OCL at +0x10 converts its +0x20 bone position and creates the OCL.
// Donor: BFME1 TransitionDamageFX::rva002523E0 (same control flow).
// Recursion at 0x004B9EA9; caller 0x004BA19D.

#include "ascii_string.h"
#include "Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include <vector>
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/Common/ObjectModule.h"

typedef int Int;

class Matrix3D;
class Drawable
{
public:
	void rva002724FD(const AsciiString &a, int b, int c, float d, float e);
	int getPristineBonePositions(const char *, int, Coord3D *, Matrix3D *, int, int) const;
	void rva002724FD(const AsciiString &name, unsigned char visible, int a, float b, float c);
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Dict;
class BehaviorModuleinterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void mapLoadPostProcess(const Dict *) = 0;
};
// The three-slot table the constructor installs at +0x10 (0x010B2588).
class DamageInfo;
enum BodyDamageType;
class DamageModuleinterface
{
public:
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) = 0;
};
class Xfer;
class Rva004BA1C8Triple {
public:
	unsigned int a;
	unsigned int b;
	unsigned int c;
};
class Rva004BA1C8 {
public:
	~Rva004BA1C8();
	Rva004BA1C8 &operator=(const Rva004BA1C8 &other);
private:
	int m_00;
	_STL::vector<AsciiString> m_04;
	unsigned int m_10;
	Rva004BA1C8Triple m_14;
	Rva004BA1C8Triple m_20;
};
class Rva004BA1D0;
class TransitionDamageFXModuleDataView;
enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};
// The neighbour-record vector at +0xD4 of the module. Its constructor is the folded
// Vector_base 0x00211E58 and its destructor the row 0x004BA35A.
class TensileFormationUpdateMember : public _STL::vector<Rva004BA1C8>
{
public:
	__forceinline TensileFormationUpdateMember() {}
	~TensileFormationUpdateMember();
};
class DamageModule : public ObjectModule,
    public BehaviorModuleinterface,
    public DamageModuleinterface
{
public:
    DamageModule(Thing *thing, const ModuleData *moduleData);
    virtual ~DamageModule();
};
// Layout from constructor 0x00252F50: interfaces at +0x0C and +0x10, 0x30
// zeroed words from +0x14, and the vector at +0xD4 (allocation 0xE0).
class TransitionDamageFX : public DamageModule
{
public:
    TransitionDamageFX(Thing *thing, const ModuleData *moduleData);
    void bfmeGoFDE();
    void bfmeUseFDE(void *r);
    void rva004B9DA9(bool applyTransition);
    virtual NameKeyType getModuleNameKey() const;
    virtual void mapLoadPostProcess(const Dict *);
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType);

protected:
    virtual ~TransitionDamageFX();
    virtual void xfer(Xfer *xfer);
    const TransitionDamageFXModuleDataView *getTransitionDamageFXModuleData() const
    {
        return (const TransitionDamageFXModuleDataView *)m_moduleData;
    }

private:
    ParticleSystemID m_particleSystemID[4][12]; // +0x14
    TensileFormationUpdateMember resolvedNeighbors; // +0xD4
};

enum KindOfType
{
	KINDOF_FIRST = 0
};

class BodyModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
	virtual void b05(); virtual void b06(); virtual void b07();
	virtual int getStatus(); // slot 8
	virtual void b09();
	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
	virtual const DamageInfo *getLastDamageInfo() const; // slot 15
};

class Object : public Thing
{
public:
	bool isKindOf(KindOfType t) const;
	unsigned getID() const { return m_id; }
	Module *findDamageModule(NameKeyType key) const { return findModule(key); }
	BodyModuleInterface *getBodyModule() const { return m_body; }

protected:
	Module *findModule(NameKeyType key) const;

public:
	unsigned char m_unmodelled60[0x14];
	unsigned m_id;					// +0x74
	unsigned char m_unmodelled78[0x254 - 0x78];
	BodyModuleInterface *m_body;	// +0x254
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);
	void create(void *primaryObj, void *primary, void *secondary, Int lifetimeFrames);
	static __forceinline void create(const ObjectCreationList *ocl, Object *primaryObj, const Coord3D *primary, const Coord3D *secondary)
	{
		if (ocl)
			((ObjectCreationList *)ocl)->create(primaryObj, (void *)primary, (void *)secondary, 0);
	}
};

struct Rva004B9DA9Record
{
	ObjectID m_objectID;
	AsciiString *m_nameBegin;
	AsciiString *m_nameEnd;
	void *m_unmodelled0C;
	ObjectCreationList *m_objectCreationList;
	unsigned char m_unmodelled14[0x0C];
	Coord3D m_localPosition;
};

// The vector words at +0xD4/+0xD8 the walk reads.
struct Rva004B9DA9RecordRange
{
	Rva004B9DA9Record *m_recordBegin;
	Rva004B9DA9Record *m_recordEnd;
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

void TransitionDamageFX::rva004B9DA9(bool applyTransition)
{
	const void *data = getModuleData();
	if (data == 0)
		return;

	Drawable *draw = m_object->getDrawable();
	if (draw == 0)
		return;

	Rva004B9DA9RecordRange &records = *reinterpret_cast<Rva004B9DA9RecordRange *>(&resolvedNeighbors);
	for (Rva004B9DA9Record *it = records.m_recordBegin; it != records.m_recordEnd; )
	{
		Rva004B9DA9Record *record = it++;

		int status = 3;
		Object *object = TheGameLogic->findObjectByID(record->m_objectID);
		if (object != 0)
			status = object->m_body->getStatus();

		for (AsciiString *name = record->m_nameBegin; name != record->m_nameEnd; ++name)
			draw->rva002724FD(*name, (unsigned char)(status != 3), 0, 0.0f, 0.0f);

		if (applyTransition)
		{
			static NameKeyType transitionDamageKey =
				TheNameKeyGenerator->nameToKey("TransitionDamageFX");

			if (object != 0)
			{
				TransitionDamageFX *transition =
					(TransitionDamageFX *)object->findDamageModule(transitionDamageKey);
				if (transition != 0)
					transition->rva004B9DA9(false);
			}

			if (status == 3 && record->m_objectCreationList != 0)
			{
				Coord3D worldPosition;
				worldPosition.x = record->m_localPosition.x;
				worldPosition.y = record->m_localPosition.y;
				worldPosition.z = record->m_localPosition.z;
				m_object->convertBonePosToWorldPos(&worldPosition, 0, &worldPosition, 0);
				ObjectCreationList *ocl = record->m_objectCreationList;
				if (ocl != 0)
					ocl->create(m_object, m_object, 0);
			}
		}
	}
}
