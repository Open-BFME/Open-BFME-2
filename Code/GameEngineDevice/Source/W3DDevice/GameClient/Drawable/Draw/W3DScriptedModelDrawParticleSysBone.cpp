// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Native BD4A7..BD691,490B; WB925C40 and native FieldParse wrappers
// BD691/BD6A8 prove the shared particle-at-bone reader and two list offsets.
// Preserve the owned32B carrier and its37B zero constructor; field meanings
// below come from WB named options and target accesses rather than its old name.
#include "ascii_string.h"
#include <string.h>
#include "../../../../../../GameEngine/Include/Common/INI/INI.h"
class Rva00704980 {
public:
 Rva00704980();
 int m_00,m_04,m_08,m_0C,m_10,m_14,m_18;
 char m_1C,m_1D,m_1E,m_1F;
};
struct BfmePod32;
// Keep the temporary's nontrivial lifetime separate from the generic STL
// carrier name: other units use that name for trivial 32-byte elements.
// Native accesses and the existing constructor establish this record layout.
struct ScriptedParticleBoneRecord:public Rva00704980 {
 ~ScriptedParticleBoneRecord(){((StringBase<char>*)&m_00)->clear();}
};
namespace _STL {
 template<class T>class allocator;
 template<class T,class A=allocator<T> >class list {public:void push_back(const T &);};
}
extern "C" const char *BfmeParticleBonePersistenceNames[];
extern "C" const char *BfmeParticleBoneTriggerNames[];
static __declspec(noinline) void parseParticleSysBone(INI *ini,void *instance,void *list)
{
 ScriptedParticleBoneRecord info;
 info.m_14=0;
 AsciiString &bone=*(AsciiString *)&info.m_00;
 bone=ini->getNextAsciiString();
 bone.toLower();
 INI::parseParticleSystemTemplate(ini,instance,&info.m_18,0);
 info.m_1C=false; info.m_1D=false;
 info.m_04=0; info.m_0C=0; info.m_08=0;
 const char *token=ini->getNextTokenOrNull(ini->m_sepsColon);
 while(token) {
  if(strcmp(token,"FollowBone")==0)
   info.m_1C=ini->scanBool(ini->getNextToken(ini->m_sepsColon));
  else if(strcmp(token,"HouseColor")==0)
   info.m_1D=ini->scanBool(ini->getNextToken(ini->m_sepsColon));
  else if(strcmp(token,"FXTrigger")==0)
   {
   const char *value=ini->getNextToken(ini->m_sepsColon);
   info.m_04=ini->scanIndexList(value,BfmeParticleBoneTriggerNames);
  }
  else if(strcmp(token,"Persist")==0)
   {
   const char *value=ini->getNextToken(ini->m_sepsColon);
   info.m_0C=ini->scanIndexList(value,BfmeParticleBonePersistenceNames);
  }
  else if(strcmp(token,"PersistID")==0)
   info.m_08=ini->scanInt(ini->getNextToken(ini->m_sepsColon));
  else if(strcmp(token,"OnlyIfOnWater")==0)
   info.m_1F=ini->scanBool(ini->getNextToken(ini->m_sepsColon));
  else if(strcmp(token,"OnlyIfOnLand")==0)
   info.m_1E=ini->scanBool(ini->getNextToken(ini->m_sepsColon));
  token=ini->getNextTokenOrNull(ini->m_sepsColon);
 }
 ((_STL::list<BfmePod32>*)list)->push_back((const BfmePod32&)info);
}
void ParseScriptedModelParticleSysBone(INI *ini,void *instance,void *,const void *)
{
 parseParticleSysBone(ini,instance,(char *)instance+0xB4);
}
void ParseScriptedAnimationParticleSysBone(INI *ini,void *instance,void *,const void *)
{
 parseParticleSysBone(ini,instance,(char *)instance+0x74);
}

// Full native enum tables: four persistence entries and three trigger
// entries plus their null terminators. Descriptive global names; original
// identifiers unknown. All pointed-to strings are owned exactly once.
extern "C" {
extern const char BfmeParticleBoneNone[]="NONE";
extern const char BfmeParticleBoneHold[]="HOLD";
extern const char BfmeParticleBoneKill[]="KILL";
extern const char BfmeParticleBoneSpawn[]="SPAWN";
extern const char BfmeParticleBoneCatapultRock[]="CATAPULT_ROCK";
extern const char BfmeParticleBoneTrebuchetRock[]="TREBUCHET_ROCK";
const char *BfmeParticleBonePersistenceNames[]={BfmeParticleBoneNone,BfmeParticleBoneHold,BfmeParticleBoneKill,BfmeParticleBoneSpawn,0};
const char *BfmeParticleBoneTriggerNames[]={BfmeParticleBoneNone,BfmeParticleBoneCatapultRock,BfmeParticleBoneTrebuchetRock,0};
}
