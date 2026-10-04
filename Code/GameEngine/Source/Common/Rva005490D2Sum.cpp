// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva005490AE@Rva005490D2@@QBEHXZ, RVA 0x005490AE, 36B
// ?rva005490D2@Rva005490D2@@QBEHXZ, RVA 0x005490D2, 31B
// Max and summing loops over the array at +4 with count at +0 via double
// indirection; retail places them back to back. The max takes the dword at
// +0x564 with cmovg (callers 0x00549403 and 0x0054945F), which MSVC 7.1
// emits only under /arch:SSE; the sum adds the dword at +0x568 (single
// caller at 0x005493CC). xor-first and dec/jne point to /O1; neighbours are
// Disp getters and a clamped setter.
struct Leaf005490D2 {
	char pad[0x564];
	int field564;
	int field568;
};
struct Mid005490D2 {
	int unk0;
	Leaf005490D2 *leaf;
};
struct Rva005490D2 {
	int count;
	Mid005490D2 *array[1];
	int rva005490AE() const;
	int rva005490D2() const;
};
int Rva005490D2::rva005490AE() const
{
	int best = 0;
	for (int i = 0; i < count; ++i) {
		int v = array[i]->leaf->field564;
		if (v > best)
			best = v;
	}
	return best;
}
int Rva005490D2::rva005490D2() const
{
	int total = 0;
	int n = count;
	if (n > 0) {
		Mid005490D2 **p = (Mid005490D2 **)array;
		do {
			total += (*p)->leaf->field568;
			++p;
		} while (--n);
	}
	return total;
}
