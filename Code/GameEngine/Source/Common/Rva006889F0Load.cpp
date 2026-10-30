// cl: /O2 /GB /arch:SSE /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// Native6889F0..688A9B,171B;4CC leading/5CC trailing; RET4.
// Same receiver reaches the owned reset6888D0 and the path string at+8.
// INI loader2DA4B takes the named parseVideoDefinition callback75A4DC.
// BF1 a7c38d3b VideoPlayerInit.cpp guides the INI lifetime and callback load;
// Bfme5HandOffClears.cpp guides the existing receiver reset. Name unresolved.
#include <string.h>
#include "string_base.h"
// Visible original StringBase C-string setter: receiver is computed before
// its inlined nullable strlen. Import-inline: expanded here, no copy emitted.
template <> __declspec(dllimport) __forceinline void StringBase<char>::set(const char *text) {
    set(text, text ? strlen(text) : 0);
}
#include "ascii_string.h"
// AsciiString::operator=(const char *) as an inline-only helper: the operator
// itself would also emit this TU's copy of the 0x000065B8 body in its
// strlen-inlined form (retail's copy calls the out-of-line setter).
static __forceinline AsciiString &AssignCString(AsciiString &s, const char *text)
{
    ((StringBase<char> *)&s)->set(text);
    return s;
}
class Xfer;
enum INILoadType {INI_LOAD_INVALID,INI_LOAD_OVERWRITE};
struct FieldParse;
class INI
{
public:
	INI();
	~INI();
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const FieldParse *parseTable );
	int getLineNum( void ) const;
	AsciiString getFilename( void ) const;
	void load(AsciiString, INILoadType, Xfer *, void (*)(INI *));
	static void parseVideoDefinition(INI *);

private:
	char m_prefix[4];
	AsciiString m_filename;
	char storage[0x874];
};
namespace _STL { void __cdecl free(void *); }

class Rva006888D0Owned
{
public:
    virtual ~Rva006888D0Owned();
};

inline Rva006888D0Owned **copyOwned(Rva006888D0Owned **destination,
    Rva006888D0Owned **first, Rva006888D0Owned **last);

inline Rva006888D0Owned **copyOwned(Rva006888D0Owned **destination,
    Rva006888D0Owned **first, Rva006888D0Owned **last)
{
    if (first == last)
        return destination;
    int bytes = (char *)last - (char *)first;
    return (Rva006888D0Owned **)((char *)memmove(destination, first, bytes) + bytes);
}

struct Rva006888D0Vector
{
    ~Rva006888D0Vector() { if (begin != 0) _STL::free(begin); }
    Rva006888D0Owned **begin;
    Rva006888D0Owned **end;
    Rva006888D0Owned **capacity;
    void clear() { end = copyOwned(begin, end, end); }
};

class Rva00688980
{
public:
	~Rva00688980();
	void rva006888D0();
	void rva006889F0(const char *path);
private:
	char prefix[8]; // +0x00
	AsciiString m_nameA; // +0x08
	AsciiString m_nameB; // +0x0C
	int m_count; // +0x10
	Rva006888D0Vector m_vector; // +0x14
};

void Rva00688980::rva006889F0(const char *path)
{
    rva006888D0();
    AssignCString(m_nameA, path);
    INI ini;
    ini.load(path,INI_LOAD_OVERWRITE,0,INI::parseVideoDefinition);
}
