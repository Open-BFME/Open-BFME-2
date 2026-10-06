// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD1B3@@QAE@ABU0@@Z @0x001DD1B3 29B
// Copy ctor of 36-byte record with int head and Rva001DD063 tail at +4.
// Evidence: retail copies [eax] then calls rowed 0x001DD063 with this+4;
// callers show outer returns this; same shape as sibling pod ctors.
struct Rva001DD063 {
    int f00;
    unsigned char b04;
    unsigned char b05;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    Rva001DD063(const Rva001DD063 &o);
};
struct Rva001DD1B3 {
    int f00;
    Rva001DD063 f04;
    Rva001DD1B3(const Rva001DD1B3 &o);
};
Rva001DD1B3::Rva001DD1B3(const Rva001DD1B3 &o)
    : f00(o.f00), f04(o.f04)
{
}
