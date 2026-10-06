// cl: /MD
struct Rva0028F2F8Aux
{
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
};
class CreateAHeroManager
{
public:
	void *rva002197A6(int v);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Object
{
public:
	void *getDisplayName();
private:
	unsigned char m_pad[4];
	Rva0028F2F8Aux *m_04;
	unsigned char m_pad2[0x74 - 0x8];
	int m_74;
};
// ?getDisplayName@Object@@QAEPAXXZ
void *Object::getDisplayName()
{
	if ((m_04->m_11F & 0x40) != 0)
	{
		void *r = TheCreateAHeroManager->rva002197A6(m_74);
		if (r == 0)
			return (char *)m_04 + 0x30;
		return (char *)r + 8;
	}
	return (char *)m_04 + 0x30;
}
