// cl: /O1 /DNDEBUG /MD
//
// ??_GAIUpdateInterface@@MAEPAXI@Z, retail 0x0026ED95 (28 bytes): slot 0 of
// vtable 0x00BFA480. Scalar deleting destructor: calls the destructor at
// 0x0026E836 and then the global operator delete when bit 0 of the flags is
// set. That destructor re-stores vtable 0x00BFA480 at +0 (and the interface
// tables at +0x0C, +0x10, +0x20, +0x24), the table AIUpdateInterface's
// constructor 0x0026E9BD installs, which identifies it as
// AIUpdateInterface::~AIUpdateInterface (pinned in reverse/symbols.csv).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual destructor
// and an inline class operator delete); BFME 2's form frees through the
// global operator delete, so the class is modelled with none, as
// DozerAIUpdateDeleter.cpp does. The destructor is declared, not defined, so
// the call resolves to the pin; the dummy tag constructor (no retail
// counterpart) only makes this TU emit the vtable and with it the deleting
// destructor.

struct EmitVtableTag;

class AIUpdateInterface
{
public:
	AIUpdateInterface(EmitVtableTag *);
protected:
	virtual ~AIUpdateInterface();
};

// ?<AIUpdateInterface::AIUpdateInterface> absent-from-retail
AIUpdateInterface::AIUpdateInterface(EmitVtableTag *)
{
}
