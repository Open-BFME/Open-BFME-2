// ?rva005F9053@Rva005F8FEE@@QAEXPBD@Z
// partial score=0.5 date=2026-10-10
// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005F8FEE@@UAE@XZ @0x005F8FEE 101B: virtual dtor with derived vtable 0x00879D20 then base 0x007C6F20. Evidence: EH_prolog scopetable 0x007A5AC0; callees rowed ReleaseTreeHintRef 0x0007DEEF twice plus Rva0052413E dtor 0x0052413E plus releaseBuffer 0x00036410 via AsciiString; callers 0x005F9431 thunk 0x005FA141; siblings Rva005F8FCC Rva005F918D.
#include "ascii_string.h"
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
class Rva0052413E
{
public:
	~Rva0052413E();
private:char names[12];
};
struct Rva005F8FEEHolder
{
	TargetRef00217D4C *m_ptr;
	~Rva005F8FEEHolder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva005F8FEEBase
{
public:
	virtual ~Rva005F8FEEBase() {}
};
struct TreeHintRef00217D4C {TargetRef00217D4C*ptr;TreeHintRef00217D4C(const TreeHintRef00217D4C&r):ptr(r.ptr){if(ptr)++ptr->references;}TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);~TreeHintRef00217D4C(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
class Rva005F8FEE : public Rva005F8FEEBase
{
public:
	virtual ~Rva005F8FEE();
	void rva005F9053(const char*);
private:
	int m_04;
	int m_08;
	AsciiString m_str0C;
	int m_10;
	int m_14;
	Rva005F8FEEHolder m_holder18;
	Rva0052413E m_vec1C;
	int m_28;
	TreeHintRef00217D4C m_holder2C;
};
Rva005F8FEE::~Rva005F8FEE()
{
}

// Native 005F9053: loaded28/replacement2C guard, held factory18,
// SkipLevelN/path string and LevelIndexFromTarget, then owning reference
// assignment and clear. Factory type relationship remains neutral.
class Rva005FEAAFHost {public:TreeHintRef00217D4C create(int,const AsciiString&);};
namespace AptUtils {const char*SkipLevelN(const char*);int LevelIndexFromTarget(const char*);}
class Rva002BED91 {public:void clear();};
void Rva005F8FEE::rva005F9053(const char*path){
 if(!m_28&&!m_holder2C.ptr&&m_holder18.m_ptr){
  {AsciiString suffix(AptUtils::SkipLevelN(path));Rva005FEAAFHost*factory=reinterpret_cast<Rva005FEAAFHost*>(m_holder18.m_ptr);m_holder2C=factory->create(AptUtils::LevelIndexFromTarget(path),suffix);}
  reinterpret_cast<Rva002BED91*>(&m_holder18)->clear();m_28=1;
 }
}
