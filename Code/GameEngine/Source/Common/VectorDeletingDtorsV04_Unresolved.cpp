// cl: /O1 /DNDEBUG /MD /EHsc
//
// Owners whose complete destructors remain unresolved are kept apart from
// the independently linkable wrappers in VectorDeletingDtorsV04.cpp.
//
// Vector deleting destructors (??_E), batch V04: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot   owner (FXParticleSystem::)
//   0x003A9A40  0x003AA0C0  0x24  0x00C1C198#0  LifeEventModuleTemplate
//   0x003A9CF8  0x003A9C39  0x48  0x00C1C1C8#0  RenderObjectDrawModuleTemplate
//   0x003A9F3F  0x003A9E80  0x1C  0x00C1C1F8#0  GpuDrawModuleTemplate
//   0x003AA17F  0x003AA0C0  0x28  0x00C1C228#0  TerrainCollisionModuleTemplate
//
// The owners are abstract (two __purecall slots each). Retail exports them
// (reverse/exports.csv), and dllexport is what put ??_E in their vtables: cl 7.1
// emits no ??_E for an abstract class otherwise, and under dllexport only together
// with the vtables, which the eight *ModuleTemplateCtorThunk/CopyCtor units also
// emit. Taking the real names means moving all of those units to exported views.

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class __declspec(novtable) Rva003AA0C0Base0
{
public:
	virtual ~Rva003AA0C0Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC, proven by the this-adjusting thunk (sub ecx,
// 0xC) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003AA0C0BaseC
{
public:
	virtual ~Rva003AA0C0BaseC();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

class Rva003AA0C0 : public Rva003AA0C0Base0, public Rva003AA0C0BaseC
{
public:
	virtual ~Rva003AA0C0();
};

class __declspec(novtable) Rva003A9C39Base0
{
public:
	virtual ~Rva003A9C39Base0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A9C39Base8
{
public:
	virtual ~Rva003A9C39Base8();
private:
	char m_unmodelled_04[0x40 - 0x04];
};

class Rva003A9C39 : public Rva003A9C39Base0, public Rva003A9C39Base8
{
public:
	virtual ~Rva003A9C39();
};

class __declspec(novtable) Rva003A9E80Base0
{
public:
	virtual ~Rva003A9E80Base0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A9E80Base8
{
public:
	virtual ~Rva003A9E80Base8();
private:
	char m_unmodelled_04[0x14 - 0x04];
};

class Rva003A9E80 : public Rva003A9E80Base0, public Rva003A9E80Base8
{
public:
	virtual ~Rva003A9E80();
};

class __declspec(novtable) Rva003AA17FVecBase0
{
public:
	virtual ~Rva003AA17FVecBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC, proven by the this-adjusting thunk (sub ecx,
// 0xC) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003AA17FVecBaseC
{
public:
	virtual ~Rva003AA17FVecBaseC();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003AA17FVec : public Rva003AA17FVecBase0, public Rva003AA17FVecBaseC
{
public:
	virtual ~Rva003AA17FVec();
};

// ?<bfmeVectorDeleteAnchorV04Unresolved> absent-from-retail
void bfmeVectorDeleteAnchorV04Unresolved()
{
	new Rva003AA0C0[2];
	new Rva003A9C39[2];
	new Rva003A9E80[2];
	new Rva003AA17FVec[2];
}
