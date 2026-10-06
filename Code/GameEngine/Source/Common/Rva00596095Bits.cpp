// cl: /DNDEBUG /MD
// ?Rva00596095Get@@YGHPAX@Z, retail 0x00596095, 44 bytes.
// Bit-test predicate returning Int: loads inner pointer at arg+4, requires
// byte at inner+0x10E &0x40 ==0, byte at inner+0x108 &0x80 ==0, byte at
// inner+0x11F &0x80 !=0, in that order for the byte-exact test chain.
// Returns 1 via xor+inc else 0 (__stdcall gives ret 4 with single ret via jmp).
// Callers (2 at 0x005960C5 etc.) pass a holder; unblocks 2 with 1 ready.
// Prev is deleting dtor, next is derived ctor; /O1 gives xor+inc and and/or idioms.
typedef int Int;
Int __stdcall Rva00596095Get(void *arg)
{
	void *inner = *(void **)((char *)arg + 4);
	if ((((unsigned char *)inner)[0x10E] & 0x40) == 0 &&
		(((unsigned char *)inner)[0x108] & 0x80) == 0 &&
		(((unsigned char *)inner)[0x11F] & 0x80) != 0)
	{
		return 1;
	}
	return 0;
}
// ?Rva005960FFGet@@YGHPAX@Z @0x005960FF 76B
// Bit-test predicate returning Int: loads inner at arg+4, checks 0x10E&0x40==0,
// 0x108 low byte &0x84==0, 0x11F&0x80==0, then 0x108&8!=0 or 0x113&4!=0 gives 1,
// else needs 0x109&0x40!=0 and rva004884B7(arg)==false for 1, else 0.
// Evidence: mov edx[esp+4] mov eax[edx+4] test chain plus call 0x4884B7; callers
// at 0x00596156 and 0x00596302 pass holder; __stdcall ret 4 with xor+inc.
class Object;
bool __cdecl rva004884B7(Object *obj);
Int __stdcall Rva005960FFGet(void *arg)
{
	void *inner = *(void **)((char *)arg + 4);
	if ((((unsigned char *)inner)[0x10E] & 0x40) == 0)
	{
		unsigned int flags = *(unsigned int *)((char *)inner + 0x108);
		if (((flags & 0x84) == 0) &&
			((((unsigned char *)inner)[0x11F] & 0x80) == 0) &&
			(((flags & 8) != 0) ||
				((((unsigned char *)inner)[0x113] & 4) != 0) ||
				(((flags & 0x4000) != 0) && !rva004884B7((Object *)arg))))
		{
			return 1;
		}
	}
	return 0;
}
// ?Rva005964ECGet@@YGHPAX@Z @0x005964EC 92B
// Bit-test predicate returning Int: loads inner at arg+4, ecx at +0x10c,
// edx 0x1000000; requires (ecx&0x400000==0 or [0x120]&edx!=0) and
// ([0x118]&4==0 or ecx&0x40!=0) and [0x108]&0x80!=0 and [0x120]&0x10==0 and
// ecx&0x40000==0 and [0x114]&edx==0 for 1, else 0.
// Evidence: mov eax[esp+4] mov eax[eax+4] mov ecx[exa+10c] test chain with
// edx 0x1000000; callers at 0x00596553 and 0x00596640; __stdcall ret 4.
Int __stdcall Rva005964ECGet(void *arg)
{
	void *inner = *(void **)((char *)arg + 4);
	unsigned int bitfields = *(unsigned int *)((char *)inner + 0x10C);
	unsigned int denom = 0x1000000;
	if (((bitfields & 0x400000) == 0 ||
			(*(unsigned int *)((char *)inner + 0x120) & denom) != 0) &&
		((((unsigned char *)inner)[0x118] & 4) == 0 ||
			((bitfields & 0x40) != 0)) &&
		((((unsigned char *)inner)[0x108] & 0x80) != 0) &&
		((*(unsigned int *)((char *)inner + 0x120) & 0x10) == 0) &&
		((bitfields & 0x40000) == 0) &&
		((*(unsigned int *)((char *)inner + 0x114) & denom) == 0))
	{
		return 1;
	}
	return 0;
}
// ?Rva00596446Get@@YGHPAX@Z @0x00596446 44B
// Bit-test predicate returning Int: loads inner at arg+4, requires
// [0x10E]&0x44==0 and [0x108]&0x80!=0 and [0x120]&0x10!=0 for 1, else 0.
// Evidence: mov eax[esp+4] mov eax[eax+4] test chain; callers at 0x00596476
// and 0x00596495; __stdcall ret 4 with xor+inc.
Int __stdcall Rva00596446Get(void *arg)
{
	void *inner = *(void **)((char *)arg + 4);
	if ((((unsigned char *)inner)[0x10E] & 0x44) == 0 &&
		(((unsigned char *)inner)[0x108] & 0x80) != 0 &&
		(((unsigned char *)inner)[0x120] & 0x10) != 0)
	{
		return 1;
	}
	return 0;
}
// ?rva00596472@Rva0025C061@@QAE_NPAX@Z @0x00596472 31B
// __thiscall predicate over holder: requires Rva00596446Get(holder)!=0
// (byte test al), then calls this Rva0025C061::rva0025C061(holder) with same
// ecx and returns true, else false. Same-this ECX survives because callee
// definition is visible in this TU (shape-lever visibility); separate TU
// spills this to esi and grows to 37B.
// Evidence: push [esp+4] call 0x596446 test al je; push [esp+4] call 0x25C061;
// mov al1 jmp xor al ret4; caller at 0x004E01F9; ecx pass-through.
enum ScienceType
{
	SCIENCE_FIRST = 0
};

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &v);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Rva0025C061
{
public:
	void rva0025C061(void *holder);
	bool rva00596472(void *holder);
	bool rva005960C1(void *holder);
private:
	int m_unk0;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_sciences;
};

