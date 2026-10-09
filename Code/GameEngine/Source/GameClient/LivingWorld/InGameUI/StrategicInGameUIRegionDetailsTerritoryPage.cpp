// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5E38EB..5E3947 complete92B and WB15F6AA0. Owner from
// admitted dtor5E362F and vtableC77BD0; Impl allocation16B from direct native call5E3753.
#include "ascii_string.h"
struct RvaSmallVtableZeroBase {void *m_04;};
class Rva0007DF07:public RvaSmallVtableZeroBase {public:virtual ~Rva0007DF07(){}};
class Rva005EEE5A:public Rva0007DF07 {public:Rva005EEE5A();bool active;};
namespace StrategicInGameUI {class RegionDetailsTerritoryPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsTerritoryPage::Impl {public:Impl(unsigned,const AsciiString&,void*);private:char storage[0x10];};
class Rva005E362F:public Rva005EEE5A {public:Rva005E362F(void*,void*,void*);virtual ~Rva005E362F();private:StrategicInGameUI::RegionDetailsTerritoryPage::Impl *impl;};
Rva005E362F::Rva005E362F(void *level,void *name,void *region):impl(new StrategicInGameUI::RegionDetailsTerritoryPage::Impl((unsigned)level,*(const AsciiString*)name,region)){}
