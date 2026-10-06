// cl: /Ob0 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE@IABUCoord3D@@ABV?$allocator@UCoord3D@@@1@@Z @0x0007C2AC 43B: STLport vector<Coord3D> count-fill ctor.
// Calls count-taking _Vector_base at 0x005C8C37 (rowed as PrereqUnitRec 60B; Coord3D spelling ICF twin same 12B stride) and 3-arg uninitialized_fill_n<Coord3D> at 0x000CA1D3 (rowed).
// Chain lane: caller of just-landed Coord3D fill_n wrapper 0xCA1D3. Callers at 0x7CED5 0x7CFF6 0x7D00E in FUN_0047c8ae. /Ob0 preserves out-of-line wrapper call per FillInsert precedent. throw() on copy removes EH per 4.1-4.2.
#include <vector>
struct Coord3D {
  float x, y, z;
  Coord3D(const Coord3D &that) throw();
};
template _STL::vector<Coord3D>::vector(unsigned int, const Coord3D&, const _STL::allocator<Coord3D>&);
