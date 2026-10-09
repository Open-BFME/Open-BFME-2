// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00427FB2@Rva00427FB2@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ
// retail 0x00427FB2 324 bytes (ret 4: the string comes back through the
// hidden return buffer).
// Serializes a key/value list into "||VER1|<limit>|key=value|key=value|..."
// through an ostrstream (rowed ctor 0x00603200 _M_put_nowiden 0x001F5F65
// unsigned-long _M_put_num 0x001F60AA dtor 0x00602E50 and the inline
// basic_ios teardown into ios_base::~ios_base 0x0001C220). The limit at +0
// must cover the 7-char header and the finished text must stay under it
// (a signed compare); otherwise the result is "" (rowed
// basic_string(const char*) 0x00009100). The text is copied out through the
// rowed range ctor 0x0002A590 from the stream's str() and pcount().
// Retail 0x006027F0 is ostrstream::str (freeze bit in the strstreambuf
// flags at +0x60 then the get FILE base at +0x08) and 0x00602810 is
// ostrstream::pcount (put FILE at +0x0C: ptr minus base). pcount keeps the
// ledger's address name (Rva00602810); str must be the real char*-returning
// member: with an int-returning view cl calls it ahead of pcount, while
// retail reads the count first. The entries at +4..+8 are 24-byte pairs of
// narrow strings (c_str() at +0 and +0x0C). WorldBuilder twin 0x0146B8C0
// (unnamed) has the same three returns. No direct caller in retail; the
// class name keeps the address.
#include <string>
#include <vector>
#include <utility>
#include <strstream>

class Rva00602810
{
public:
	int rva00602810();
};

class Rva00427FB2
{
public:
	_STL::string rva00427FB2() const;

private:
	unsigned int m_limit; // +0
	_STL::vector<_STL::pair<_STL::string, _STL::string> > m_entries; // +4
};

_STL::string Rva00427FB2::rva00427FB2() const
{
	if (m_limit < 7)
		return _STL::string("");
	_STL::ostrstream out;
	out << "||VER1|" << m_limit << "|";
	for (_STL::vector<_STL::pair<_STL::string, _STL::string> >::const_iterator it = m_entries.begin();
		it != m_entries.end(); ++it)
	{
		out << it->first.c_str() << "=" << it->second.c_str() << "|";
	}
	if (((Rva00602810 *)&out)->rva00602810() >= (int)m_limit)
		return _STL::string("");
	return _STL::string((const char *)out.str(), (const char *)out.str() + ((Rva00602810 *)&out)->rva00602810());
}
