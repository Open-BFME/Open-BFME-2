// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Eight 5B novtable empty dtors each tail-jumping to its rowed/pinned Map base
// dtor: 0x00207BDA->0x002075F3, 0x00207BDF->0x00207630, 0x00207BE4->0x0020766D,
// 0x00207BE9->0x002076AA, 0x00207BEE->0x002076E7, 0x00207BF3->0x00207724,
// 0x00207BF8->0x00207761, 0x00207BFD->0x0020779E. Evidence: each target pinned
// ??1Rva00XXXXMap@@QAE@XZ, Unwind callers, prev pop_fwd flags, §4.8 5-byte jmp
// novtable recipe.
class Rva002075F3Map { public: ~Rva002075F3Map(); };
class __declspec(novtable) Rva00207BDAMap : public Rva002075F3Map { public: ~Rva00207BDAMap(); };
Rva00207BDAMap::~Rva00207BDAMap() {}
class Rva00207630Map { public: ~Rva00207630Map(); };
class __declspec(novtable) Rva00207BDFMap : public Rva00207630Map { public: ~Rva00207BDFMap(); };
Rva00207BDFMap::~Rva00207BDFMap() {}
class Rva0020766DMap { public: ~Rva0020766DMap(); };
class __declspec(novtable) Rva00207BE4Map : public Rva0020766DMap { public: ~Rva00207BE4Map(); };
Rva00207BE4Map::~Rva00207BE4Map() {}
class Rva002076AAMap { public: ~Rva002076AAMap(); };
class __declspec(novtable) Rva00207BE9Map : public Rva002076AAMap { public: ~Rva00207BE9Map(); };
Rva00207BE9Map::~Rva00207BE9Map() {}
class Rva002076E7Map { public: ~Rva002076E7Map(); };
class __declspec(novtable) Rva00207BEEMap : public Rva002076E7Map { public: ~Rva00207BEEMap(); };
Rva00207BEEMap::~Rva00207BEEMap() {}
class Rva00207724Map { public: ~Rva00207724Map(); };
class __declspec(novtable) Rva00207BF3Map : public Rva00207724Map { public: ~Rva00207BF3Map(); };
Rva00207BF3Map::~Rva00207BF3Map() {}
class Rva00207761Map { public: ~Rva00207761Map(); };
class __declspec(novtable) Rva00207BF8Map : public Rva00207761Map { public: ~Rva00207BF8Map(); };
Rva00207BF8Map::~Rva00207BF8Map() {}
class Rva0020779EMap { public: ~Rva0020779EMap(); };
class __declspec(novtable) Rva00207BFDMap : public Rva0020779EMap { public: ~Rva00207BFDMap(); };
Rva00207BFDMap::~Rva00207BFDMap() {}
