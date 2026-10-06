// cl: /DNDEBUG /MD
//
// Ported from Open-BFME-1's game/GameEngine/Source/Common/Rva0089CompactHelpers.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) by tools/bfme1_sweep.py:
// 8 bodies byte-identical between lotrbfme.exe and game.dat once relocation
// slots are set aside, tier T1 "clean transfer", cl: /DNDEBUG /MD /O2.
//
// The donor was held at copy-tier S -- it defines 21 functions and the sweep
// placed only 8, so find_declared_unmatched refused the whole file. This TU
// carries the 7 that are both placed and cleanly named:
//
//   0x006D1420  36B  Rva00896360Handle::Rva00896360Handle(const&, int)
//   0x006CFEB0  20B  Rva00894F00Pair::Rva00894F00Pair(const int*, int)
//   0x006CFE80  19B  Rva00894E80Ref::Rva00894E80Ref(const&)
//   0x006CD560  18B  Rva00892620NotEqual(const int*, int)
//   0x006CFED0  18B  Rva00894F60Equal(const int*, int)
//   0x006CFE60  17B  Rva00894E60Ref::Rva00894E60Ref(int*)
//   0x0003CD10  17B  Rva0088D990Owner::set(Rva0088D990Inner*)
//
// The donor's eighth placement (0x0003CCE0, 17B) is carried here too, but NOT
// under the donor's name. lotrbfme.exe folded that 17B body across eight BFME1
// addresses, so `Rva0088D960Owner::set` is the sweep's pick among nine twins
// and AGENTS.md forbids spending a guessed name on a folded address. The BYTES
// are not in doubt: the sweep placed them uniquely here, and the retail body is
// complete -- 0x0003CCE0 + 17 = 0x0003CCF1 is int3 padding before the next
// 16-aligned entry at 0x0003CD00, and the body is a whole `ret 4` function:
//
//   mov eax, ecx / mov ecx, [esp+4] / mov edx, [ecx] /
//   mov dword ptr [eax+0x9F50], edx / ret 4
//
// so the row lands under an address-derived name: it asserts the bytes and no
// identity. Same pad-then-member shape as its sibling above, with the pad set
// to retail's own store offset.
//
// No reverse/symbols.csv pin is needed -- every one of these bodies is
// self-contained and reaches no global and no callee.

bool Rva00892620NotEqual(const int *value, int other)
{
	return *value != other;
}

bool Rva00894F60Equal(const int *value, int other)
{
	return *value == other;
}

struct Rva00894E60Ref
{
	int *m_pointer;
	Rva00894E60Ref(int *pointer);
};
Rva00894E60Ref::Rva00894E60Ref(int *pointer) : m_pointer(pointer)
{
	if (pointer) ++*pointer;
}

struct Rva00894E80Ref
{
	int *m_pointer;
	Rva00894E80Ref(const Rva00894E80Ref &other);
};
Rva00894E80Ref::Rva00894E80Ref(const Rva00894E80Ref &other) : m_pointer(other.m_pointer)
{
	if (m_pointer) ++*m_pointer;
}

struct Rva00894F00Pair
{
	int m_pointer;
	int m_extra;
	Rva00894F00Pair(const int *pointer, int extra);
};
Rva00894F00Pair::Rva00894F00Pair(const int *pointer, int extra) : m_pointer(*pointer), m_extra(extra) {}

struct Rva00896360Handle
{
	int *m_pointer;
	int m_extra;
	Rva00896360Handle(const Rva00896360Handle &other, int extra);
};
Rva00896360Handle::Rva00896360Handle(const Rva00896360Handle &other, int extra)
{
	m_pointer = other.m_pointer;
	if (m_pointer) {
		++*m_pointer;
		m_extra = extra;
		return;
	}
	m_extra = extra;
}

struct Rva0088D990Inner
{
	unsigned char m_value;
};
class Rva0088D990Owner
{
public:
	Rva0088D990Owner *set( Rva0088D990Inner *src );

private:
	char m_pad[0x9F54];
	unsigned char m_copy;
};
Rva0088D990Owner *Rva0088D990Owner::set( Rva0088D990Inner *src )
{
	m_copy = src->m_value;
	return this;
}

struct Rva0003CCE0Inner
{
	int m_value;
};
class Rva0003CCE0Owner
{
public:
	Rva0003CCE0Owner *set( Rva0003CCE0Inner *src );

private:
	char m_pad[0x9F50];
	int m_copy;
};
// ?set@Rva0003CCE0Owner@@QAEPAV1@PAURva0003CCE0Inner@@@Z
Rva0003CCE0Owner *Rva0003CCE0Owner::set( Rva0003CCE0Inner *src )
{
	m_copy = src->m_value;
	return this;
}
