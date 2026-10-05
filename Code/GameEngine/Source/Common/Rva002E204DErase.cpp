// cl: /O1
// ?rva002E204D@Rva002E204D@@QAEPAVRva002E0D93@@PAV2@@Z @0x002E204D 61B: erase pos from 216B Rva002E0D93 array via rowed copy 0x002E1E9A then pin dtor 0x001EB63C; callers 0x002E2279 0x0037EEF0.
class Rva002E0D93
{
public:
	char m_pad[0xD8];
};
Rva002E0D93 *Rva002E1E9ACopy(Rva002E0D93 *src, Rva002E0D93 *srcEnd, Rva002E0D93 *dst, char *tmp);
class Rva001EB63C
{
public:
	~Rva001EB63C();
};
class Rva002E204D
{
public:
	Rva002E0D93 *rva002E204D(Rva002E0D93 *pos);
private:
	Rva002E0D93 *m_start00;
	Rva002E0D93 *m_finish04;
	Rva002E0D93 *m_end08;
};
Rva002E0D93 *Rva002E204D::rva002E204D(Rva002E0D93 *pos)
{
	Rva002E0D93 *finish = m_finish04;
	Rva002E0D93 *next = pos + 1;
	if (next != finish) {
		char tmp;
		Rva002E1E9ACopy(next, finish, pos, &tmp);
	}
	--m_finish04;
	((Rva001EB63C *)m_finish04)->Rva001EB63C::~Rva001EB63C();
	return pos;
}
