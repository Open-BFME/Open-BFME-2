// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
class CreateAHeroData;
class Rva002B7250 {public:void rva002B7250(CreateAHeroData *);};
struct Rva005E5FObserverOwner {char prefix[8];Rva002B7250 observers;};
class Rva005E5FObserver {public:virtual void notify();~Rva005E5FObserver() {}};
class Rva0042D69DPtrChaseField {public:int get() const;};
class Rva0042D6FDPtrChaseField {public:int get() const;};
class Rva0042D703PtrChaseField {public:int get() const;};
class Rva00319B0AOwner {public:void rva00319B31();};
class Rva005E5FButtons {public:virtual void s0();virtual void s1();virtual void erase(int);};
class Rva005E5FPanel {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void close();};
class Rva005E5FDetails {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void clear();};
class Rva005F23B2 {public:~Rva005F23B2();char storage[24];};
class Rva000AD6F4 {public:void clear();char storage[8];};
struct Rva005E5FOwnedSlot {Rva000AD6F4 holder;~Rva005E5FOwnedSlot(){holder.clear();}};
class Rva005E5FFB :public Rva005E5FObserver {public:
 ~Rva005E5FFB();
 char prefix4[12];void *owner10;int word14;Rva005E5FObserverOwner *owner18;
 Rva005F23B2 child1C;int word34;Rva005E5FOwnedSlot owned38,owned40;
};
Rva005E5FFB::~Rva005E5FFB() {
 Rva005E5FButtons *buttons=reinterpret_cast<Rva005E5FButtons*>(reinterpret_cast<Rva0042D69DPtrChaseField*>(owner10)->get());
 if(buttons){buttons->erase(5);buttons->erase(2);buttons->erase(1);}
 Rva005E5FPanel *panel=reinterpret_cast<Rva005E5FPanel*>(reinterpret_cast<Rva0042D6FDPtrChaseField*>(owner10)->get());
 if(panel)panel->close();
 Rva005E5FDetails *details=reinterpret_cast<Rva005E5FDetails*>(reinterpret_cast<Rva0042D703PtrChaseField*>(owner10)->get());
 if(details)details->clear();
 reinterpret_cast<Rva00319B0AOwner*>(owner18)->rva00319B31();
 owner18->observers.rva002B7250(reinterpret_cast<CreateAHeroData*>(this));
}

// Native5E5FFB..5E60B5,186B. WB15FE930 corroborates three button
// removals, two guarded panel calls, owner notification/unregister and
// reverse destruction of members40/38/1C, followed by listener restore.
// The24B child size comes from its existing5F23B2 provider; word34 is
// opaque. All owner/member/interface names remain target-neutral.
// ?Rva005E5FFBDeleteAnchor absent-from-retail
void Rva005E5FFBDeleteAnchor(Rva005E5FFB *value){delete value;}
