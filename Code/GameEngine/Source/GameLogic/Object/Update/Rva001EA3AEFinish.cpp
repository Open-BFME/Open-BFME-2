// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
#include <vector>

class LocomotorTemplate;

// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h); saved in save files.
enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,

	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,

	LOCOMOTORSET_COUNT
};

typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;


// Reuse verified provider definitions instead of emitting competing STL copies.
namespace _STL {
template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType&);
template<> BfmeLocomotorTemplateVector::iterator BfmeLocomotorTemplateVector::erase(iterator, iterator);
template<> void BfmeLocomotorTemplateVector::push_back(const value_type&);
}

// Reference1281192f68 GeneralsMD AIUpdate.cpp parseLocomotorSet validation/assignment.
// Target adaptation: stored name+18, set-name+1C and speed+20, method(INI*,ThingTemplate*).
// Original receiver and method names unknown. Prefix is only a measured ABI view.
#include "ascii_string.h"
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../../Include/Common/INI/FieldParse.h"
#include "../../../../Include/Common/INI/INI.h"
// FieldParse table for the LocomotorDefinition parse, read from retail at 0x00BDEA60.
extern "C" {
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x007DEA60: 3 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00BDEA60[4] = {
	{ "Speed", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "Condition", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "Locomotor", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ 0, 0, 0, 0 }
};
class AIUpdateModuleData {
public: char unknown00[8]; BfmeLocomotorSetMap templates;
};
#include "../../../../Include/Common/ThingTemplate.h"
#include "../../../../Include/GameLogic/LocomotorStore.h"
extern LocomotorStore *TheLocomotorStore;
extern const char *TheLocomotorSetNames[];
#include "../../../../Include/GameLogic/LocomotorSet.h"
class Rva001EA2CFLocomotorDefinition {
public:
	void rva001EA3AE(INI *ini, ThingTemplate *instance);
private: char unknown00[0x18]; AsciiString name; AsciiString setName; float speed;
};
// Native 1EA3AE/70 confirms measured receiver members and forward signature.
// FieldParse data VA00BDEA60 is read from retail; no function address is embedded.
void Rva001EA2CFLocomotorDefinition::rva001EA3AE(INI *ini, ThingTemplate *instance) {
 name.set("");
 setName.set("");
 speed=0.0f;
 ini->initFromINI(this, g_00BDEA60);
 ((LocomotorSet *)this)->setLocomotorAndBaseSpeed(ini, instance);
}
