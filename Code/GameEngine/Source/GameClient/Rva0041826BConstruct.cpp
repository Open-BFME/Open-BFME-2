// cl: /Ob2 /EHsc /MD
// ?Rva0041826BConstruct@@YAXPAVRva004181F5@@PBV1@@Z @0x0041826B 45B
// Placement-new copy via rowed copy 0x004181F5 with EH state and null check
// from new expression. Takes dst plus src pointers (cdecl, caller cleans).
// Evidence: chain lane after landing 0x004181F5; caller 0x004182D3 allocates
// 0x20 then constructs at +4; unblocks 0x004182D3.
#include <new>
class Rva004181F5 {
public:
    Rva004181F5(const Rva004181F5 &other);
private:
    char m_pad[0x1c];
};
void __cdecl Rva0041826BConstruct(Rva004181F5 *dst, const Rva004181F5 *src)
{
    new (dst) Rva004181F5(*src);
}
