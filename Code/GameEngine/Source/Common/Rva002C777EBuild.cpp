// cl: /O1 /DNDEBUG /MD
//
// ?rva002C777E@@YAPAVWeaponTemplateSetHead@@PAV1@H@Z @0x002C777E 257B:
// Head builder (cdecl, out ptr + index, returns out). Memsets the 0x4C head,
// switch on idx builds one of five 19-dword masks through the pinned
// 0x002C760B bit-setter (thiscall, zero + 7 bit ids, returns this) and
// OR-merges it via the landed 0x002C7492 row, then copy-constructs out
// through the landed 0x00045455 copy ctor. Per-case build+merge tails are
// shared by the compiler (single build call site); the default path
// re-memsets and skips the merge. Buffers are one 5-entry array; indices
// chosen so each lea hits its retail ebp offset. Head/mask share the 0x4C
// layout (Rva002C7492 int[19] view for merge/build, WeaponTemplateSetHead
// for out/copy); exact function identity unproven.
extern "C" void *memset(void *dst, int c, unsigned n);

typedef unsigned size_t;
inline void *operator new(size_t, void *place)
{
	return place;
}

class Rva002C7492
{
public:
	void rva002C7492(const Rva002C7492 *other);
	Rva002C7492 *rva002C760B(int zero, int b0, int b1, int b2, int b3, int b4, int b5, int b6);

private:
	int m_mask[19];
};

class WeaponTemplateSetHead
{
	char _m[0x4C];

public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
};

WeaponTemplateSetHead *__cdecl rva002C777E(WeaponTemplateSetHead *out, int idx)
{
	__assume(out != 0);
	Rva002C7492 head;
	memset(&head, 0, 0x4C);
	Rva002C7492 bufs[5];
	switch (idx) {
	case 0:
		head.rva002C7492(bufs[0].rva002C760B(0, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x28, 0x7b));
		break;
	case 1:
		head.rva002C7492(bufs[2].rva002C760B(0, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x2e, 0x7c));
		break;
	case 2:
		head.rva002C7492(bufs[3].rva002C760B(0, 0x35, 0x36, 0x37, 0x38, 0x39, 0x34, 0x7d));
		break;
	case 3:
		head.rva002C7492(bufs[4].rva002C760B(0, 0x212, 0x21c, 0x21e, 0x214, 0x216, 0x218, 0x21a));
		break;
	case 4:
		head.rva002C7492(bufs[1].rva002C760B(0, 0x213, 0x21d, 0x21f, 0x215, 0x217, 0x219, 0x21b));
		break;
	default:
		memset(&head, 0, 0x4C);
		break;
	}
	new (out) WeaponTemplateSetHead((const WeaponTemplateSetHead &)head);
	return out;
}
