// cl: /O1 /DNDEBUG /MD
// ?Rva001F8FEEWrite@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDABUS001F87D5@@@Z @0x001F8FEE 24B: guarded forward to rowed Rva001F8B5FWrite via rowed Rva001F3744IsZero.
// Evidence: push dword [ebp+0x14] call 0x001F3744 test al jne jmp 0x001F8B5F; same guarded-forward shape as Rva001F9006Write; chain lane from 0x001F3744; no callers.
namespace _STL
{
template <class C> class char_traits
{
};
template <class C, class T> class basic_ostream
{
};
}

struct S001F87D5
{
    char _0[4];
    float x;
    float y;
};

struct S001F3744
{
    char m_00[4];
    float m_04;
    float m_08;
};

bool __cdecl Rva001F3744IsZero(const S001F3744 *p);
void Rva001F8B5FWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const S001F87D5 &value);

void Rva001F8FEEWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const S001F87D5 &value)
{
    if (Rva001F3744IsZero((const S001F3744 *)&value))
        return;
    Rva001F8B5FWrite(os, pad, key, value);
}
