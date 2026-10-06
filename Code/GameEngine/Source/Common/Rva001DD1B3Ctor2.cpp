// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD1B3@@QAE@ABHABURva001DD063@@@Z @0x001DD2BF 29B
// Two-arg ctor of 36-byte record: int head plus Rva001DD063 tail at +4.
// Evidence: chain lane every callee rowed; retail copies [eax] then calls rowed 0x001DD063 with this+4 and returns this; caller 0x001DE3A5.
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
    Rva001DD1B3(const int &key, const Rva001DD063 &tail);
};
Rva001DD1B3::Rva001DD1B3(const int &key, const Rva001DD063 &tail)
    : f00(key), f04(tail)
{
}
