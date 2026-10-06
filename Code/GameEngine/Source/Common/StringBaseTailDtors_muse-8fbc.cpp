// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Tail-jmp dtors to pinned StringBase<char> dtor 0x00036410 (17 pins): add ecx,disp; jmp.
// Each outer class holds StringBase<char> at the retail displacement; empty dtor tail-calls it at /O1.
template <typename T> class StringBase { public: ~StringBase(); };

// ??1Rva000B9AAA@@QAE@XZ @0x000B9AAA 8B; add ecx,0x10; jmp StringBase D dtor. 9 callers incl 4 Unwind funclets.
class Rva000B9AAA { public: ~Rva000B9AAA(); private: char m_lead[0x10]; StringBase<char> m_str; };
Rva000B9AAA::~Rva000B9AAA() {}

// ??1Rva00255D17@@QAE@XZ @0x00255D17 8B; add ecx,0x1C; jmp StringBase D dtor. 11 callers incl 7 Unwind funclets.
class Rva00255D17 { public: ~Rva00255D17(); private: char m_lead[0x1C]; StringBase<char> m_str; };
Rva00255D17::~Rva00255D17() {}

// ??1Rva004D9A3C@@QAE@XZ @0x004D9A3C 8B; add ecx,0x14; jmp StringBase D dtor. 2 callers incl Unwind.
class Rva004D9A3C { public: ~Rva004D9A3C(); private: char m_lead[0x14]; StringBase<char> m_str; };
Rva004D9A3C::~Rva004D9A3C() {}
