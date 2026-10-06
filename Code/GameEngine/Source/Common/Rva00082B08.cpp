// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00082B08@Rva00082B08@@QAEXXZ @0x00082B08 127B: triple conditional Rva002B7250 erase plus two vector range erases plus conditional tail to Rva000FE001 move drain. Evidence: three Rva002B7250 row calls plus two 0x819EC vector erase row calls plus tail jmp to 0xFE188 row plus caller 0x91CF2.
#include <vector>
class CreateAHeroData { public: void *m_p; };
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct TreeHintRef00217D4C { char m_pad[4]; };
class Rva000FE001
{
public:
	void rva000FE188();
};
class Rva00082B08
{
public:
	void rva00082B08();
private:
	char m_pad0[0xc8];
	CreateAHeroData m_aC8;
	CreateAHeroData m_bCC;
	CreateAHeroData m_cD0;
	char m_pad1[0x100 - 0xd4];
	Rva000FE001 *m_fe100;
	Rva002B7250 *m_p104;
	_STL::vector<TreeHintRef00217D4C> m_v108;
	Rva002B7250 *m_p114;
	_STL::vector<TreeHintRef00217D4C> m_v118;
	Rva002B7250 *m_p124;
};
void Rva00082B08::rva00082B08()
{
	if (m_p104) {
		m_p104->rva002B7250(&m_aC8);
		m_p104 = 0;
		m_p114->rva002B7250(&m_bCC);
		m_p114 = 0;
		m_p124->rva002B7250(&m_cD0);
		m_p124 = 0;
	}
	_STL::vector<TreeHintRef00217D4C> *pV0 = &m_v108;
	pV0->erase(pV0->begin(), pV0->end());
	_STL::vector<TreeHintRef00217D4C> *pV1 = &m_v118;
	pV1->erase(pV1->begin(), pV1->end());
	if (m_fe100)
		m_fe100->rva000FE188();
}
