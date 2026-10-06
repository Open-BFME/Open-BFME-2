// cl: /DNDEBUG /MD /EHsc
// ?Rva005F09FFAssign@@YAXPAPAX0@Z, retail 0x005F09FF, 24 bytes.
// Target bytes show a null-guarded one-pointer copy, then a conditional
// increment of the copied referent's dword at +0x08. Keep the name address-
// derived: two existing _Construct pins point here for different four-byte
// element types, so they do not establish one target type identity.

struct Rva005F09FFReferent
{
	unsigned char m_unmodelled_000[0x08];
	unsigned m_references;
};

void Rva005F09FFAssign(void **dest, void **source)
{
	if (dest == 0)
		return;
	void *object = *source;
	*dest = object;
	if (object == 0)
		return;
	++static_cast<Rva005F09FFReferent *>(object)->m_references;
}
