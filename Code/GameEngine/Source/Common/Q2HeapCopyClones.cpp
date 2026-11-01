// cl: /EHs-c-
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Q2HeapCopyClones.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva003ADC4F::clone 0x003ADC32 (29B), Rva003AE0AF::clone 0x003AE092 (29B).
// Callee addresses are read off retail's call sites (reverse/symbols.csv).
// Only the placed bodies are carried; the donor's other definitions are
// omitted.
// Two __thiscall const members that heap-allocate a copy of the
// receiver and return the pointer:
//
//   push esi / push <SIZE> / mov esi,ecx
//   call ??2@YAPAXI@Z / add esp,4
//   test eax,eax / je null
//   push esi / mov ecx,eax / call <COPY CTOR> / pop esi / ret
//  null:
//   xor eax,eax / pop esi / ret
//
// WHAT THE BYTES SHOW.  This is MSVC's whole `new T(expr)` sequence and not a
// hand-written allocate-then-initialise: the size is a literal push, the
// allocator is the global `operator new` body the ledger already carries at
// 0x00881F30, the `add esp,4` is the __cdecl cleanup, and the `test/je` that
// skips the constructor on a null return with `xor eax,eax` is the guard MSVC
// interposes for a class type -- source code cannot produce that arm without
// writing the check itself, and then the null arm would not re-materialise
// eax.  `mov esi,ecx` before the allocation and `push esi` as the single
// __thiscall stack argument make the constructor a COPY constructor taking the
// receiver by reference; there is no other argument.
//
// Each clone calls the copy constructor immediately after its native body.
// That is what ties each clone to the existing constructor owner:
// the pairing is read off the REL32, not assumed.
//
// TWO AXES: the pushed size (sizeof(T), which is all these bodies say about
// the class) and the copy-constructor target.  23 of the 31 bytes are
// concrete; the two displacements are resolved from the ledger and the pins.
//
// WHAT THE BYTES DO NOT DECIDE.  Nothing here shows a single member of the
// class -- only its size -- so the layout is one opaque char array.  The
// return type is spelled as the class's own pointer because `new T` yields
// one, but a base-class return would encode identically.  Whether the copy
// constructor is user-written or implicit is not visible either; it is
// declared and left undefined so that the call is the only thing asserted.
// The TU is built with exception handling OFF, which retail's bytes require:
// with /EHs the same source gets a 93-byte body wrapped in an unwind frame.
//
// Original identities remain unknown; class owners follow native copy calls.

#include "../../Include/Common/BfmeAccessorMacros.h"

Q2_HEAP_COPY_CLONE( Rva003ADC4F, 0x5C )
Q2_HEAP_COPY_CLONE( Rva003AE0AF, 0x20 )
