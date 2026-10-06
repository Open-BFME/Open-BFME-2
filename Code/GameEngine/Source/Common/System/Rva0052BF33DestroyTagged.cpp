// cl: /DNDEBUG /MD /GX-
// ?Rva0052BF33DestroyTagged@@YAXPAURva0052BF33Elem@@0ABU__false_type@_STL@@@Z
// @0x0052BF33 26B. Unlock lane: destroys range through each 8-byte element's
// virtual dtor (scalar-deleting slot with zero flag); caller 0x005A6EDA is the
// tag-dispatch DestroyRange. Same shape as Rva0052BF81_DestroyTagged in
// LivingWorldRegionConnectionHelpers.cpp but stride 8. Next is that TU.
extern "C" void free(void *block);
namespace _STL
{
struct __false_type
{
};
}

struct Rva0052BF33Elem
{
	virtual ~Rva0052BF33Elem();
	char m_pad[4];
};

void Rva0052BF33DestroyTagged(Rva0052BF33Elem *first, Rva0052BF33Elem *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~Rva0052BF33Elem();
}

// ?Rva0052BF4DDestroyTagged@@YAXPAURva0052BF4DElem@@0ABU__false_type@_STL@@@Z
// @0x0052BF4D 26B. Unlock lane: same tagged virtual loop as 0x0052BF33 above
// but stride 0x28; caller at 0x0052C274; unblocks 0x0052C266.
struct Rva0052BF4DElem
{
	virtual ~Rva0052BF4DElem();
	char m_pad[36];
};

void Rva0052BF4DDestroyTagged(Rva0052BF4DElem *first, Rva0052BF4DElem *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~Rva0052BF4DElem();
}

// ?Rva0052BF67DestroyTagged@@YAXPAURva0052BF67Elem@@0ABU__false_type@_STL@@@Z
// @0x0052BF67 26B. Unlock lane: same tagged virtual loop as above but stride
// 0x20; caller at 0x0052C3CD; unblocks 0x0052C3BF.
struct Rva0052BF67Elem
{
	virtual ~Rva0052BF67Elem();
	char m_pad[28];
};

void Rva0052BF67DestroyTagged(Rva0052BF67Elem *first, Rva0052BF67Elem *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~Rva0052BF67Elem();
}

// ?Rva0052BF9BDestroyTagged@@YAXPAURva0052BF9BElem@@0ABU__false_type@_STL@@@Z
// @0x0052BF9B 26B. Unlock lane: same tagged virtual loop as above but stride
// 0x14; caller at 0x0022C8F1; unblocks 0x0022C8E3.
struct Rva0052BF9BElem
{
	virtual ~Rva0052BF9BElem();
	char m_pad[16];
};

void Rva0052BF9BDestroyTagged(Rva0052BF9BElem *first, Rva0052BF9BElem *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~Rva0052BF9BElem();
}

// ?Rva0052BFB5DestroyTagged@@YAXPAURva0052BFB5Elem@@0ABU__false_type@_STL@@@Z
// @0x0052BFB5 26B. Unlock lane: same tagged virtual loop as above but stride
// 0x0C; caller at 0x0052C388; unblocks 0x0052C37A.
struct Rva0052BFB5Elem
{
	virtual ~Rva0052BFB5Elem();
	char m_pad[8];
};

void Rva0052BFB5DestroyTagged(Rva0052BFB5Elem *first, Rva0052BFB5Elem *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~Rva0052BFB5Elem();
}

// ?Rva0052BCE7DestroyTagged@@YAXPAURva0052BCE7Elem@@0ABU__false_type@_STL@@@Z
// @0x0052BCE7 29B (push 0 form is 29B vs 26B above due to disp32 for 0xB8).
// Unlock lane: same tagged virtual loop as above but stride 0xB8; caller at
// 0x0052C25C; unblocks 0x0052C24E. Prev/next are stlport TUs.
struct Rva0052BCE7Elem
{
	virtual ~Rva0052BCE7Elem();
	char m_pad[180];
};

