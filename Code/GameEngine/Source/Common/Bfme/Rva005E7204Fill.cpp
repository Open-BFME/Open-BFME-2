// cl: /DNDEBUG /MD /EHsc
// ?Rva005E7204Fill@@YAPAPAXPAPAXI0PAX@Z, retail 0x005E7204, 37 bytes.
// Null-guarded fill looping Rva005E71C6Assign at 0x005E71C6 with +0x28
// refcount. Evidence: caller at 0x005E81F9 passes 4 words; body ignores
// the 4th.

void Rva005E71C6Assign(void **dest, void **source);

void **Rva005E7204Fill(void **dest, unsigned count, void **source, void *unused)
{
	void **d = dest;
	unsigned n = count;
	if (n <= 0)
		return d;
	do {
		Rva005E71C6Assign(d, source);
		++d;
		--n;
	} while (n != 0);
	return d;
}
