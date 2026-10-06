// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD063@@QAE@XZ @0x001DD1D0 47B
// Default ctor of 32-byte record: f00=-1 with byte zeros and float zeros via movss.
// Evidence: unlock lane no callees; retail or -1 plus movss zeros; caller 0x001DE332; layout matches rowed copy 0x001DD063.
struct Rva001DD063 {
    int f00;
    unsigned char b04;
    unsigned char b05;
    float f08;
    float f0C;
    float f10;
    float f14;
    float f18;
    float f1C;
    Rva001DD063();
};
Rva001DD063::Rva001DD063()
    : f00(-1), b04(0), b05(0), f08(0.0f), f0C(0.0f), f10(0.0f), f14(0.0f), f18(0.0f), f1C(0.0f)
{
}