void Rva0052BCE7DestroyTagged(Rva0052BCE7Elem *first, Rva0052BCE7Elem *last, const _STL::__false_type &tag)
{
	for (; first != last; ++first)
		first->~Rva0052BCE7Elem();
}

// ?Rva005A6EDADestroyRange@@YAXPAURva0052BF33Elem@@0@Z retail 0x005A6EDA 24B.
// Chain lane: calls this TU's 0x0052BF33 with tag temp; callers include
// 0x001501E4/0x0052CB40/0x005659D2.
void Rva005A6EDADestroyRange(Rva0052BF33Elem *first, Rva0052BF33Elem *last)
{
	_STL::__false_type tag;
	Rva0052BF33DestroyTagged(first, last, tag);
}

// ?Rva0052C37ADestroyRange@@YAXPAURva0052BFB5Elem@@0@Z retail 0x0052C37A 24B.
// Chain lane: calls this TU's 0x0052BFB5 with tag temp; 6 callers including
// 0x004EE51B/0x0052CC3F/0x005659B6.
void Rva0052C37ADestroyRange(Rva0052BFB5Elem *first, Rva0052BFB5Elem *last)
{
	_STL::__false_type tag;
	Rva0052BFB5DestroyTagged(first, last, tag);
}

// ?Rva0052C24EDestroyRange@@YAXPAURva0052BCE7Elem@@0@Z retail 0x0052C24E 24B.
// Chain lane: calls this TU's 0x0052BCE7 with tag temp; callers at
// 0x0052CA47/0x0052CAB3.
void Rva0052C24EDestroyRange(Rva0052BCE7Elem *first, Rva0052BCE7Elem *last)
{
	_STL::__false_type tag;
	Rva0052BCE7DestroyTagged(first, last, tag);
}

// ?Rva0052C266DestroyRange@@YAXPAURva0052BF4DElem@@0@Z retail 0x0052C266 24B.
// Chain lane: calls this TU's 0x0052BF4D with tag temp; callers at
// 0x0052CA86/0x005659F0.
void Rva0052C266DestroyRange(Rva0052BF4DElem *first, Rva0052BF4DElem *last)
{
	_STL::__false_type tag;
	Rva0052BF4DDestroyTagged(first, last, tag);
}

// ?Rva0052C3BFDestroyRange@@YAXPAURva0052BF67Elem@@0@Z retail 0x0052C3BF 24B.
// Chain lane: calls this TU's 0x0052BF67 with tag temp; 3 callers including
// 0x0052CD1D/0x0056591D.
void Rva0052C3BFDestroyRange(Rva0052BF67Elem *first, Rva0052BF67Elem *last)
{
	_STL::__false_type tag;
	Rva0052BF67DestroyTagged(first, last, tag);
}

// ?rva0052CAAB@Rva0052CAABVec@@QAEXXZ retail 0x0052CAAB 30B. Chain lane: calls
// this TU's 0x0052C24E then frees storage via pinned C++ free; caller at
// 0x0052D7E0.
struct Rva0052CAABVec
{
	void rva0052CAAB();
	Rva0052BCE7Elem *m_start;
	Rva0052BCE7Elem *m_finish;
};
void Rva0052CAABVec::rva0052CAAB()
{
	Rva0052C24EDestroyRange(m_start, m_finish);
	Rva0052BCE7Elem *start = m_start;
	if (start != 0)
		free(start);
}

// ?Rva0022C8E3DestroyRange@@YAXPAURva0052BF9BElem@@0@Z retail 0x0022C8E3 24B.
// Unlock lane: calls this TU's 0x0052BF9B with tag temp; unblocks 10 (5
// ready); 10 callers including 0x0022CADE/0x00565950.
void Rva0022C8E3DestroyRange(Rva0052BF9BElem *first, Rva0052BF9BElem *last)
{
	_STL::__false_type tag;
	Rva0052BF9BDestroyTagged(first, last, tag);
}
