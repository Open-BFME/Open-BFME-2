// cl: /MD /DNDEBUG
// ?Rva000BDD08Destroy@@YAXPAVRva000B9AAA@@0@Z @0x000BDD08 25B
// Array-destroy range over Rva000B9AAA (stride 0x18).
// Evidence: retail push esi loop calls rowed ??1Rva000B9AAA@@QAE@XZ
// @0x000B9AAA then add esi 0x18; callers @0x000C1BFB @0x000C1CCD
// @0x000C206F @0x000C2141; same recipe as rowed Rva000BDCEFDestroy
// @0x000BDCEF and Rva0032AF56Destroy @0x0032AF56.
class Rva000B9AAA
{
public:
	~Rva000B9AAA();

	char m_pad[0x18];
};

void Rva000BDD08Destroy(Rva000B9AAA *first, Rva000B9AAA *last)
{
	for (; first != last; ++first)
		first->~Rva000B9AAA();
}
