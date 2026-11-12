// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Native5EDB74..5EDE64 constructs the same0x54 object whose destructor
// already owns5EDE64..5EDED7. WB names the family RegionAwardMovieClip::Impl.
// Keep the existing address-derived owner; the field offsets and callback
// ABI come from retail. The five binding suffixes independently connect the
// OnOpen/OnClosed and button/player callbacks. Clean matched ArmyMemberIcon
// and Palantir constructors guide concat and delegate lifetime semantics.
// Native callback args are one text pointer, not inferred from donor ABI.
#include "ascii_string.h"
#include "unicode_string.h"
#include <ctype.h>
#include <stdlib.h>
#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager*g_bfmeAptWindowManager;
#include "../../Include/GameClient/RegionAwardMovieClip.h"
namespace StrategicHUD {
class RegionAwardMovieClip::Impl {
public:
 void SetRegionNameString(const UnicodeString&);
 void SetRegionBonusTextString(int,const UnicodeString&);
 void SetPlayerString(int,const char*,const UnicodeString&);
};
}
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../../Libraries/Source/Apt/AptCommandTarget.h"
#include "../../Include/Common/DelegateDesc.h"
struct RegionAwardBinding : DelegateDesc {
 template<class T> RegionAwardBinding(T*o,void(T::*m)(const char*)):DelegateDesc(o,m){}
};
class Rva00579E47 {
public: Rva00579E47(const DelegateDesc&);
protected: struct Ref {void*vt;int count;}; Ref*pointer;
};
#include "../../Include/Common/AptCommandMap.h"
template<class T>class AptRef:public Rva00579E47 {
public:
 AptRef(const RegionAwardBinding&regionAwardBinding):Rva00579E47(regionAwardBinding){}
 ~AptRef(){if(pointer)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)pointer);}
};
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddRegionAwardCommand(AptCommandMapAdder &adder, const AsciiString&name,RegionAwardBinding desc)
{
	adder.AddCommandMap(name,desc);
}
class Rva005242D7 {
public:Rva005242D7();~Rva005242D7();
private:char pad[12];
};
struct BfmeStringRecord005ED5F3;
namespace _STL{
template<class T>class allocator;
template<class T,class A>class vector;
template<>class vector<BfmeStringRecord005ED5F3,allocator<BfmeStringRecord005ED5F3> >{
public:vector(unsigned int);~vector();
 unsigned int size()const{return (int)((char*)end-(char*)begin)/20;}
private:BfmeStringRecord005ED5F3*begin,*end,*capacity;
};
}
class RegionAwardOwner {
public:
 virtual void slot0();
 virtual void closed();
 virtual void playerClicked(int);
 virtual void selectClicked();
 virtual void cancelClicked();
};
#include "../../Include/Common/Rva000B3F84Pair.h"
struct AsciiStringRef{const AsciiString*string;};
struct AsciiStringPlusString:AsciiStringRef{AsciiStringRef second;};
struct AsciiStringPlusStringText:AsciiStringPlusString {
 operator AsciiString();Rva000B3F84Pair text;
};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){
 AsciiStringPlusString r;r.string=&a;r.second.string=&b;return r;
}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString&left,const char*right){
 Rva000B3F84Pair text;text.init(right);
 AsciiStringPlusStringText r;static_cast<AsciiStringPlusString&>(r)=left;r.text=text;return r;
}

class Rva005EDE64
{
public:
 Rva005EDE64(RegionAwardOwner*,int,const AsciiString&);
 ~Rva005EDE64();
 void OnOpen(const char*);void OnClosed(const char*);
 void OnCancelButtonClicked(const char*);void OnSelectButtonClicked(const char*);void OnPlayerClicked(const char*);
private:
 RegionAwardOwner*m_owner;
 int m_level;
 AsciiString m_name;
 AptCommandMapAdder m_commands;
 Rva005242D7 m_images;
 int m_state;
 UnicodeString m_cached;
 UnicodeString m_bonusCache[6];
 _STL::vector<BfmeStringRecord005ED5F3,_STL::allocator<BfmeStringRecord005ED5F3> > m_players;
 int m_selected;
};
Rva005EDE64::Rva005EDE64(RegionAwardOwner*owner,int level,const AsciiString&name)
:m_owner(owner),m_level(level),m_name(name),m_state(0),m_players(2),m_selected(-1) {
 AsciiString prefix;
 prefix.format("_level%u.",m_level);
 AddRegionAwardCommand(m_commands, prefix+m_name+"_OnOpen",RegionAwardBinding(this,&Rva005EDE64::OnOpen));
 AddRegionAwardCommand(m_commands, prefix+m_name+"_OnClosed",RegionAwardBinding(this,&Rva005EDE64::OnClosed));
 AddRegionAwardCommand(m_commands, prefix+m_name+"_OnCancelButtonClicked",RegionAwardBinding(this,&Rva005EDE64::OnCancelButtonClicked));
 AddRegionAwardCommand(m_commands, prefix+m_name+"_OnSelectButtonClicked",RegionAwardBinding(this,&Rva005EDE64::OnSelectButtonClicked));
 AddRegionAwardCommand(m_commands, prefix+m_name+"_OnPlayerClicked",RegionAwardBinding(this,&Rva005EDE64::OnPlayerClicked));
 ((StrategicHUD::RegionAwardMovieClip::Impl*)this)->SetRegionNameString(UnicodeString::TheEmptyString);
 for(int i=0;i<6;++i)((StrategicHUD::RegionAwardMovieClip::Impl*)this)->SetRegionBonusTextString(i,UnicodeString::TheEmptyString);
 int m_playerCount=m_players.size();
 for(int i=0;i<m_playerCount;++i){
 ((StrategicHUD::RegionAwardMovieClip::Impl*)this)->SetPlayerString(i,"PlayerName",UnicodeString::TheEmptyString);
 ((StrategicHUD::RegionAwardMovieClip::Impl*)this)->SetPlayerString(i,"NumRegions",UnicodeString::TheEmptyString);
 ((StrategicHUD::RegionAwardMovieClip::Impl*)this)->SetPlayerString(i,"NumUnits",UnicodeString::TheEmptyString);
 }
}
Rva005EDE64::~Rva005EDE64(){}
void Rva005EDE64::OnOpen(const char*){if(m_state==0)m_state=1;}
void Rva005EDE64::OnClosed(const char*){if(m_state==2){m_state=3;m_owner->closed();}}
void Rva005EDE64::OnCancelButtonClicked(const char*){if(m_state==1&&!g_bfmeAptWindowManager->field318)m_owner->cancelClicked();}
void Rva005EDE64::OnSelectButtonClicked(const char*){if(m_state==1&&!g_bfmeAptWindowManager->field318)m_owner->selectClicked();}
void Rva005EDE64::OnPlayerClicked(const char*text){
 if(text&&isdigit(*text)){
  int i=atoi(text);
  if(i>=0&&(unsigned int)i<m_players.size()&&m_state==1&&!g_bfmeAptWindowManager->field318)m_owner->playerClicked(i);
 }
}
