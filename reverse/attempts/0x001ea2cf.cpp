// ?setLocomotorAndBaseSpeed@LocomotorSet@@QAEXPAVINI@@@Z
// partial score=0.99 date=2026-10-09
// NEAR draft (natural WB-shaped body; WB 0x00AF2420 LocomotorSet::setLocomotorAndBaseSpeed).
// 224B vs 223B: registers and code all match; only the stack packing differs:
// cl gives the dead INI* home [ebp+8] to the spilled locomotor template and a
// fresh slot to the set key where retail puts the key at [ebp+8] and packs the
// template with the 8-byte INIException at [ebp-8]. Strings fixed (tab in both).
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
class INI {
public: int scanIndexList(const char *, const char *const *);
 int getLoadType() const { return loadType; }
private: char unknown00[8]; int loadType;
};
class AIUpdateModuleData {
public: char unknown00[8]; BfmeLocomotorSetMap templates;
};
class ThingTemplate {
public: AIUpdateModuleData *friend_getAIModuleInfo();
 const AsciiString& getName() const { return name; }
 void rva0033E17D(LocomotorSetType, const LocomotorTemplate *);
 void Rva0033D396StoreFloat(int, float);
private: char unknown00[0x64]; AsciiString name;
};
class LocomotorStore {
public: LocomotorTemplate *findLocomotorTemplate(const AsciiString &);
};
extern LocomotorStore *TheLocomotorStore;
extern const char *TheLocomotorSetNames[];
#include "../../reference/shims/iniexception/Common/INIException.h"
class Rva001EA2CFLocomotorDefinition {
public: void rva001EA2CF(INI *ini, ThingTemplate *instance);
private: char unknown00[0x18]; AsciiString name; AsciiString setName; float speed;
};
void Rva001EA2CFLocomotorDefinition::rva001EA2CF(INI *ini, ThingTemplate *instance) {
 AIUpdateModuleData *self=instance->friend_getAIModuleInfo();
 if (!self) throw INIException(3,"Attempted to specify a locomotor for object %s without an AIUpdate	block.",instance->getName().str());
 LocomotorSetType set=(LocomotorSetType)ini->scanIndexList(setName.str(),TheLocomotorSetNames);
 const LocomotorTemplate *loco=TheLocomotorStore->findLocomotorTemplate(name);
 if (!self->templates[set].empty()) {
  if (ini->getLoadType()!=2 && ini->getLoadType()!=4)
   throw INIException(3,"re-specifying a LocomotorSet	is no longer allowed");
 }
 instance->rva0033E17D(set,loco);
 instance->Rva0033D396StoreFloat((int)set,speed);
}
