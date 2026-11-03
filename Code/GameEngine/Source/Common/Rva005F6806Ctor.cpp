// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 005F6806..005F686A; owner shares C796D0 with destructor5F64F5.
// Named ArmyDetailsMovieClip80 establishes level/name/layout/back ABI.
class AsciiString;
#include "../../Include/GameClient/ArmyDetailsMovieClip.h"
namespace StrategicHUD {
// The 0x38-byte member at +8 is the hero clip's Impl, rowed at 0x005F654C.
class HeroArmyDetailsMovieClip {
public:
 class Impl {
 public:
  Impl(void *,unsigned int,const AsciiString &);
  virtual ~Impl();
 private: char storage[0x38-4];
 };
};
}
class Rva005F64F5 : public StrategicHUD::ArmyDetailsMovieClip {
public:
 Rva005F64F5(int,const AsciiString &,bool);
 virtual ~Rva005F64F5();
private: StrategicHUD::HeroArmyDetailsMovieClip::Impl *owned8;
};
Rva005F64F5::Rva005F64F5(int level,const AsciiString &name,bool back)
 : StrategicHUD::ArmyDetailsMovieClip(level,name,1,back),
 owned8(new StrategicHUD::HeroArmyDetailsMovieClip::Impl(this,level,name)) {}
