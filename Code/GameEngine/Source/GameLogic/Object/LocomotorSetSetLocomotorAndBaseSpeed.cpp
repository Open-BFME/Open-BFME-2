// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/iniexception /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?setLocomotorAndBaseSpeed@LocomotorSet@@QAEXPAVINI@@PAVThingTemplate@@@Z, retail 0x001EA2CF, 223 bytes.
// Target identity: WorldBuilder names 0x00AF2420 LocomotorSet::setLocomotorAndBaseSpeed in
// Locomotor.cpp with the same validation strings; native 1EA2CF..1EA3AE RET8 proves the INI
// and ThingTemplate arguments and the receiver offsets +18/+1C/+20. The BFME1 donor
// (Rva001BD0D0LocomotorBinding.cpp) supplies the body shape; BFME2's scanIndexList is a member.
// The work after the first throw sits in an else block: that scope makes VC7.1 pack the set
// key into the dead INI* home and share [ebp-4] between the template and the INIException.
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

// Compare the iterators here without emitting an /O1 copy of vector::empty;
// AIUpdate.cpp owns the independently verified retail out-of-line body.
static __forceinline bool locomotorTemplatesEmpty(const BfmeLocomotorTemplateVector &values)
{
 return values.begin() == values.end();
}

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;


// Reuse verified provider definitions instead of emitting competing STL copies.
namespace _STL {
template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType&);
template<> BfmeLocomotorTemplateVector::iterator BfmeLocomotorTemplateVector::erase(iterator, iterator);
template<> void BfmeLocomotorTemplateVector::push_back(const value_type&);
}

// Reference1281192f68 GeneralsMD AIUpdate.cpp parseLocomotorSet validation/assignment.
// Target adaptation: stored name+18, set-name+1C and speed+20, method(INI*,ThingTemplate*).
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
#include "Common/INIException.h"
class LocomotorSet {
public: void setLocomotorAndBaseSpeed(INI *ini, ThingTemplate *instance);
private: char unknown00[0x18]; AsciiString name; AsciiString setName; float speed;
};
void LocomotorSet::setLocomotorAndBaseSpeed(INI *ini, ThingTemplate *instance) {
 AIUpdateModuleData *self=instance->friend_getAIModuleInfo();
 if (!self)
  throw INIException(3,"Attempted to specify a locomotor for object %s without an AIUpdate\tblock.",instance->getName().str());
 else {
  LocomotorSetType set=(LocomotorSetType)ini->scanIndexList(setName.str(),TheLocomotorSetNames);
  const LocomotorTemplate *loco=TheLocomotorStore->findLocomotorTemplate(name);
  if (!locomotorTemplatesEmpty(self->templates[set]) && ini->getLoadType()!=2 && ini->getLoadType()!=4)
   throw INIException(3,"re-specifying a LocomotorSet\tis no longer allowed");
  instance->rva0033E17D(set,loco);
  instance->Rva0033D396StoreFloat((int)set,speed);
 }
}
