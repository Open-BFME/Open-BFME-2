// cl: /O1 /DNDEBUG /MD /EHsc
// ?Rva00055041AsciiHash@@YGIPBVAsciiString@@@Z, retail 0x00055041 (28B).
// Shard TU: AsciiString chars-or-empty forwarder into the STLport string
// hash. The chars live 8 past the StringBase header (ref_count plus
// length plus capacity); a null header falls back to the retail empty
// literal at VA 0x00BBAC1C. The hash resolves via its ledger pin: the
// donor is STLport vendored _hash_fun __stl_hash_string verbatim (imul5
// loop over signed chars), which is inline in its header and therefore
// never rowed itself. Stdcall per ret-4 with an unused ecx.

template <typename T>
class StringBase
{
public:
    void concat(const T *text);

private:
    friend class AsciiString;

    StringBase(const T *text);
    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString
{
public:
    AsciiString(const char *text)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
    }

    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            (const StringBase<char> &)that);
    }

    ~AsciiString();

private:
    char *m_text;
};

namespace _STL
{
	unsigned int __stl_hash_string(const char *s);
}

// ?Rva00055041AsciiHash@@YGIPBVAsciiString@@@Z
unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name)
{
	const StringBase<char> *data = *(const StringBase<char> * const *)name;
	const char *chars = data != 0 ? (const char *)data + 8 : (const char *)0x00BBAC1C;
	return _STL::__stl_hash_string(chars);
}
