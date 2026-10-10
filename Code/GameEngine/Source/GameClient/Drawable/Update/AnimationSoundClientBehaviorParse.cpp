// Native004CA798..004CAB2B full915B, WB126F130/1707 and AnimationSound
// table C5F064 establish the parser identity and token order. Reference searches
// found no applicable parser in BF1 or GeneralsMD; reconstruction follows
// independently matching native and WB branches, strings and call relationships.
// Required/excluded flags occupy19 words; pool entry is A8B with owning sound
// reference at4. Existing neutral constructor/tree/flag ABI names are reused;
// WeaponTemplateSetHead and BitFlags304 are provider spellings, not target
// semantic type or bound claims. Audio getter is virtual slot75; INI separators420.
// Explicit frame scan precedes constructor arguments as in native code.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
#include "ascii_string.h"
#include <string.h>
class INIException {public:char *message;int code;INIException(int,const char*,...);INIException(const INIException&);~INIException();};
class INI {public:const char*getNextSubToken(const char*);const char*getNextToken(const char*);const char*getNextTokenOrNull(const char*);float scanReal(const char*);char pad[0x420];const char *separators;};
class OpaqueRefCounted{public:void Release_Ref();};
class Rva0036CA00Str {public:Rva0036CA00Str(const Rva0036CA00Str&);~Rva0036CA00Str(){if(object)object->Release_Ref();}OpaqueRefCounted *object;};
template<int N>class LookupSlots:public LookupSlots<N-1>{public:virtual void gap(char(*)[N]);};template<>class LookupSlots<0>{};
class SoundLookupView:public LookupSlots<75>{public:virtual Rva0036CA00Str lookup(const AsciiString&);};
class AudioManager;extern AudioManager *TheAudio;
template<int N>class BitFlags{public:bool setBitByName(const char*);};
class WeaponTemplateSetHead {public:WeaponTemplateSetHead(){} WeaponTemplateSetHead(const WeaponTemplateSetHead&);unsigned words[19];};
class Rva004C9E94 {public:Rva004C9E94(const Rva0036CA00Str&,const int*,float,const WeaponTemplateSetHead&,const WeaponTemplateSetHead&);int key;Rva0036CA00Str sound;float frame;WeaponTemplateSetHead required,excluded;bool check;};
struct AnimationSoundTreeNode;
class AnimationSoundTree {public:AnimationSoundTreeNode**rva004CA68B(AnimationSoundTreeNode**,const void*);};
enum NameKeyType{KEY0=0};class NameKeyGenerator{public:NameKeyType nameToKey(const AsciiString&);};extern NameKeyGenerator *TheNameKeyGenerator;
void Rva004CA798Parse(INI *ini,void *data,void*)
{
 if(!data)return;
 char soundTag[]="Sound";
 char requiredTag[]="RequiredMC";
 char excludedTag[]="ExcludedMC";
 char animationTag[]="Animation";
 char framesTag[]="Frames";
 AsciiString soundName(ini->getNextSubToken(soundTag));
 if(soundName.isEmpty())throw INIException(3,"AnimationSound line: sound name cannot empty");
 Rva0036CA00Str sound=((SoundLookupView*)TheAudio)->lookup(soundName);
 if(!sound.object)throw INIException(3,"AnimationSound line: unknown sound '%s'",soundName.str());
 const char *token=ini->getNextTokenOrNull(ini->separators);
 WeaponTemplateSetHead required,excluded;
 memset(&required,0,sizeof(required));memset(&excluded,0,sizeof(excluded));
 if(token && !_strcmpi(token,requiredTag)){
  token=ini->getNextToken(ini->separators);
  bool done=false;
  do{
   if(!((BitFlags<304>*)&required)->setBitByName(token))throw INIException(3,"AnimationSound line: unknown model condition '%s' in %s list",token,requiredTag);
   token=ini->getNextTokenOrNull(ini->separators);
   if(token && !_strcmpi(token,requiredTag))token=ini->getNextTokenOrNull(ini->separators);
   if(!token || !_strcmpi(token,excludedTag) || !_strcmpi(token,animationTag) || !_strcmpi(token,framesTag))done=true;
  }while(!done);
 }
 if(token && !_strcmpi(token,excludedTag)){
  token=ini->getNextToken(ini->separators);
  bool done=false;
  do{
   if(!((BitFlags<304>*)&excluded)->setBitByName(token))throw INIException(3,"AnimationSound line: unknown model condition '%s' in %s list",token,excludedTag);
   token=ini->getNextTokenOrNull(ini->separators);
   if(token && !_strcmpi(token,excludedTag))token=ini->getNextTokenOrNull(ini->separators);
   if(!token || !_strcmpi(token,animationTag) || !_strcmpi(token,framesTag))done=true;
  }while(!done);
 }
 do{
  if(!token || _strcmpi(token,animationTag))throw INIException(3,"AnimationSound line: expected '%s' next, got '%s'",animationTag,token?token:"<End of line>");
  AsciiString animationName(ini->getNextToken(ini->separators));
  animationName.toUpper();
  int key=TheNameKeyGenerator->nameToKey(animationName);
  token=ini->getNextSubToken(framesTag);
  do{
   float frame=ini->scanReal(token);
   Rva004C9E94 info(sound,&key,frame,required,excluded);
   AnimationSoundTreeNode *node;
   ((AnimationSoundTree*)((char*)data+8))->rva004CA68B(&node,&info);
   token=ini->getNextTokenOrNull(ini->separators);
  }while(token && _strcmpi(token,animationTag));
 }while(token);
}
