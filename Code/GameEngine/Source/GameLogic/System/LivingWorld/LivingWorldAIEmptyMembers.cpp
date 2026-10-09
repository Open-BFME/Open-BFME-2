// cl: /O1 /G7 /EHsc /MD /arch:SSE
// The two otherwise unnamed embedded members at LivingWorldAI+8C/+120
// are initialized by the genuine three-byte empty constructor fold47A6A9.
// Native4FB458/4FB485 and WB1319A7F/1319AB5 independently establish
// ordinary member lifetimes. Layout widths come from native adjacent fields;
// the original member classes are unknown. Keep providers in a separate TU
// so the caller preserves the retail out-of-line initialization boundaries.
class Rva004FB3F2State8C { public: Rva004FB3F2State8C(); ~Rva004FB3F2State8C(); char bytes[0x60]; };
class Rva004FB3F2State120 { public: Rva004FB3F2State120(); ~Rva004FB3F2State120(); int value; };
Rva004FB3F2State8C::Rva004FB3F2State8C() {}
Rva004FB3F2State120::Rva004FB3F2State120() {}

class Rva004FB3F2Iterator { public: Rva004FB3F2Iterator(); ~Rva004FB3F2Iterator(); int first,last,current,node; };
Rva004FB3F2Iterator::Rva004FB3F2Iterator():first(0),last(0),current(0),node(0) {}

Rva004FB3F2State8C::~Rva004FB3F2State8C() {}
Rva004FB3F2State120::~Rva004FB3F2State120() {}
Rva004FB3F2Iterator::~Rva004FB3F2Iterator() {}
