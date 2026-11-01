// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport
// FILE: OCLSpecialPower.cpp //////////////////////////////////////////////////////////////////////
// Desc:   Special powers that are driven by object creation lists (BFME 2).
//
// Target facts:
//  - ??0OCLSpecialPower (0x004C30D8, 42 bytes) calls the rowed
//    SpecialPowerModule constructor 0x00493C5A, then stores three tables:
//    0x00C5CC74 at +0x00 (the ObjectModule chain, 15 slots), the folded
//    SpecialPowerModule BehaviorModuleInterface table 0x00BEFCF8 at +0x0C and
//    0x00C5CC10 at +0x10 (the SpecialPowerModuleInterface table, 25 slots);
//  - slots 10, 12 and 18 of 0x00C5CC10 are the rowed overriders
//    doSpecialPower (0x004C3204), doSpecialPowerAtLocation (0x004C3365) and
//    rva0049466D (0x004C3260);
//  - the CreateLocation parse table names (VA 0x00DCDFD0) are Zero Hour's
//    six plus three BFME 2 placements.
// Donor (Zero Hour OCLSpecialPower.cpp) facts: the class, method and
// placement names. Zero Hour's ModuleData, xfer/crc/loadPostProcess bodies,
// disabled check and angle argument are not BFME 2's.
//
// No vtable is emitted here: most of the three tables' slots still carry
// placeholder owners, so the class is novtable and the constructor stores the
// tables by their data-ledger names, each defined by a census object
// (StopSpecialPowerCtor.cpp precedent). All three names are the ledger aliases
// that the destructor's current owner Rva004C3108 (0x004C3108) defines.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lib/Coord3D.h"
#include "../../../../Include/Common/Module.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// BFME 2's list (retail VA 0x00DCDFD0, .data, read from retail): the
// CreateLocation parseIndexList names of OCLSpecialPowerModuleData's table,
// Zero Hour's six plus three BFME 2 placements.
const char* TheOCLCreateLocTypeNames[] =
{
	"CREATE_AT_EDGE_NEAR_SOURCE",
	"CREATE_AT_EDGE_NEAR_TARGET",
	"CREATE_AT_EDGE_NEAR_TARGET_AND_MOVE_TO_LOCATION",
	"CREATE_AT_LOCATION",
	"USE_OWNER_OBJECT",
	"CREATE_ABOVE_LOCATION",
	"CREATE_AT_EDGE_FARTHEST_FROM_TARGET",
	"CREATE_CLOSEST_TO_SPAWN_POINT",
	"USE_SECONDARY_OBJECT_LOCATION",
	0
};

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

// The constructor's three tables, by their data-ledger names.
extern "C" const void *const __identifier("??_7Rva004C3108@@6BRva00493DEF@@@")[];				// 0x00C5CC74
extern "C" const void *const __identifier("??_7Rva004C3108@@6BMiBase1@@@")[];					// 0x00BEFCF8
extern "C" const void *const __identifier("??_7Rva004C3108@@6BRva004C3108_B2@@@")[];			// 0x00C5CC10

//-------------------------------------------------------------------------------------------------
class __declspec(novtable) OCLSpecialPower : public SpecialPowerModule
{
public:
	OCLSpecialPower( Thing *thing, const ModuleData *moduleData );

	virtual void doSpecialPower( unsigned commandOptions );
	virtual void doSpecialPowerAtLocation( const Coord3D *loc, unsigned commandOptions );
	virtual bool rva0049466D( const Coord3D *loc );
};

//-------------------------------------------------------------------------------------------------
// ??0OCLSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C30D8
OCLSpecialPower::OCLSpecialPower( Thing *thing, const ModuleData *moduleData )
							 : SpecialPowerModule( thing, moduleData )
{
	*(unsigned int *)this = (unsigned int)__identifier("??_7Rva004C3108@@6BRva00493DEF@@@");
	*(unsigned int *)((char *)this + 0x0C) = (unsigned int)__identifier("??_7Rva004C3108@@6BMiBase1@@@");
	*(unsigned int *)((char *)this + 0x10) = (unsigned int)__identifier("??_7Rva004C3108@@6BRva004C3108_B2@@@");
}
