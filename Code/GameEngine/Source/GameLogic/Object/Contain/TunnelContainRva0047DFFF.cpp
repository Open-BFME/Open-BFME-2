// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047DFFF, 16 bytes, RET.
// Shape: this is kept in esi across one member call (0x00464120, address-derived
// name: its only evidence is the __thiscall with ecx = this), then the last
// statement tail-jumps into TunnelContain::rva0047DF81 (0x0047DF81, matched in
// TunnelContainRva0047DF81.cpp). The owner is inferred from the tail callee and
// the file neighbours; the class name is not otherwise established.
class TunnelContain
{
public:
 void rva0047DFFF();
 void rva00464120();
 void rva0047DF81();
};
void TunnelContain::rva0047DFFF()
{
 rva00464120();
 rva0047DF81();
}
