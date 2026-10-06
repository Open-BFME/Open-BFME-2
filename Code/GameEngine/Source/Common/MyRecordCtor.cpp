// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
#include "ascii_string.h"

// ??0MyRecord@@QAE@XZ @0x0033B0EF 52B.
// Container-record default ctor: BitFlags<11> at +0, AsciiString at +4,
// int at +8; then init helper 0x0033A865 on same this. Evidence: retail calls
// BitFlags 0x3B31AD with this, ANDs +4 to 0 (AsciiString inline default),
// arms EH state 0, then calls 0x0033A865 with same this; LINK BONUS 61B via
// Rva0033E102Rebuild caller 0x0033E136; layout {4,string,4} matches
// BfmeContainerRecord002CF46E and Rva0033E102Rebuild MyRecord.
template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags();
private:
	unsigned int m_words[1];
};

class Rva0033A865
{
public:
	void rva0033A865();
};

struct MyRecord
{
	MyRecord();
	BitFlags<11> m00;
	AsciiString m04;
	int m08;
};

MyRecord::MyRecord()
{
	((Rva0033A865 *)this)->rva0033A865();
}
