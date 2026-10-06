// cl: /MD
// stlport
// ?rva0042680D@Rva004266A1@@QAEEH@Z @0x0042680D 30B
// Flag1 getter on the same 8-byte record vector at +4 as Rva004266A1::rva004266A1.
// Bounds check calls the rowed rva004266A1 then returns vec[index].flag1 (+5) else 0.
// Callers 0x002D6891/0x0039B98F/0x004E4424/0x0051C294 prove the index arg and the al test.
#include <vector>
class AsciiString { public: AsciiString(const AsciiString &); AsciiString &operator=(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
struct Rva004266A1Rec { AsciiString text; unsigned char flag0; unsigned char flag1; unsigned char flag2; };
struct Rva004266A1 { char pad[4]; _STL::vector<Rva004266A1Rec> vec; bool rva004266A1(int index); unsigned char rva0042680D(int index); };
unsigned char Rva004266A1::rva0042680D(int index)
{
    if (!rva004266A1(index))
        return 0;
    return vec[index].flag1;
}
