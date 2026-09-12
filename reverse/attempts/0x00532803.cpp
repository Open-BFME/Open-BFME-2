// ?erase@?$vector@W4ParticleSystemID@@V?$allocator@W4ParticleSystemID@@@_STL@@@_STL@@QAEPAW4ParticleSystemID@@PAW43@0@Z
// partial score=0.4 date=2026-09-12
// cl: /O1 /DNDEBUG /MD
//
// _STL::vector<ParticleSystemID, _STL::allocator<ParticleSystemID>>::erase
// (ParticleSystemID*, ParticleSystemID*), retail 0x00532803, 38 bytes. Named
// by Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// (m_particleSystemIDs). Shifts the tail down over the erased range via
// __copy_ptrs and trims _M_finish; ParticleSystemID is a 4-byte enum, so
// this instantiation's COMDAT is byte-identical to the already-matched
// __copy_ptrs<ScienceType const*, ScienceType*> at 0x0025BF40 (pinned in
// reverse/symbols.csv).

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
T2 __copy_ptrs(T1 first, T1 last, T2 result, __false_type);

template <class T>
class allocator {};

template <class T, class Alloc>
struct vector
{
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;

	T *erase(T *first, T *last);
};

template <class T, class Alloc>
T *vector<T, Alloc>::erase(T *first, T *last)
{
	_M_finish = __copy_ptrs<const T *, T *>(last, _M_finish, first, __false_type());
	return first;
}

}

enum ParticleSystemID { PARTICLESYSTEMID_INVALID = 0 };

template struct _STL::vector<ParticleSystemID, _STL::allocator<ParticleSystemID> >;

// STUCK ON: the __copy_ptrs<ParticleSystemID const*, ParticleSystemID*>
// callee's pin (reverse/symbols.csv, address 0x0025BF40, the same COMDAT
// already matched as __copy_ptrs<ScienceType const*, ScienceType*> in
// ThingTemplate.cpp -- verified consistent by tools/pin_consistency.py) is
// NOT included in this stash; add it back before reusing this body.
//
// With that pin, this compiles to 46B against a 38B target (4/38
// positional, exact prefix 3B, unresolved=[]) -- correctly resolved, wrong
// size. Every source shape tried allocates a real 1-byte stack local (`lea
// edi,[ebp-4] / stos byte`) to hold the by-value `_STL::__false_type()`
// tag argument to __copy_ptrs. Retail does not: it takes the tag's address
// as `lea eax,[ebp+0xb]`, one byte INTO the "first" parameter's own 4-byte
// stack slot (ebp+8..ebp+0xb) -- it never allocates fresh stack for the
// empty tag object at all, just reuses a dead byte of an existing
// parameter's storage. Tried: naming src_first/src_last as separate typed
// locals before the call vs inlining everything into one call expression
// with explicit `__copy_ptrs<const T*, T*>(...)` template arguments --
// both produce the same 46B shape with a fresh stack slot for the tag.
// Next step: find what source shape (or optimization flag) makes cl 13.10
// address-reuse an existing parameter slot for an empty-class by-value
// argument instead of allocating one; docs/matching.md or another __false_type
// by-value near-miss elsewhere in reverse/re_attempts.log may already have
// this lesson banked.
