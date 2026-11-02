// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
//
// InstantDeathBehaviorModuleData FieldParse procs, BFME 2 layout. The table
// at VA 0x00C41FA8 (read by the rowed buildFieldParse 0x0045D35F) maps FX ->
// the shared list parser 0x00339B9A at +0x38, OCL -> 0x0045D1BD, Weapon ->
// 0x0045D200 and Sound -> 0x0045D2F6. The OCL and Weapon procs are Zero
// Hour's InstantDeathBehavior.cpp file statics (scoped to the module data
// class here so the ledger names stay unique; several ZH units carry a static
// parseOCL), with the BFME 2 vector offsets
// (+0x44 / +0x50; the module data ctor 0x0045D176 builds four vectors from
// +0x38) and the BFME 2 findWeaponTemplate taking a const AsciiString &.
// Sound is a BFME 2 addition: each token goes through the pinned audio
// token parser 0x00339184 into a ref-counted handle that is appended to the
// vector at +0x5C and released (rowed Release_Ref) at scope exit; its name
// stays address-derived.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
#include <windows.h>

#include "../../../../Include/Common/INI/INI.h"

class ObjectCreationList;
class WeaponTemplate;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};
extern ObjectCreationListStore *TheObjectCreationListStore;

#include "../../../../Include/GameLogic/WeaponStore.h"
extern WeaponStore *TheWeaponStore;

// Same 4-byte element the rowed push_back 0x0005A084 is instantiated on.
struct Rva0005A084Element { int a[1]; };

// Audio handle the Sound proc fills: one ref-counted pointer, released on exit.
void Rva00339184(const char *token, void *store);

class InstantDeathBehaviorModuleData
{
public:
	static void parseOCL(INI *ini, void *instance, void *store, const void *userData);
	static void parseWeapon(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x44];
	_STL::vector<const ObjectCreationList *> m_ocls;	// +0x44
	_STL::vector<const WeaponTemplate *> m_weapons;		// +0x50
	_STL::vector<Rva0005A084Element> m_sounds;		// +0x5C
};

// ?parseOCL@InstantDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void InstantDeathBehaviorModuleData::parseOCL(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	InstantDeathBehaviorModuleData *self = (InstantDeathBehaviorModuleData *)instance;
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls.push_back(ocl);
	}
}

// ?parseWeapon@InstantDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void InstantDeathBehaviorModuleData::parseWeapon(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	InstantDeathBehaviorModuleData *self = (InstantDeathBehaviorModuleData *)instance;
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(AsciiString(token));	// could be null! this is OK!
		self->m_weapons.push_back(wt);
	}
}
