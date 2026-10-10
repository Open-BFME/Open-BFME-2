// Target 002B236A returns receiver+34; its class identity is unknown.
// The former HRawAnimClass::Get_HName attribution was a unique-byte-placement
// inference. Native raw vtable BD5D20 slot4 selects 0066D7D0 (+30), not this row.
class Rva002B236AField { public: void *get() const; };
void *Rva002B236AField::get() const { return (char *)this + 0x34; }
