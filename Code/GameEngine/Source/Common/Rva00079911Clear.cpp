// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00079911@Rva00079911@@QAEXXZ @0x00079911 116B via vector pair clear with ref release plus list clear
// Evidence: thiscall ret0 tail jmp to List_base<string> clear; two vector<void*> erases; and [ecx+0x310],0 plus dec [ecx+4] release and virtual slot 0xec call; caller 0x0007A54B
#include <list>
#include <vector>
#include <string>

class Rva00079911Item
{
public:
	virtual void Delete();
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
	virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
	virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56();
	virtual void v57(); virtual void v58();
	virtual void FuncEC(int x);
	int m_ref;
	char m_pad[0x310 - 8];
	int m_310;
};

class Rva00079911
{
public:
	void rva00079911();
private:
	char m_pad00[0xc];
	_STL::list<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > m_list;
	_STL::vector<void *> m_vec1;
	_STL::vector<void *> m_vec2;
};

void Rva00079911::rva00079911()
{
	for (void **it = m_vec1.begin(); it != m_vec1.end(); ++it) {
		Rva00079911Item *p = (Rva00079911Item *)*it;
		p->m_310 = 0;
		if (--p->m_ref == 0)
			p->Delete();
	}
	for (void **it = m_vec2.begin(); it != m_vec2.end(); ++it) {
		Rva00079911Item *p = (Rva00079911Item *)*it;
		p->FuncEC(0);
		if (--p->m_ref == 0)
			p->Delete();
	}
	_STL::vector<void *> &v1 = m_vec1;
	v1.erase(v1.begin(), v1.end());
	_STL::vector<void *> &v2 = m_vec2;
	v2.erase(v2.begin(), v2.end());
	m_list.clear();
}
