// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD0A0@@QAE@ABU0@@Z @0x001DD0A0 97B
// Copy ctor of 52-byte POD record. Evidence: called by pinned
// _STL::_Construct<BfmePod52> at 0x001DD2DC (18B, je-guarded placement new)
// and by vector<BfmePod52>::_M_fill_insert at 0x001DE5D2 (225B, 0x34 stride).
// Layout read from retail mov sequence: 8 dwords, 3 bytes, 1 pad, 4 dwords.
struct Rva001DD0A0 {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    unsigned char b20;
    unsigned char b21;
    unsigned char b22;
    int f24;
    int f28;
    int f2C;
    int f30;
    Rva001DD0A0(const Rva001DD0A0 &o);
};
Rva001DD0A0::Rva001DD0A0(const Rva001DD0A0 &o)
    : f00(o.f00), f04(o.f04), f08(o.f08), f0C(o.f0C),
      f10(o.f10), f14(o.f14), f18(o.f18), f1C(o.f1C),
      b20(o.b20), b21(o.b21), b22(o.b22),
      f24(o.f24), f28(o.f28), f2C(o.f2C), f30(o.f30)
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmePod52@@QAE@ABU0@@Z=??0Rva001DD0A0@@QAE@ABU0@@Z")
