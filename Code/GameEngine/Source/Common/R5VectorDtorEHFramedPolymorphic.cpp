// cl: /O1 /EHsc
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ??4?$vector@UGen00141A00@@V?$allocator@U 0x002D0F65 (206B),
// vector<Gen003AA0D0>::vector 0x005DE870 (93B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Open-BFME5: fourteen more STLport vector<T> destructors over a POLYMORPHIC
// element -- the shape Q4VectorDtorPolymorphic.cpp already lands six of, at
// the element sizes that are NOT powers of two.
//
// The destroy loop dispatches through the element's own vtable:
//
//     mov eax,[p] / push 0 / mov ecx,p / call [eax]
//
// which is MSVC's scalar deleting destructor with the free flag CLEAR --
// destroy in place, do not release.  Going through the vtable at all is the
// tell: `p->~T()` on a type whose destructor is not virtual compiles to a
// direct call, so the element type has a VIRTUAL DESTRUCTOR owning slot 0.
//
// What separates these six from Q4's is only the element size.  A power of
// two lets the compiler turn the pointer difference into an element count
// with a `sar`/`shl` pair; 92, 140, 180, 88, 220 and 112 do not, so each of
// these carries a magic multiply or a plain shift instead.  Same source, and
// the divide block
// is derived rather than written.
//
// IDENTITY IS NOT RECOVERED.  Element names come from the vector destructor's
// own address, and `char m_pad[SIZE-4]` carries the size past the vptr; it is
// not a claim about the element's fields.

#include <vector>

#define R5_POLY_ELEM( T, SIZE )                                               \
	struct T                                                                  \
	{                                                                         \
		virtual ~T();                                                         \
		char m_pad[ SIZE - 4 ];                                               \
		T();                                                                  \
		T( const T & );                                                       \
		T &operator=( const T & );                                            \
	};

// Only the two placed members are instantiated. The donor instantiated all
// fourteen vector<T> classes, and their other members (pinned elsewhere to
// different retail bodies) came out as private wrong COMDAT copies.
R5_POLY_ELEM( Gen00141A00, 0x5C )		// 168B at 0x00141A00
R5_POLY_ELEM( Gen003AA0D0, 0x18 )		// 167B at 0x003AA0D0

template _STL::vector<Gen00141A00> &
	_STL::vector<Gen00141A00>::operator=( const _STL::vector<Gen00141A00> & );
template _STL::vector<Gen003AA0D0>::vector( _STL::vector<Gen003AA0D0>::size_type );
