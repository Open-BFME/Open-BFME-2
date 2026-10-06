// cl: /Oy- /MD /EHsc
// ?rva004D6187@Rva004D60CA@@QAEXV?$StringBase@G@@@Z @0x004D6187 (52B):
// Wide-string setter on Rva004D60CA: copies the by-value argument into the
// +0x1c StringBase<wchar> member via pin-only set 0x00037150, then destroys
// the parameter via rowed releaseBuffer 0x00036E70 (inlined dtor, EH state).
// Evidence: caller 0x004D187B builds esi with Rva004D60CA ctor 0x004D60CA
// then calls this with a StringBase<wchar> temp; callers 0x004D17C5 etc.

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
	void set(const StringBase &other);
private:
	void releaseBuffer();
	T *m_data;
};

class Rva004D60CA
{
public:
	void rva004D6187(StringBase<unsigned short> s);
private:
	char m_pad00[0x1c];
	StringBase<unsigned short> m_str1c;
};

void Rva004D60CA::rva004D6187(StringBase<unsigned short> s)
{
	StringBase<unsigned short> &slot = m_str1c;
	slot.set(s);
}
