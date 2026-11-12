// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// WB0161D1A0 identifies the territory-details implementation constructor.
// Native5F1DB0..5F207C fixes its boundary, 0x48 layout and callback flow.
// The owned61-byte concat operator is visible without inlining its call: the
// compiler can reuse dead operand slots, preserving the native40-byte frame.
// Native region-bonus label and formatting family. Static helpers are kept
// with their consumer to preserve the compiler's private register ABI.
#include "ascii_string.h"
#include "unicode_string.h"
struct RegionBonusPair { const char *format;const char *tooltip; };
struct RegionBonusRecord { int kind;RegionBonusPair labels; };
extern const char RegionBonusFormat0[]="STRATEGICHUD:RegionAbsoluteBonus";
extern const char RegionBonusTooltip0[]="STRATEGICHUD:RegionCommandPointBonusTooltip";
extern const char RegionBonusFormat1[]="STRATEGICHUD:RegionPercentageBonus";
extern const char RegionBonusTooltip1[]="STRATEGICHUD:RegionAttackBonusTooltip";
extern const char RegionBonusTooltip2[]="STRATEGICHUD:RegionDefenseBonusTooltip";
extern const char RegionBonusTooltip3[]="STRATEGICHUD:RegionExperienceBonusTooltip";
extern const char RegionBonusTooltip4[]="STRATEGICHUD:RegionResourceBonusTooltip";
extern const char RegionBonusTooltip5[]="STRATEGICHUD:RegionPowerPointBonusTooltip";
extern const RegionBonusRecord RegionBonusRecords[]={
 {0, {RegionBonusFormat0, RegionBonusTooltip0}},
 {1, {RegionBonusFormat1, RegionBonusTooltip1}},
 {2, {RegionBonusFormat1, RegionBonusTooltip2}},
 {3, {RegionBonusFormat1, RegionBonusTooltip3}},
 {4, {RegionBonusFormat1, RegionBonusTooltip4}},
 {5, {RegionBonusFormat0, RegionBonusTooltip5}}
};

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
static __declspec(noinline) const RegionBonusPair *LookupRegionBonus(int kind) {
 int i=0;
 if(kind) { do {++i;} while(RegionBonusRecords[i].kind!=kind); }
 return &RegionBonusRecords[i].labels;
}
static __declspec(noinline) UnicodeString FormatRegionBonus(int kind,int count) {
 if(count>0) {
  UnicodeString text;
  bool exists;
  UnicodeString format=TheGameText->fetch(LookupRegionBonus(kind)->format,&exists);
  if(exists)text.format(format.str(),count);
  return text;
 }
 return TheGameText->fetch("STRATEGICHUD:RegionBonusNone",0);
}
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

#include "../../../../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../../../../Include/Common/DelegateDesc.h"

#include "../../../../../Include/Common/AptCommandMap.h"

// Build the same four-byte owning delegate through its rowed constructor.
class Rva00579E47
{
public:
 Rva00579E47(const DelegateDesc &);
protected:
 Rva00579E47() {}
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
class Image;
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddCommandMapDelegate(AptCommandMapAdder &adder, const AsciiString &name, DelegateDesc desc)
{
	adder.AddCommandMap(name, &desc);
}


class Rva005242D7 {public:Rva005242D7();~Rva005242D7();private:char bytes[12];};
// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
#include "../../../../../Include/Common/Rva000B3F84Pair.h"

#include "../../../../../Include/Common/AsciiStringRef.h"

#include "../../../../../Include/Common/AsciiStringPlusString.h"

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

inline __declspec(noinline) AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right) {Rva000B3F84Pair text; text.init(right); AsciiStringPlusStringText r;static_cast<AsciiStringPlusString &>(r)=left;r.m_right=text;return r;}

// "APT:" + prefix + name + text: the text-plus-string node is the rowed
// 0x002226E5 (System/RegistryAsciiPath.cpp); the two widening concats are
// emitted out of line here and ICF-folded at 0x005F17C6 and 0x005D2F96
// (pinned, these definitions are the fold proofs); the materializer is the
// pinned 0x005F1D47 (WorldBuilder StringCompose::Concat<...>, three levels).
#include "../../../../../Include/GameClient/Rva002226E5TextPlusString.h"
Rva002226E5TextPlusString __cdecl operator+(const char *left, const AsciiString &right); // 0x002226E5

