// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native5CF937..5CF9AA115B. WB15B7670 gives the ctor callgraph.
// Existing destructor5CFDA6 and scalar5CFD8A independently identify the
// receiver. Retail C752C4 has2 primary slots and C752B0 has5 secondary
// slots; primary C75290 has2. The bases are at0/8, not a member-only view.
// The existing83B Rva5E9F3F ctor takes provider then battle. Native pushes
// owner+14 as battle and incoming argC as provider, followed by3 opaque
// inputs. The owned171B implementation supplies the battle/provider roles.
// Owner+C feeds the existing6B pointer-chase getter before the exact5B
// direct virtual-forwarding body; WB labels this ChecklistUI::FadeOut.
// Original state/class names and unused virtual prototypes remain unknown.
class Rva0057C394;class LivingWorldBattle;
class Rva0042D697PtrChaseField{public:int get()const;};
class Rva005CC208{public:virtual void rva005CC208();};
struct Rva005CF937Owner{char pad[12];void*ui;char pad10[4];LivingWorldBattle*battle;};
class Rva005CF872 {public:Rva005CF872(Rva005CF937Owner*o):owner(o){}virtual~Rva005CF872(){}virtual void slot1();Rva005CF937Owner*owner;};
class Rva005E9F3F {public:Rva005E9F3F(Rva0057C394*,LivingWorldBattle*,void*,void*,void*);virtual~Rva005E9F3F();virtual void event1();virtual void event2();virtual void event3();virtual void event4();void*impl;};
class Rva005CFDA6:public Rva005CF872,public Rva005E9F3F{public:Rva005CFDA6(Rva005CF937Owner*,Rva0057C394*,void*,void*,void*);virtual~Rva005CFDA6();virtual void slot1();virtual void event1();virtual void event2();virtual void event3();virtual void event4();};
Rva005CFDA6::Rva005CFDA6(Rva005CF937Owner*o,Rva0057C394*p,void*a,void*c,void*d):Rva005CF872(o),Rva005E9F3F(p,o->battle,a,c,d){
 Rva005CC208*ui=(Rva005CC208*)((Rva0042D697PtrChaseField*)owner->ui)->get();if(ui)ui->Rva005CC208::rva005CC208();
}
