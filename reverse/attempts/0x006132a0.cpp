// ?Return_File@RawFileFactoryClass@@QAEXPAVFileClass@@@Z
// partial score=0.5 date=2026-09-12
// cl: /O1 /DNDEBUG /MD
//
// RawFileFactoryClass::Return_File, retail 0x006132A0, 36 bytes. Named by
// Code/Libraries/Source/WWVegas/WWLib/ini.cpp (two call sites through
// _TheFileFactory/_TheWritingFileFactory). Zero Hour's ffactory.cpp has the
// same one-liner body ("delete file;"); FileClass's virtual destructor
// (vtable slot 0) is called with the deleting flag 0, and the caller then
// calls the plain, non-virtual operator delete directly -- both branches
// (null and non-null) reach that same operator delete call, matching
// `delete` on a polymorphic pointer through a base class with a trivial
// (non-overridden) operator delete.

void operator delete(void *) throw();

class FileClass
{
public:
	virtual void *ScalarDeletingDtor(int flag);
};

class RawFileFactoryClass
{
public:
	void Return_File(FileClass *file);
};

void RawFileFactoryClass::Return_File(FileClass *file)
{
	if (!file)
	{
		operator delete((void *)0);
		return;
	}
	operator delete(file->ScalarDeletingDtor(0));
}

// STUCK ON: cl (this build's wine MSVC 7.1) always merges the null and
// non-null tails into one shared "push <value>; call operator_delete" once
// it can prove both push the same runtime value (0 in the null path, and
// the ScalarDeletingDtor(0) return in the other) -- 24 bytes, 18/36
// positional match, exact prefix 6B. Retail's 36-byte body duplicates the
// tail in full (its own `xor eax,eax / push eax / call operator delete /
// pop ecx / ret 4` block at +0x18), never sharing it with the non-null
// path's `push eax / call operator delete / pop ecx / ret 4` at +0xe.
// Tried and rejected (all land on the same 24B shared-tail shape):
//  - plain `delete file;` (flag=1, single combined vtable call -- 17B, no
//    split at all, /O1 and /O2 both);
//  - `if(file) file->~FileClass(); operator delete(file);` (flag=0 split
//    achieved, but `file` needs an esi spill across the vtable call since
//    an explicit pseudo-destructor call is declared void -- 28B, 0/36
//    because the whole register-allocation shifts from byte 0);
//  - if/else with explicit operator delete in both branches, `operator
//    delete(0)` / `operator delete(file)` / `void *volatile zero=0;
//    operator delete(zero)` (forces an ebp frame instead, 39B) / two early
//    returns instead of if/else -- every non-volatile shape converges on
//    the same 24B merge, and the volatile shape gets a frame pointer
//    instead of retail's esp-relative one.
// Try next: a NOINLINE helper for just the non-null path (so the compiler
// cannot see both call sites at once and CSE the "0"), or building this
// under whatever exact optimization pragma/flag combination stops cl from
// recognizing operator delete's argument is the same runtime value across
// the two paths (this project's docs/matching.md may have a similar
// "prevent merge" lesson already banked from another dead-tail case).