struct AptTextPlusStringPlusString : Rva002226E5TextPlusString
{
	AsciiStringRef m_third;
};

// The materializer 0x005F1D47 is rowed as the conversion of Rva005F1D06
// (System/Rva00513E03Length.cpp): the text node inherits it from that view.
struct Rva005F1D06 : AptTextPlusStringPlusString
{
	operator AsciiString(); // 0x005F1D47
};

struct AptTextPlusStringPlusStringText : Rva005F1D06
{
	Rva000B3F84Pair m_text;
};

AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right);

AptTextPlusStringPlusStringText operator+(const AptTextPlusStringPlusString &left, const char *right);

class Rva005F1AF5 {public:void rva005F1AF5(const char*);void rva005F1B18(const char*);};
namespace StrategicHUD {class RegionDetailsTerritoryMovieClip {public:class Impl;};}
class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl {
public:Impl(unsigned int level,const AsciiString &name);
 void rva005F1999(int index,int value);
 void rva005F191E(const Image *image);
 __declspec(noinline) void rva005F1A2D();
private:unsigned int level;AsciiString name;
 AptCommandMapAdder commands;Rva005242D7 images;
 UnicodeString title,description;const Image *preview;int bonuses[6];int selectedBonus;
};
void StrategicHUD::RegionDetailsTerritoryMovieClip::Impl::rva005F1999(int index,int value) {
 if(value!=bonuses[index]) {
  AsciiString key;key.format("APT:_level%u.%s_Bonus%d",level,name.str(),index);
  ((BfmeAptWindowManager*)TheRva00222A8BTarget)->bfmeSetText(key,FormatRegionBonus(index,value),false);
  bonuses[index]=value;
 }
}

static __declspec(noinline) UnicodeString RegionBonusTooltip(int kind) {
 return TheGameText->fetch(LookupRegionBonus(kind)->tooltip,0);
}
struct RGBColor;
#include "../../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
void StrategicHUD::RegionDetailsTerritoryMovieClip::Impl::rva005F1A2D() {
 if(selectedBonus>=0 && selectedBonus<6)TheMouse->rva001EEA6D(RegionBonusTooltip(selectedBonus),-1,0,1.0f);
}

StrategicHUD::RegionDetailsTerritoryMovieClip::Impl::Impl(unsigned int l,const AsciiString &asciiString):level(l),name(asciiString) {
 selectedBonus=-1;
 preview=0;
 for(int *p=bonuses;p!=bonuses+6;++p)*p=0;
 AsciiString prefix;prefix.format("_level%u.",level);
 AddCommandMapDelegate(commands, prefix+name+"_OnRollOverBonus",DelegateDesc((Rva005F1AF5*)this,&Rva005F1AF5::rva005F1AF5));
 AddCommandMapDelegate(commands, prefix+name+"_OnRollOutBonus",DelegateDesc((Rva005F1AF5*)this,&Rva005F1AF5::rva005F1B18));
 { UnicodeString blank((const unsigned short*)L" ");
 ((BfmeAptWindowManager*)TheRva00222A8BTarget)->bfmeSetText("APT:"+prefix+name+"_TerritoryName",blank,false); }
 { UnicodeString blank((const unsigned short*)L" ");
 ((BfmeAptWindowManager*)TheRva00222A8BTarget)->bfmeSetText("APT:"+prefix+name+"_TerritoryDescription",blank,false); }
 for(int i=0;i<6;++i) {
  AsciiString key;key.format("APT:_level%u.%s_Bonus%d",level,name.str(),i);
  ((BfmeAptWindowManager*)TheRva00222A8BTarget)->bfmeSetText(key,FormatRegionBonus(i,0),false);
 }
}

// Native5F1B51 loads pointer+4 and tail-jumps to the owned Impl method.
// Original wrapper identity and complete outer extent remain unknown.
struct Rva005F1B51
{
    char unknown0[4];
    StrategicHUD::RegionDetailsTerritoryMovieClip::Impl *implementation;
    void rva005F1B51();
};
void Rva005F1B51::rva005F1B51()
{
    implementation->rva005F1A2D();
}
