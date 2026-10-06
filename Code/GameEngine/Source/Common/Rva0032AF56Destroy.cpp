// cl: /DNDEBUG /MD
// ?Rva0032AF56Destroy@@YAXPAVRva00329D0E@@0@Z @0x0032AF56 25B
// Array-destroy range over Rva00329D0E (size 0x10).
// Evidence: retail push esi loop calls rowed ??1Rva00329D0E@@QAE@XZ
// @0x00329D0E then add esi 0x10 cmp to second arg; callers @0x0032C3BD
// @0x0032C4DD; chain lane after landing the ??1.
class Rva00329D0E
{
public:
	~Rva00329D0E();

	char m_pad[0x10];
};

void Rva0032AF56Destroy(Rva00329D0E *first, Rva00329D0E *last)
{
	for (; first != last; ++first)
		first->~Rva00329D0E();
}
