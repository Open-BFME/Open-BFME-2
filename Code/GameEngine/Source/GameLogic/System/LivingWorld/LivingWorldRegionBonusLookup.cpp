// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
// Retail 0x0020F0EE..0x0020F143, 85 bytes, thiscall RET4.
// Selects the first region rule whose predicate at 0x0020E9D0 accepts
// the territory identifier stored at argument +0x12C. Pointer-vector
// boundaries +0x5C/+0x60 and the predicate ABI are retail evidence.
// Caller 0x003F1660 uses the selected rule's translated label and bonus.
// Original owner/method names remain unknown. CreateAHeroData* is the
// established predicate's word-sized storage view, not a claimed identity
// for the region identifier. No donor layout is asserted here.
class CreateAHeroData;

class Rva0020E9D0
{
public:
	bool rva0020E9D0(CreateAHeroData *);
};

class Rva0020F0EEArg
{
public:
	char m_pad[0x12c];
	CreateAHeroData *m_ptr12c;
};

class Rva0020F0EE
{
public:
	Rva0020E9D0 *rva0020F0EE(Rva0020F0EEArg *arg);

private:
	char m_pad[0x5c];
	_STL::vector<Rva0020E9D0*> m_vec;
};

Rva0020E9D0 *Rva0020F0EE::rva0020F0EE(Rva0020F0EEArg *arg)
{
    unsigned int index = 0;
    if (m_vec.size() > index) {
        CreateAHeroData *key = arg->m_ptr12c;
        Rva0020E9D0 **cursor = m_vec.begin();
        do {
            Rva0020E9D0 *element = *cursor;
            if (element->rva0020E9D0(key))
                return element;
            ++index;
            ++cursor;
        } while (index < m_vec.size());
    }
    return 0;
}
