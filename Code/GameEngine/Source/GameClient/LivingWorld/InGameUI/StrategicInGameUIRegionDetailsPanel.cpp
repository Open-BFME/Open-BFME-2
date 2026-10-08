// cl: /O1 /DNDEBUG /MD /EHsc
// Retail5CC81F/237 and WB15BF010/936 establish the three page branches.
// Constructor arguments remain opaque pointer-sized ABI values. PageContext
// carries the three copied words; its original type and member names are unknown.
struct PageContext {
 void *word0;void *word4;void *word8;
 PageContext(void *a,void *b,void *c):word0(a),word4(b),word8(c){}
};
// Storage-only caller views: sizes come from retail's allocations. These
// declarations intentionally do not model the constructors' virtual interfaces.
class Rva005CC656 { char storage[20];public:Rva005CC656(void *,void *,void *,const PageContext &); };
class Rva005CC677 { char storage[20];public:Rva005CC677(void *,void *,void *,const PageContext &); };
class Rva005E362F { char storage[16];public:Rva005E362F(void *,void *,void *); };
struct PageRefObjectView { void *vptr;int references; };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct PageRef {
 PageRefObjectView *ptr;
 PageRef(PageRefObjectView *p):ptr(p){if(p)++p->references;}
 PageRef(const PageRef &r):ptr(r.ptr){if(ptr)++ptr->references;}
 ~PageRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);}
};
namespace StrategicInGameUI {class RegionDetailsPanel {public:class Impl;};}
class StrategicInGameUI::RegionDetailsPanel::Impl {
public:PageRef CreatePage(int,void *,void *);
private:char unknown[0x10];void *word10;void *word14;void *word18;void *word1C;
};
PageRef StrategicInGameUI::RegionDetailsPanel::Impl::CreatePage(int kind,void *a,void *b) {
 switch(kind) {
 case 0:return PageRef((PageRefObjectView *)new Rva005E362F(a,b,word10));
 case 1:{PageContext c(word10,word14,word1C);return PageRef((PageRefObjectView *)new Rva005CC656(this,a,b,c));}
 case 2:{PageContext c(word10,word18,word1C);return PageRef((PageRefObjectView *)new Rva005CC677(this,a,b,c));}
 default:return PageRef(0);
 }
}
