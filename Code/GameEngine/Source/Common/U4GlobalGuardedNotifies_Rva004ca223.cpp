// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three bodies from the 0x005E97B0..0x0060D680 slice whose whole content is a
// null test around one call.
//
// 0x006057C0 (51 bytes) -- assignment with a self-check:
//
//     mov eax,[esp+4] / push esi / mov esi,ecx / cmp eax,esi / je OUT
//     mov ecx,[eax+4]  / mov [esi+4], ecx
//     mov edx,[eax+8]  / mov [esi+8], edx
//     mov eax,[eax+0x10] / mov [esi+0x10],eax
//     mov ecx,[<GLOBAL>] / test ecx,ecx / je OUT / push esi / call <A>
//     OUT: mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `mov eax,esi` before `ret 4` returns the receiver, and
// the argument is compared against `this` before anything is copied: that is
// `if (&other != this)` guarding a copy-assignment, and the returned receiver
// is `return *this`.  THE COPIED FIELDS ARE 4, 8 AND 0x10 ONLY -- 0 and 0xC are
// read by nothing and written by nothing, so the operator assigns three of the
// class's members and leaves the others alone.  A compiler-generated assignment
// would copy every member; a `memcpy`-shaped one would not skip a hole.  Both
// jumps land on the same instruction, so the global test is INSIDE the
// self-check, not after it.
//
// 0x00604C00 (22 bytes) -- the same global, a different call:
//
//     mov eax,ecx / mov ecx,[<GLOBAL>] / test ecx,ecx / je OUT
//     add eax,-0xC / push eax / call <B> / OUT: ret
//
// `add eax,-0xC` on `this` with NO null guard around it is a pointer adjustment
// the compiler knows cannot be null -- which `this` never is.  Subtracting is
// base-to-DERIVED, so the receiver is a subobject at offset 0xC of the object
// being handed over.  The two calls take differently adjusted pointers, so they
// are two different entry points, and both are reached through the same global
// dword at 0x012F10D0, which is therefore a pointer and is loaded into ecx --
// a __thiscall receiver -- rather than pushed.
//
// 0x0060C2C0 (21 bytes) -- a free function guarding the receiver itself:
//
//     mov ecx,[esp+4] / test ecx,ecx / je OUT
//     mov eax,[esp+8] / push eax / call <C> / OUT: ret 8
//
// The receiver arrives as an ORDINARY STACK ARGUMENT and is moved into ecx, and
// the function pops its own two dwords: __stdcall wrapping a __thiscall call.
// The null test is on the receiver, so the source tests the pointer it was
// handed before calling through it.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from an address, the
// global's address is a DIR32 operand copied from retail, and the three call
// targets are pinned in targets/game/reverse/symbols.csv by the addresses their REL32s
// resolve to.  The unread fields are spelled `int` because a slot nothing
// touches has no type in evidence.

class U4Owner00604C00;
class U4Assign006057C0;

// The object the global at 0x012F10D0 points at.  Its two entry points are
// 0x00409040 and 0x004090C0.
class U4Notify
{
public:
	void noteAssign( U4Assign006057C0 *a );
	void noteOwner( U4Owner00604C00 *o );
};

extern class Rva00432F23 *g_004C9DC9Container;

// ---------------------------------------------------------------- 0x006057C0

class U4Assign006057C0
{
public:
	U4Assign006057C0 &operator=( const U4Assign006057C0 &other );
	int m_f00;
	int m_f04;
	int m_f08;
	int m_f0C;
	int m_f10;
};

U4Assign006057C0 &U4Assign006057C0::operator=( const U4Assign006057C0 &other )
{
	if ( &other != this )
	{
		m_f04 = other.m_f04;
		m_f08 = other.m_f08;
		m_f10 = other.m_f10;
		if ( (*(U4Notify **)&g_004C9DC9Container) != 0 )
			(*(U4Notify **)&g_004C9DC9Container)->noteAssign( this );
	}
	return *this;
}
