// cl: /MD
//
// ?Rva0052CEF6Clear@@YAXPAVRva004E366E@@0@Z retail 0x0052CEF6 25B
// Evidence: unlock lane; callee rva004E366E 0x004E366E; unblocks 0x0052D20C 0x0056614D; prev vector Pod40 next ConstIntGetters4; range destroy step 0xC.
class Rva004E366E
{
public:
	void rva004E366E();
private:
	char m_pad[12];
};
void __cdecl Rva0052CEF6Clear(Rva004E366E *first, Rva004E366E *last)
{
	for (; first != last; ++first)
		first->rva004E366E();
}
