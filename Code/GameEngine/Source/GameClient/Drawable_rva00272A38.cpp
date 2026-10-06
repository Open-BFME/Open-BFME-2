// cl: /DNDEBUG /MD /EHsc
// ?rva00272A38@Drawable@@QAEXXZ retail 0x00272A38 25 bytes.
// Void walk over null-terminated Elem array at +0x14C calling slot34. Evidence: same +0x14C walk as neighbour Drawable_rva00272A02 0x00272A02; prev 0x00272A02 same flags.
class Elem
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13();
};
class Drawable
{
public:
	void rva00272A38();
private:
	unsigned char m_pad[0x14C];
	Elem **m_arr;
};

void Drawable::rva00272A38()
{
	for (Elem **pp = m_arr; *pp != 0; ++pp)
		(*pp)->s13();
}
