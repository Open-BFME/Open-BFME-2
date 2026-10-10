// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5CE0B8..5CE0DF and 5E73FB..5E744F: destructors of the
// already-recovered constructor owners. Target layout: primary0, vbptr4,
// owned holder8; derived linkC moves the counted virtual base from C to10.
// Existing ctor146 at5E87E0 proves the nonvirtual Rva005CC5E5 parent;
// that parent's57B constructor and native22B destructor fix its two tables.
// Omitting this parent was the old negative-this-offset blocker. The class
// graph lets MSVC emit the native virtual-base destructor ABI directly.
// Derived destruction clears link->owner(+20), then destroys the base.
// Base destruction clears the owning holder through the existing29B worker
// before the parent's inline destructor restores C74E6C/C74E68.
// Layout/ABI are target facts; application identities remain unknown.
class Rva0007DF07 {public: Rva0007DF07():count(0){} virtual ~Rva0007DF07(){} private:unsigned count;};
class Rva005CC5E5 : public virtual Rva0007DF07 {public: Rva005CC5E5() throw(); virtual void slot0(); virtual ~Rva005CC5E5(){};};
class Rva000AD6F4 {public: void clear(); ~Rva000AD6F4(){clear();} private:void *pointer;};
struct Rva005CE172Context;
class Rva005E87E0 : public Rva005CC5E5 {public: Rva005E87E0(void*,void*,Rva005CE172Context*); virtual ~Rva005E87E0(); private:Rva000AD6F4 payload;};
struct Rva005CE172Link {char prefix[0x20];void *owner;};
struct Rva005CE172Context {char prefix[8];Rva005CE172Link *link;};
class Rva005CE172 : public Rva005E87E0 {public:Rva005CE172(void*,void*,Rva005CE172Context*); virtual ~Rva005CE172();private:Rva005CE172Link *context;};
Rva005E87E0::~Rva005E87E0() {}
Rva005CE172::~Rva005CE172() {if(context)context->owner=0;}
