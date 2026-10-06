// cl: /MD
// stlport
// ?rva004266A1@Rva004266A1@@QAE_NH@Z @0x004266A1 27B
// Bounds check on a vector of 8-byte BfmeStringRecord00426A5B at +4 (begin at +4 end at +8 sar 3).
// Element layout AsciiString + 3 flags read from StringRecordCopyBFME2.cpp and the 8-byte vector
// instantiation; callers 0x004267E9/0x0042680D/0x004268F6/0x004269F7/0x0042682B/0x00426914 prove
// the +4/+8 vector and the 8-byte stride (lea/mov with index*8 and +4/+5/+6 flag loads).
// Retail idioms xor-first cmp jl and inc with jae match /O1 single-return shape.
#include <vector>
class AsciiString { public: AsciiString(const AsciiString &); AsciiString &operator=(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
struct Rva004266A1Rec { AsciiString text; unsigned char flag0; unsigned char flag1; unsigned char flag2; };
struct Rva004266A1 { char pad[4]; _STL::vector<Rva004266A1Rec> vec; bool rva004266A1(int index); };
bool Rva004266A1::rva004266A1(int index)
{
    return index >= 0 && (unsigned)index < vec.size();
}
