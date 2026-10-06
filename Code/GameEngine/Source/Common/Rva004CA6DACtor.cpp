// ??0AnimationSoundTree@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc
// Pinned ctor for AnimationSoundTree, retail 0x004CA6DA, 25 bytes.
// The header init is done by the rowed ?rva004CA13D@AnimationSoundTree (0x004CA13D),
// which takes two unused dummy addresses; retail materialises a separate one-byte
// local for each argument, so the body pushes two distinct `lea` forms.
// The slot, not the expression, is what distinguishes them: retail recomputes
// the SAME address twice (`lea eax,[ebp-1]` / push / `lea eax,[ebp-1]` / push).
//
// Reaching that shape needs two levers that pull in opposite directions. Passing
// one local twice lets cl 7.1 CSE the two addresses into a single lea + two pushes
// (22 bytes); passing two distinct locals keeps both leas but places the second
// one byte lower, because two live one-byte locals always occupy adjacent slots
// (ebp-1 then ebp-2). Unions, references, array/pointer aliasing and +0 pointer
// arithmetic all fold back to the one-lea form.
//
// Giving the two dummies DISJOINT SCOPES resolves both: each is a separate local
// object, so cl keeps both leas, but the first is dead when the second is declared,
// so the stack slot is reused and both addresses are [ebp-1]. Verified 25 bytes,
// exact match, in an isolated scratch TU.
// Evidence: sole caller 0x004CA72B in
// Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehaviorModuleDataCtor.cpp;
// prev 0x004CA653 dtor and the 0x004CA13D header-init body share this // cl: line.

namespace _STL
{
template <class _Tp> class allocator
{
public:
	static _Tp *allocate(unsigned int __n, void const *__hint);
};
}

class AnimationSoundTreeHeaderHandle
{
public:
	void *m_header;
};

class AnimationSoundTree
{
public:
	AnimationSoundTree();

private:
	AnimationSoundTreeHeaderHandle m_handle;
	unsigned int m_count;

public:
	AnimationSoundTree *rva004CA13D(void const *d1, void const *d2) throw();
};

AnimationSoundTree::AnimationSoundTree()
{
	void const *first;
	{
		char firstDummy;
		first = &firstDummy;
	}
	{
		char secondDummy;
		rva004CA13D(first, &secondDummy);
	}
}