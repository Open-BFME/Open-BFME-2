// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5E1928..5E197E complete86B: replace help at1C from army14,
// then install that handle on owner10->8. Original class identity unresolved.
struct TargetRef00217D4C {void *vtable;int count;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct RvaF6Ret {
 TargetRef00217D4C *ptr;
 ~RvaF6Ret(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
RvaF6Ret Helper0056BABF(int);
struct TreeHintRef00217D4C {
 TargetRef00217D4C *ptr;
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
};
class Rva003FE20FBase {public:virtual void slot1(void *);};
struct Rva005E1928Owner {char unknown00[8];Rva003FE20FBase *target;};
class Rva005E1928 {public:void rva005E1928();private:
 char unknown00[0x10];Rva005E1928Owner *owner;int army;char unknown18[4];TreeHintRef00217D4C help;
};
void Rva005E1928::rva005E1928(){
 help=(const TreeHintRef00217D4C&)Helper0056BABF(army);
 owner->target->Rva003FE20FBase::slot1(&help);
}
