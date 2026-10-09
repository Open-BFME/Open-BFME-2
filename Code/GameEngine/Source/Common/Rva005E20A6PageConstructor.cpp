// cl: /O1 /G7 /MD /EHsc
// Native5E20A6..5E2103 complete93B and WB15F13C0; class from
// admitted dtor5E1FBC/vtableC77A64, Impl allocation44B and WB15F0740.
struct RvaSmallVtableZeroBase {void *m_04;};
class Rva0007DF07:public RvaSmallVtableZeroBase {public:virtual ~Rva0007DF07(){}};
class Rva005EEE5A:public Rva0007DF07 {public:Rva005EEE5A();bool active;};
struct PageContext {void *region,*page,*owner;};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:Impl(void*,void*,void*,const PageContext&);private:char storage[0x2C];};
class Rva005E1FBC:public Rva005EEE5A {public:Rva005E1FBC(void*,void*,const PageContext&);virtual ~Rva005E1FBC();private:StrategicInGameUI::RegionDetailsArmiesPage::Impl *impl;};
Rva005E1FBC::Rva005E1FBC(void *level,void *name,const PageContext& context):impl(new StrategicInGameUI::RegionDetailsArmiesPage::Impl(this,level,name,context)){}
