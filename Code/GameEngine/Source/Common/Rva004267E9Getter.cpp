// cl: /MD
// stlport
// ?rva004267E9@Rva004266A1@@QAEPAXH@Z @0x004267E9 36B
// Indexed pointer into the same 8-byte record vector at +4 as Rva004266A1::rva004266A1.
// Bounds check calls the rowed rva004266A1 then returns &vec[index] (lea begin+index*8)
// else the exported empty AsciiString::TheEmptyString at 0x009E0878. Callers 0x004E45A3
// and 0x0051C2BB pass the result to AsciiString::operator= proving the +0 text member.
#include <vector>
class AsciiString { public: AsciiString(const AsciiString &); AsciiString &operator=(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; public: static const AsciiString TheEmptyString; };
struct Rva004266A1Rec { AsciiString text; unsigned char flag0; unsigned char flag1; unsigned char flag2; };
struct Rva004266A1 { char pad[4]; _STL::vector<Rva004266A1Rec> vec; bool rva004266A1(int index); void *rva004267E9(int index); };
void *Rva004266A1::rva004267E9(int index)
{
    if (!rva004266A1(index))
        return (void *)&AsciiString::TheEmptyString;
    return &vec[index];
}
