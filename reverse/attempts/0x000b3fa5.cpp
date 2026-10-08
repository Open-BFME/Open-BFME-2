// ?rva000B3FA5@WeaponTemplateSetHead@@QAEXHH@Z
// partial score=0.6 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc
class WeaponTemplateSetHead {
public:
    unsigned words[19];
    void rva000B3FA5(int index, int value);
};
void WeaponTemplateSetHead::rva000B3FA5(int index,int value)
{
    unsigned mask=1u << (index & 31);
    words[index >> 5] ^= ((unsigned)-value ^ words[index >> 5]) & mask;
}
