// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@QAE@XZ @0x0007C5D5 63B:
// STLport 4.5.3 vector<Rva0007BB16Record>::~vector over the 0x24-byte
// two-string record (same definition as stlport_vector_rva0007bb16_destroy.cpp
// and Code/GameEngine/Source/Common/StringRecordDtors.cpp). Retail destroys
// the range through the rowed _Destroy at 0x0007C2D7 then frees via 0x00030830
// (EH states 0/-1); called by 16 parents including 0x0007DBEC and 0x00152496.
#include <vector>

#include "ascii_string.h"

struct Rva0007BB16Record
{
	~Rva0007BB16Record();
	AsciiString m_00;
	int m_04;
	AsciiString m_08;
	int m_tail0C[6];
};

template _STL::vector<Rva0007BB16Record>::~vector();
