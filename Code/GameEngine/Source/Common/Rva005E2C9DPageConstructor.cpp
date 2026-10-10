// cl: /O1 /G7 /MD /EHsc
// ??0Rva005E21EB@@QAE@PAX0ABUPageContext@@@Z @0x005E2C9D 93B (the pin
// spelling; ret 0xC). Twin of Rva005E20A6PageConstructor.cpp for the
// structures page: native 5E2C9D..5E2CFA runs the Rva005EEE5A base ctor, stores
// vftable 0x00C77AB8 (class Rva005E21EB, scalar deleting dtor 0x005E25B1) and
// news the 0x30-byte page Impl (ctor 0x005E2B45, called with this, the two
// pointer arguments and the PageContext reference), keeping the result at +0xC.
// The Impl ctor is the callee the sibling's allocation flow names; its ledger
// spelling comes from the page's slot methods (RegionDetailsStructuresPage).
struct RvaSmallVtableZeroBase {void *m_04;};
class Rva0007DF07:public RvaSmallVtableZeroBase {public:virtual ~Rva0007DF07(){}};
class Rva005EEE5A:public Rva0007DF07 {public:Rva005EEE5A();bool active;};
struct PageContext {void *region,*page,*owner;};
namespace StrategicInGameUI {class RegionDetailsStructuresPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsStructuresPage::Impl {public:Impl(void*,void*,void*,const PageContext&);private:char storage[0x30];};
class Rva005E21EB:public Rva005EEE5A {public:Rva005E21EB(void*,void*,const PageContext&);virtual ~Rva005E21EB();private:StrategicInGameUI::RegionDetailsStructuresPage::Impl *impl;};
Rva005E21EB::Rva005E21EB(void *level,void *name,const PageContext& context):impl(new StrategicInGameUI::RegionDetailsStructuresPage::Impl(this,level,name,context)){}
