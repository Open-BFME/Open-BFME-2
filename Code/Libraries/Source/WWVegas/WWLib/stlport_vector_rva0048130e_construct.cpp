// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??$_Construct@URva0048130E@@U1@@_STL@@YAXPAURva0048130E@@ABU1@@Z, retail 0x00481514, 45 bytes.
// True _Construct for ProductionQueueHordeContainModuleData's +0xD4 vector
// element (8-byte Rva0048130E): null-tests dest then copy-constructs via the
// rowed 0x0048147C. Same 45B EH shape as other _Constructs; called by the
// uninitialized-copy workers at 0x00481541/0x00481567.
#include <vector>

struct Rva0048130E
{
	~Rva0048130E();
	Rva0048130E(const Rva0048130E &);
};

template void _STL::_Construct<Rva0048130E, Rva0048130E>(Rva0048130E *, const Rva0048130E &);
