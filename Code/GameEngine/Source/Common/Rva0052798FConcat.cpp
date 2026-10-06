// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva0052798FAppend@@YAAAVAsciiString@@AAV1@PBD@Z @ 0x0052798F (56B): free concat helper wrapping const char* as CharSource then StringBase concat returning dst. Evidence: same 56B EH_prolog shape as Rva00222C93Append 0x00222C93 plus Rva0059B0DD Rva00317C68; vtable g_00C6805C; callee rowed concat 0x00036A30; caller 0x00527B4B.
#include "ascii_string.h"
extern const void *const g_00C6805C[];
template <typename T>
class CharSource
{
public:
	virtual int getLength() const = 0;
	virtual void _gap() const = 0;
	virtual int getChars(T *dest) const = 0;
	virtual ~CharSource() {}
};
class CharSourceNarrow0052798F : public CharSource<char>
{
public:
	CharSourceNarrow0052798F(const char *s)
	{
		*(const void **)this = g_00C6805C;
		m_str = s;
	}
	int getLength() const;
	void _gap() const;
	int getChars(char *dest) const;
private:
	const char *m_str;
};
AsciiString &Rva0052798FAppend(AsciiString &dst, const char *src)
{
	CharSourceNarrow0052798F tmp(src);
	((StringBase<char> &)dst).concat(tmp);
	return dst;
}
