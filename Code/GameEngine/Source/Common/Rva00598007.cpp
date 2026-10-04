// cl: /O1 /MD
// ?rva00598007@Rva00598007@@QAEPAURva002A8AB1Record@@XZ @0x00598007 15B
// Evidence: leaf lookup via global and rowed Rva002A8F24 rva002A8AB1 on member at +0x30; ready caller 0x00598CBC uses eax as pointer plus 0x160.
struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva00598007
{
public:
	Rva002A8AB1Record *rva00598007();
private:
	char _pad[0x30];
	void *m_30;
};

Rva002A8AB1Record *Rva00598007::rva00598007()
{
	Rva002A8AB1Record *p = g_00DFEEF8->rva002A8AB1(m_30);
	return p;
}
