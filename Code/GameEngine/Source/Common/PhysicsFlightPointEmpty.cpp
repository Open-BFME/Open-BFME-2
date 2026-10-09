// cl: /O1 /MD /EHsc
// A 12B flight-point call view: native3901DA arrays require independent empty
// ctor/dtor callbacks at47A6A9/B3FD0. These definitions are complete byte-and-
// relocation twins of canonical Coord3D callbacks and add zero unique bytes.
#include "../../../Libraries/Include/Lib/Coord3D.h"
struct Rva003901DAPoint : Coord3D { Rva003901DAPoint();~Rva003901DAPoint(); };
Rva003901DAPoint::Rva003901DAPoint() {}
Rva003901DAPoint::~Rva003901DAPoint() {}