bool Rva0025C061::rva00596472(void *holder)
{
	if (((unsigned char)Rva00596446Get(holder)) != 0)
	{
		rva0025C061(holder);
		return true;
	}
	return false;
}
// ?rva00596491@Rva0025BF8C@@QAE_NPAX@Z @0x00596491 31B
// __thiscall predicate over holder: requires Rva00596446Get(holder)!=0
// (byte test al), then calls this Rva0025BF8C::rva0025BF8C(holder) with same
// ecx and returns true, else false. Same-this ECX survives because callee
// definition is visible in this TU (shape-lever visibility).
// Evidence: push [esp+4] call 0x596446 test al je; push [esp+4] call 0x25BF8C;
// mov al1 jmp xor al ret4; caller at 0x004E043B; ecx pass-through.
class CreateAHeroData;
class Rva0025BF8C
{
public:
	bool rva0025BF8C(void *holder);
	bool rva00596491(void *holder);
	bool rva005960E0(void *holder);
private:
	char m_pad[4];
	_STL::vector<CreateAHeroData *, _STL::allocator<CreateAHeroData *> > m_vec04;
};

bool Rva0025BF8C::rva00596491(void *holder)
{
	if (((unsigned char)Rva00596446Get(holder)) != 0)
	{
		rva0025BF8C(holder);
		return true;
	}
	return false;
}
// ?rva005960C1@Rva0025C061@@QAE_NPAX@Z @0x005960C1 31B
// __thiscall predicate over holder: requires Rva00596095Get(holder)!=0
// (byte test al), then calls this Rva0025C061::rva0025C061(holder) with same
// ecx and returns true, else false. Same-this ECX survives because callee
// definition is visible in this TU (shape-lever visibility).
// Evidence: push [esp+4] call 0x596095 test al je; push [esp+4] call 0x25C061;
// mov al1 jmp xor al ret4; caller at 0x004E0257; ecx pass-through.
bool Rva0025C061::rva005960C1(void *holder)
{
	if (((unsigned char)Rva00596095Get(holder)) != 0)
	{
		rva0025C061(holder);
		return true;
	}
	return false;
}
// ?rva005960E0@Rva0025BF8C@@QAE_NPAX@Z @0x005960E0 31B
// __thiscall predicate over holder: requires Rva00596095Get(holder)!=0
// (byte test al), then calls this Rva0025BF8C::rva0025BF8C(holder) with same
// ecx and returns true, else false. Same-this ECX survives because callee
// definition is visible in this TU (shape-lever visibility); separate TU
// spills this to esi (prior blocked ecx save wall t=12).
// Evidence: push [esp+4] call 0x596095 test al je; push [esp+4] call 0x25BF8C;
// mov al1 jmp xor al ret4; caller at 0x004E048D; ecx pass-through.
bool Rva0025BF8C::rva005960E0(void *holder)
{
	if (((unsigned char)Rva00596095Get(holder)) != 0)
	{
		rva0025BF8C(holder);
		return true;
	}
	return false;
}
