// cl: /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
//
// Three related non-polymorphic ctors, 69B each, differing only in the final
// member-init call (and the EH funclet id):
//   ??0Rva00540B03@@QAE@XZ @0x00540B03 -> rva00540A26 @0x00540A26
//   ??0Rva00542225@@QAE@XZ @0x00542225 -> rva00542067 @0x00542067
//   ??0Rva005422CF@@QAE@XZ @0x005422CF -> rva00542148 @0x00542148
// Each builds the Rva00330757Member head (+0, via rowed 0x00330757), the
// typed key vector (+0x10, with the native three-pointer constructor), zeroes
// +0x1c, then runs its own no-arg init (declared here, pinned in
// reverse/symbols.csv; identity unproven). Same member-EH idiom as the landed
// Rva00526275Ctor.cpp / Rva0033076E bodies: member dtors inline into the
// compiler's funclets, so no dtor rows are needed. Views copy the member TUs.
#include <vector>

#include "../../../Libraries/Include/Lib/Region3D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
// Native reset/read consumers prove 40/28/20-byte key records respectively.
// These are existing ABI-carrier spellings; application frame names remain
// unknown. Their implicit destructors are trivial, unlike the unrelated
// 63-byte vector<BfmeE16> destructor previously declared here.
class Rva0054000B { public: Rva0054000B(); int m_00; private: char m_pad04[0x24]; };
struct Rva00541021 { int m_field0; Region3D m_region; Rva00541021(); Rva00541021(const Rva00541021 &); };
class Rva0054103E { public: int m_field0; Region2D m_region; Rva0054103E(); Rva0054103E(const Rva0054103E &); };

class Rva00330757Member
{
public:
	Rva00330757Member();
	~Rva00330757Member();

private:
	// The rowed listener-head lifetime is external; only its16B extent is used.
	char m_items[12];
	int m_flags;
};

class Rva0054034A { public: void rva00540A26(); };

class Rva00540B03
{
public:
	Rva00540B03();
	void rva00540A26();
private:
	Rva00330757Member m_head;
	_STL::vector<Rva0054000B> m_vec10;
	int m_1C;
};

Rva00540B03::Rva00540B03()
	: m_head(), m_vec10()
{
	m_1C = 0;
	reinterpret_cast<Rva0054034A *>(this)->rva00540A26();
}

class Rva00542225
{
public:
	Rva00542225();
	void rva00542067();
private:
	Rva00330757Member m_head;
	_STL::vector<Rva00541021> m_vec10;
	int m_1C;
};

Rva00542225::Rva00542225()
	: m_head(), m_vec10()
{
	m_1C = 0;
	rva00542067();
}

class Rva005422CF
{
public:
	Rva005422CF();
	void rva00542148();
private:
	Rva00330757Member m_head;
	_STL::vector<Rva0054103E> m_vec10;
	int m_1C;
};

Rva005422CF::Rva005422CF()
	: m_head(), m_vec10()
{
	m_1C = 0;
	rva00542148();
}
