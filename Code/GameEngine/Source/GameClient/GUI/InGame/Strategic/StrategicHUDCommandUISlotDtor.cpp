// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// The array at005D2BD4 is six1C-byte slots: its EH iterator pushes
// ctor005D2575 and dtor005D258E. Native005D258E..005D25F2 is100B,
// bounded by its RET at005D25F1 and the separately owned outer destructor.
// The target releases refs+10/+C then clears holders+8/+4/+0; +14/+18
// are trivial words. The zeroing constructor's address-qualified name is
// retained; its other uses do not establish the slot's original type name.
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva000AD6F4 {public:void clear();char data[4];};
class Rva00528FE6 {public:void rva00529009();char data[4];};
struct ButtonFrameRef {Rva000AD6F4 handle;~ButtonFrameRef(){handle.clear();}};
struct FlashRef {Rva00528FE6 handle;~FlashRef(){handle.rva00529009();}};
struct CountedSlotRef {TargetRef00217D4C*ptr;~CountedSlotRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
class Rva005D2575 {public:Rva005D2575();~Rva005D2575();private:ButtonFrameRef button,submenu;FlashRef flash;CountedSlotRef callback,timer;unsigned unknown14,unknown18;};
Rva005D2575::~Rva005D2575(){}
