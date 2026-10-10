// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native fullC838F..C8492 CDECL animation-record parser and tableBCA560.
// ZH W3DModelDraw::parseAnimation supplies the semantic lead; BFME2 uses
// nested eleven-field INI parsing and a64B record (existing copy/dtor/ctor).
// Exact field tokens, offsets and callback pointers establish animation
// behavior; retained Bfme neutral record identity and original meanings
// only where table tokens prove them. All enum/token data explicitly owned.
// Native unused76B zeroed stack area retained without a class identity claim.
// size()!=0 gives native masked byte distance; barriers keep both separate
// front-pointer loads across the string calls instead of adding ESI save.
#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord000BDF17 {
 _STL::vector<AsciiString>names;AsciiString text0,text1;
 float word14,word18;int word1C;float word20,word24,word28;
 bool flag2C,flag2D;int word30;float word34,word38;bool flag3C;
 BfmeVectorRecord000BDF17(const AsciiString&,float);
 BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17&);
 ~BfmeVectorRecord000BDF17();
};

#include <string.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class INI;typedef void(*INIFieldParseProc)(INI*,void*,void*,const void*);
struct FieldParse{const char*token;INIFieldParseProc parse;const void*userData;int offset;};
class INI{public:static void parseAsciiStringVector(INI*,void*,void*,const void*);static void parseIndexList(INI*,void*,void*,const void*);static void parseReal(INI*,void*,void*,const void*);static void parseBool(INI*,void*,void*,const void*);static void parseInt(INI*,void*,void*,const void*);AsciiString getNextAsciiString();void initFromINI(void*,const FieldParse*);};
extern const FieldParse BfmeAnimationRecordFields[];
struct Rva000C838FOwner{char prefix[0x50];_STL::vector<BfmeVectorRecord000BDF17>animations;};
namespace _STL{template<>void vector<BfmeVectorRecord000BDF17>::push_back(const BfmeVectorRecord000BDF17&);}
void Rva000C838FParse(INI*ini,void*instance,void*store,const void*userData){
 AsciiString token=ini->getNextAsciiString();
 AsciiString original(token);token.toLower();
 BfmeVectorRecord000BDF17 record(token,0.0f);record.text1=original;
 unsigned char scratch[76];memset(scratch,0,sizeof scratch);
 if((unsigned)userData==1)record.word1C=2;
 ini->initFromINI(&record,BfmeAnimationRecordFields);
 if(record.word30<0)record.word30=0;
 if(record.word30>100)record.word30=100;
 if(record.names.size()!=0&&(_ReadWriteBarrier(),!record.names.front().isEmpty())&&(_ReadWriteBarrier(),!record.names.front().isNone()))
  ((Rva000C838FOwner*)instance)->animations.push_back(record);
}

class ModelConditionInfo{public:static void parseRealRange(INI*,void*,void*,const void*);};
extern const char BfmeAnimationMode0[]="MANUAL";
extern const char BfmeAnimationMode1[]="LOOP";
extern const char BfmeAnimationMode2[]="ONCE";
extern const char BfmeAnimationMode3[]="LOOP_PINGPONG";
extern const char BfmeAnimationMode4[]="PLAY_TO_FRAME";
extern const char BfmeAnimationMode5[]="LOOP_BACKWARDS";
extern const char BfmeAnimationMode6[]="ONCE_BACKWARDS";
const char*BfmeAnimationModeNames[]={BfmeAnimationMode0,BfmeAnimationMode1,BfmeAnimationMode2,BfmeAnimationMode3,BfmeAnimationMode4,BfmeAnimationMode5,BfmeAnimationMode6,0};
extern const char BfmeAnimationField0[]="AnimationName";
extern const char BfmeAnimationField1[]="AnimationMode";
extern const char BfmeAnimationField2[]="Distance";
extern const char BfmeAnimationField3[]="AnimationBlendTime";
extern const char BfmeAnimationField4[]="AnimationMustCompleteBlend";
extern const char BfmeAnimationField5[]="AnimationSpeedFactorRange";
extern const char BfmeAnimationField6[]="UseWeaponTiming";
extern const char BfmeAnimationField7[]="AnimationPriority";
extern const char BfmeAnimationField8[]="FadeBeginFrame";
extern const char BfmeAnimationField9[]="FadeEndFrame";
extern const char BfmeAnimationField10[]="FadingIn";
extern const FieldParse BfmeAnimationRecordFields[]={{BfmeAnimationField0,INI::parseAsciiStringVector,0,0},{BfmeAnimationField1,INI::parseIndexList,BfmeAnimationModeNames,28},{BfmeAnimationField2,INI::parseReal,0,20},{BfmeAnimationField3,INI::parseReal,0,32},{BfmeAnimationField4,INI::parseBool,0,44},{BfmeAnimationField5,ModelConditionInfo::parseRealRange,0,0},{BfmeAnimationField6,INI::parseBool,0,45},{BfmeAnimationField7,INI::parseInt,0,48},{BfmeAnimationField8,INI::parseReal,0,52},{BfmeAnimationField9,INI::parseReal,0,56},{BfmeAnimationField10,INI::parseBool,0,60},{0,0,0,0}};
