// cl: /O1 /MD /EHsc
// ?Rva00317C68Append@@YAAAVAsciiString@@AAV1@PBD@Z @0x00317C68 56B: free concat helper appending a global CharSource plus second arg via StringBase concat 0x00036A30 with EH prolog. Evidence: retail mov scope plus EH_prolog plus g_00BFDC6C vtable store plus second-arg store plus concat call plus fs restore; caller 0x00317DF7; same EH shape as 0x00317C34 setter.
extern const void *const g_00BFDC6C[];
template <typename T> class StringBase;
template <typename T>
class CharSource
{
public:
	virtual int getLength() const = 0;
	virtual void _gap() const = 0;
	virtual int getChars(T *dest) const = 0;
};
template <typename T> class StringBase
{
public:
	void concat(const CharSource<T> &source);
private:
	void *m_data;
};
class CharSourceSuffix : public CharSource<char>
{
public:
	CharSourceSuffix(const char *s)
	{
		*(const void **)this = g_00BFDC6C;
		m_arg = s;
	}
	virtual ~CharSourceSuffix() {}
	int getLength() const;
	void _gap() const;
	int getChars(char *dest) const;
private:
	const char *m_arg;
};
class AsciiString : public StringBase<char>
{
};
AsciiString &Rva00317C68Append(AsciiString &dst, const char *src)
{
	CharSourceSuffix tmp(src);
	dst.concat(tmp);
	return dst;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00BFDC6C@@3QBQBXB=??_7Rva002AAD9C@@6B@")
