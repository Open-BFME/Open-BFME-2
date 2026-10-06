// cl: /Oy- /DNDEBUG /MD /EHsc
// stlport
// ?rva0025BF8C@Rva0025BF8C@@QAE_NPAX@Z, retail 0x0025BF8C, 59 bytes.
// Vector find-and-erase returning bool: loads CreateAHeroData* at arg+0x74 into
// a stack temp (mov eax,[ebp+8]; mov eax,[eax+0x74]; mov [ebp+8],eax), finds it
// in the vector<CreateAHeroData*> at this+4 via rowed find at 0x0020E873, erases
// via rowed erase at 0x0025BF5D when present, returns 1 else 0 (mov al,1 / xor al).
// Callers (4 at 0x005960F1 etc.) pass a holder with hero at +0x74; unblocks 4.
// Prev is VectorObjectIDFillInsert, next is Rva0025BFE3 ctor; EBP frame needs /Oy-.
#include <vector>
class CreateAHeroData;
class Rva0025BF8C
{
public:
	bool rva0025BF8C(void *arg);
private:
	char m_pad[4];
	_STL::vector<CreateAHeroData *> m_vec04;
};
bool Rva0025BF8C::rva0025BF8C(void *arg)
{
	CreateAHeroData *hero = *(CreateAHeroData **)((char *)arg + 0x74);
	_STL::vector<CreateAHeroData *>::iterator it =
		_STL::find(m_vec04.begin(), m_vec04.end(), hero);
	if (it != m_vec04.end()) {
		m_vec04.erase(it);
		return true;
	}
	return false;
}
// ?UnRegister@AIStructureStats@@QAE_NPAX@Z @0x00596548 93B
// __thiscall over holder arg: requires Rva005964ECGet(holder)!=0 (byte test),
// then if inner(+4)[0x123]&1 finds hero(+0x74) in derived vector at this+0x10
// via rowed find and erases via rowed erase when present, else calls base
// Rva0025BF8C::rva0025BF8C(holder). Returns true in both push paths, false
// when predicate fails. Base size 0x10, derived vector at +0x10.
// Evidence: push edi mov esi ecx call 0x5964EC test al je; mov eax[edi+4]
// test [eax+123]1 je to base call else find 0x20E873 erase 0x25BF5D; caller
// at 0x004E0458; EBP frame /Oy- with stlport like base.
int __stdcall Rva005964ECGet(void *holder);
class AIStructureStats : public Rva0025BF8C
{
public:
	bool UnRegister(void *holder);
private:
	_STL::vector<CreateAHeroData *> m_vec10;
};
bool AIStructureStats::UnRegister(void *holder)
{
	if (((unsigned char)Rva005964ECGet(holder)) != 0)
	{
		void *inner = *(void **)((char *)holder + 4);
		if ((((unsigned char *)inner)[0x123] & 1) != 0)
		{
			CreateAHeroData *hero = *(CreateAHeroData **)((char *)holder + 0x74);
			_STL::vector<CreateAHeroData *>::iterator it =
				_STL::find(m_vec10.begin(), m_vec10.end(), hero);
			if (it != m_vec10.end())
			{
				m_vec10.erase(it);
			}
		}
		else
		{
			Rva0025BF8C::rva0025BF8C(holder);
		}
		return true;
	}
	return false;
}
