// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// ?rva0004C3147@OCLSpecialPower@@SA?AW4NameKeyType@@XZ @0x4C3147
// (69B): cached pool-name key for OCLSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("OCLSpecialPower"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

#include "Lib/Coord3D.h"
// First: BehaviorModule.h selects the Snapshot name-slot surface that
// Common/Player.h requires before Snapshot's first inclusion.
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

//-------------------------------------------------------------------------------------------------
class SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower( unsigned commandOptions ) = 0;
	virtual void doSpecialPowerAtObject( Object *obj, unsigned commandOptions ) = 0;
	virtual void doSpecialPowerAtLocation( const Coord3D *loc, unsigned commandOptions ) = 0;
	virtual bool rva0049466D( const Coord3D *loc ) = 0;
};

//-------------------------------------------------------------------------------------------------
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );
	virtual ~SpecialPowerModule();											// rowed 0x00493DEF

	virtual void doSpecialPower( unsigned commandOptions );
	virtual void doSpecialPowerAtObject( Object *obj, unsigned commandOptions );
	virtual void doSpecialPowerAtLocation( const Coord3D *loc, unsigned commandOptions );
	virtual bool rva0049466D( const Coord3D *loc );
};


//-------------------------------------------------------------------------------------------------
class __declspec(novtable) OCLSpecialPower : public SpecialPowerModule
{
public:
	OCLSpecialPower( Thing *thing, const ModuleData *moduleData );

	static NameKeyType rva0004C3147();

	virtual void doSpecialPower( unsigned commandOptions );
	virtual void doSpecialPowerAtLocation( const Coord3D *loc, unsigned commandOptions );
	virtual bool rva0049466D( const Coord3D *loc );
};

// ?rva0004C3147@OCLSpecialPower@@SA?AW4NameKeyType@@XZ
NameKeyType OCLSpecialPower::rva0004C3147()
{
	static NameKeyType TheOCLSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("OCLSpecialPower");
	return TheOCLSpecialPowerPoolKey;
}
