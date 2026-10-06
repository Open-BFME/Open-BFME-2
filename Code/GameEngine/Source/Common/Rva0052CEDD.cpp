// cl: /MD
//
// ?Rva0052CEDDClear@@YAXPAVRva004E1A04@@0@Z retail 0x0052CEDD 25B
// Evidence: chain lane; callee dtor 0x004E1A04 rowed in Rva004E1A04Dtor.cpp;
// callers at 0x0052D1E7/0x00566137; unblocks 0x0052D1CD/63 and 0x0056612F/30;
// prev vector Pod40 next Rva0052CEF6Clear; range destroy step 0x10.
class Rva004E1A04
{
public:
	~Rva004E1A04();
private:
	char m_pad[16];
};
void __cdecl Rva0052CEDDClear(Rva004E1A04 *first, Rva004E1A04 *last)
{
	for (; first != last; ++first)
		first->~Rva004E1A04();
}
