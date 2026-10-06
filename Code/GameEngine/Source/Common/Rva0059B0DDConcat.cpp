// cl: /MD /EHsc
// ?Rva0059B0DDConcat@@YAPAV?$StringBase@D@@PAV1@PBD@Z @0x0059B0DD (56B)
// Free concat helper wrapping arg2 as 8-byte CharSource on the stack then
// calling rowed StringBase<char>::concat 0x00036A30 with arg1 as this,
// returning arg1.
// Same wrapper recipe as NarrowStrLenSource but single pointer field.
// Evidence: vtable data 0x00870E60 plus caller 0x0059B703 in 0x0059B5A3.
template <typename T>
class CharSource
{
public:
	virtual int getLength() const = 0;
	virtual void _gap() const = 0;
	virtual int getChars(T *dest) const = 0;
};

template <typename T>
class StringBase
{
public:
	void concat(const CharSource<T> &source);
};

class NarrowStrSource0059B0DD : public CharSource<char>
{
public:
	NarrowStrSource0059B0DD(const char *s) : m_str(s) {}
	~NarrowStrSource0059B0DD() {}
	virtual int getLength() const;
	virtual void _gap() const {}
	virtual int getChars(char *dest) const;

private:
	const char *m_str;
};

StringBase<char> *__cdecl Rva0059B0DDConcat(StringBase<char> *dst, const char *src)
{
	NarrowStrSource0059B0DD tmp(src);
	dst->concat(tmp);
	return dst;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?getChars@NarrowStrSource0059B0DD@@UBEHPAD@Z=?rva0059B3C1@Rva0059B3C1@@QAEHPAD@Z")
