// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$_Construct@URva0039627D@@U1@@_STL@@YAXPAURva0039627D@@ABU1@@Z @0x0039695E 45B
// _STL::_Construct<Rva0039627D,Rva0039627D> via vendored <memory> (EH framed 45B precedent
// stlport_construct_rva_records.cpp rowed _Construct<Rva003371B1> 0x00337313).
// Evidence: copy ctor ??0Rva0039627D@@QAE@ABU0@@Z rowed at 0x003962AE;
// caller 0x00397CC9 allocates 0x20 via 0x000307F0 and constructs at +0x10;
// chain from 0x003962AE landed this session.
#include <memory>
struct Rva0039627D
{
	Rva0039627D(const Rva0039627D &other);
};
template void _STL::_Construct<Rva0039627D, Rva0039627D>(Rva0039627D *, const Rva0039627D &);
