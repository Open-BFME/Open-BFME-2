// ?rva000AFAD6@Rva000AFAD6@@QAE?AVOpen2Rec74A060@@H@Z
// cl: /O1 /Oy- /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// This class declaration mirrors the target type used by the matched copy
// constructor at 0x000AEBFF. The target call and 0x28 element stride support
// this return type; the enclosing container identity is unknown.
class Open2Rec74A060
{
public:
    Open2Rec74A060( const Open2Rec74A060 &other );
    int m_at00;
    int m_at04;
    int m_at08;
    int m_at0c;
    int m_at10;
    AsciiString m_at14;
    int m_at18;
    int m_at1c;
    int m_at20;
    int m_at24;
};

// Address-derived owner: target evidence establishes a by-value element
// lookup, while the owning class and method name are not established.
class Rva000AFAD6
{
public:
    Open2Rec74A060 rva000AFAD6( int index );
};

Open2Rec74A060 Rva000AFAD6::rva000AFAD6( int index )
{
    Open2Rec74A060 *elements = (Open2Rec74A060 *)( (char *)this + 0x80CC );
    return elements[ index ];
}
