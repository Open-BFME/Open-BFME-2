// Pointer-chase null-or-zero int getters: fifteen-byte __thiscall members
// (nineteen bytes compiled, sharing the trailing four-byte true-tail) with
// one shape:
//
//     mov eax,[ecx] / test eax,eax / jz true / cmp [eax+8],0 / jz true
//       / xor eax,eax / ret / true: xor eax,eax / inc eax / ret
//
// A pointer is read from `this`, null selects true, otherwise the dword at
// +8 through the pointer selects true when zero; only a non-null pointer to
// a non-zero dword returns zero. The true-tail (`xor eax,eax / inc eax /
// ret`) is the shared four-byte int-one getter immediately following each
// body in retail, so the ledger claims the first fifteen bytes here and the
// tail lives in IntOneGetters.cpp. Spelled as a single AND returning zero
// with a trailing `return 1`, which MSVC 7.1 under /O1 emits with the two
// forward jumps to the local tail. Identity is not recovered: every name is
// derived from its address.
// cl: /O1
class Rva00262117NullOrZero
{
public:
	int get() const;
	int *m_ptr;
};

struct Rva00262117Inner
{
	int m_first;
	int m_second;
	int m_third;
};

int Rva00262117NullOrZero::get() const
{
	int *raw = m_ptr;
	if (raw != 0 && ((Rva00262117Inner *)raw)->m_third != 0)
		return 0;
	return 1;
}
