// ?rva0045A57C@AutoAbilityBehavior@@QAE_NXZ
// Native45A57C..45A63F (195B), WB117C610.
// Readiness predicate, original method name remains unknown. Target mask1C,
// Object status94/model10C/AI258 and gate bits independently observed.
// Same-valued data PHI recovers native receiver/mask register allocation.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include /ICode/GameEngine/Source/Common /EHsc
// Reference guide: Open-BFME-1 f98983a7d AutoAbilityBehavior_bfmeCanAutoFire.cpp
// (clean125B predicate). Target0045A57C/WB117C610 adds module-status mask,
// target model/status gates, tri-state eligibility and button exclusion mask.
// Fields below come from native accesses; donor semantics do not establish
// original BFME2 method names.
#include "Lib/Coord3D.h"
#include "ascii_string.h"
namespace _STL { template<unsigned int N> class _Base_bitset {
public: bool _M_is_any() const; unsigned int words[N];
}; }
class Rva00331682Holder { public: bool test(const void*) const; };
class Rva00263546 { public: bool rva00263546(const Rva00263546*) const; };
class AIUpdateInterface { public: char data00[0x34]; void *active; };
class BodyModule { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual float slot14();
};
class CommandButton;
enum ObjectStatusTypes { AutoAbilityStatus74=74 };
class Object {
public:
 bool rva002922D9(const CommandButton*);
 int rva0028F4EF();
 bool testStatus(ObjectStatusTypes) const;
 char data00[0x38]; Coord3D position;
 char data44[0x94-0x44]; unsigned int status[4];
 char dataA4[0x10C-0xA4]; unsigned int model[19];
 char data158[0x254-0x158]; BodyModule *body;
 AIUpdateInterface *ai;
};
class CommandButton {
public:
 bool isReady(const Object*) const;
 char data00[0x134]; float range;
 bool flag138;
 char data139[3]; Rva00263546 exclude;
};
class ControlBar { public: const CommandButton *findCommandButton(const AsciiString&); };
extern ControlBar *TheControlBar;
struct AutoAbilityData {
 char data00[0xC]; float minimumRange;
 char data10[0x1C-0x10]; _STL::_Base_bitset<4> forbiddenStatus;
 char data2C[0x5F-0x2C]; bool allowSelf;
};
class BfmeWideResult;
class AutoAbilityBehavior {
public:
 bool rva0045A57C();
 Object *rva0045A447(BfmeWideResult*,const CommandButton*);
 char data00[4]; const AutoAbilityData *data; Object *object;
 char data0C[0x20-0xC]; AsciiString command;
};
bool AutoAbilityBehavior::rva0045A57C()
{
 const _STL::_Base_bitset<4> &mask=(data?data:data)->forbiddenStatus;
 Object *obj=object;
 if(mask._M_is_any() && ((const Rva00331682Holder*)&mask)->test(obj->status)) return false;
 const CommandButton *button=TheControlBar->findCommandButton(command);
 if(!button->isReady(obj)) return false;
 if(!obj->rva002922D9(button)) return false;
 if((unsigned char)(obj->model[4])&1) return false;
 if((unsigned char)(obj->model[3]>>31)&1) return false;
 if((unsigned char)(obj->model[5]>>3)&1) return false;
 if(!obj->rva0028F4EF()) return false;
 if(((const Rva00263546*)obj->model)->rva00263546(&button->exclude)) return false;
 if(obj->testStatus(AutoAbilityStatus74)) return false;
 AIUpdateInterface *ai=obj->ai;
 if(ai && ai->active) return false;
 return true;
}
