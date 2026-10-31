// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Five-byte bodies from unrowed .text gaps that are a bare tail jump to a
// rowed member on the same receiver (or a derived-class destructor jumping
// to its rowed base destructor). Each callee keeps its ledger spelling; the
// forwarding owners are not recovered and are address-named.

class AsciiString;
class Object;
enum NameKeyType { };
class WeaponTemplate;

class Rva001F050B
{
public:
	void rva001F050B();
};

class Rva001F425C
{
public:
	void call();
};

class Rva001F4276
{
public:
	void call(int, int);
};

class Rva001F429A
{
public:
	void call();
};

class Rva001F42BA
{
public:
	void call(int);
};

class Rva001F43BD
{
public:
	void rva001F43BD(void *);
};

class Rva001F5CF7
{
public:
	void rva001F5CF7();
};

class Rva001F5D4F
{
public:
	void rva001F5D4F(int);
};

class H1F8167
{
public:
	~H1F8167();
};

class Rva001F8E45
{
public:
	void rva001F8E45(void *, void *);
};

class Rva005C9D30
{
public:
	~Rva005C9D30();
};

class Rva001FA529
{
public:
	void rva001FA529(void *, void *);
};

class Rva001EAF7B
{
public:
	bool rva001EAF7B();
};

class Rva00204136
{
public:
	void rva00204984();
	~Rva00204136();
};

class Rva00206593
{
public:
	void rva00206EC7();
};

class Rva0021030E
{
public:
	~Rva0021030E();
};

class Rva0021DB35
{
public:
	~Rva0021DB35();
};

class Rva00223591
{
public:
	int rva00223736(const AsciiString *);
	void rva0022380B();
};

class Rva00226856
{
public:
	~Rva00226856();
};

class Rva002268B0
{
public:
	~Rva002268B0();
};

class Rva0022DB29
{
public:
	~Rva0022DB29();
};

class Rva0022DD19
{
public:
	~Rva0022DD19();
};

class Rva0022DD62
{
public:
	~Rva0022DD62();
};

class Rva0022DDAB
{
public:
	~Rva0022DDAB();
};

class Rva0039B20C
{
public:
	void rva0039B227(int);
	void rva0039B246();
};

// _STL::_List_base<Rva0024076D>, dtor rowed at 0x002461DA (StlportListRva002461DA.cpp).
class Rva0024076D;
namespace _STL
{
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class _List_base
{
public:
	~_List_base();
};
}
typedef _STL::_List_base<Rva0024076D, _STL::allocator<Rva0024076D> > Rva0024076DListBase;

class Rva00255CA8
{
public:
	void rva00255CA8();
};

class Rva0028614C
{
public:
	void rva0028662D();
};

class Rva0028881C
{
public:
	void rva002889BB();
};

class Rva00289371HashTable
{
public:
	void clear();
};

class Rva002913EB
{
public:
	void rva002913EB();
};

class Rva0029A407
{
public:
	void rva0029A407();
};

class Rva0029B63A
{
public:
	void rva0029E015();
};

class Rva002A1D02
{
public:
	void clear();
};

class Rva002A8FE0
{
public:
	void rva002A8FE0();
};

class Rva001FD42B
{
public:
	void rva001FD630();
};

class Rva001FD458
{
public:
	void rva001FD659();
};

class Rva002B54F9
{
public:
	void rva002B54F9();
};

class Rva002B5522
{
public:
	void rva002B5522();
};

class Rva002BF75A
{
public:
	void rva002BF7BE();
};

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *);
	int rva00223429(const AsciiString *);
	void rva00212858(unsigned int);
	void rva003A2A41();
};

class Rva002E15E6
{
public:
	void rva002E15E6();
};

class GameTextTable
{
public:
	~GameTextTable();
};

class Rva002EE9B7
{
public:
	void rva002EE9B7();
};

class Out
{
public:
	~Out();
};

class Rva002CF7B5
{
public:
	void rva002CF7B5();
};

class Rva002CF7DE
{
public:
	void rva002CF7DE();
};

class Rva002D02FD
{
public:
	void rva002D02FD();
};

// 0x001F0652 (5B): tail jump to the rowed Rva001F050B::rva001F050B 0x001F050B on the same receiver.
class Rva001F0652
{
public:
	void rva001F0652();
};
void Rva001F0652::rva001F0652()
{
	((Rva001F050B *)this)->rva001F050B();
}

// 0x001F495A (5B): tail jump to the rowed Rva001F425C::call 0x001F425C on the same receiver.
class Rva001F495A
{
public:
	void rva001F495A();
};
void Rva001F495A::rva001F495A()
{
	((Rva001F425C *)this)->call();
}

// 0x001F495F (5B): tail jump to the rowed Rva001F4276::call 0x001F4276 on the same receiver.
class Rva001F495F
{
public:
	void rva001F495F(int a, int b);
};
void Rva001F495F::rva001F495F(int a, int b)
{
	((Rva001F4276 *)this)->call(a, b);
}

// 0x001F4964 (5B): tail jump to the rowed Rva001F429A::call 0x001F429A on the same receiver.
class Rva001F4964
{
public:
	void rva001F4964();
};
void Rva001F4964::rva001F4964()
{
	((Rva001F429A *)this)->call();
}

// 0x001F4969 (5B): tail jump to the rowed Rva001F42BA::call 0x001F42BA on the same receiver.
class Rva001F4969
{
public:
	void rva001F4969(int a);
};
void Rva001F4969::rva001F4969(int a)
{
	((Rva001F42BA *)this)->call(a);
}

// 0x001F4A0D (5B): tail jump to the rowed Rva001F43BD::rva001F43BD 0x001F43BD on the same receiver.
class Rva001F4A0D
{
public:
	void rva001F4A0D(void *a);
};
void Rva001F4A0D::rva001F4A0D(void *a)
{
	((Rva001F43BD *)this)->rva001F43BD(a);
}

// 0x001F6488 (5B): tail jump to the rowed Rva001F5CF7::rva001F5CF7 0x001F5CF7 on the same receiver.
class Rva001F6488
{
public:
	void rva001F6488();
};
void Rva001F6488::rva001F6488()
{
	((Rva001F5CF7 *)this)->rva001F5CF7();
}

// 0x001F648D (5B): tail jump to the rowed Rva001F5D4F::rva001F5D4F 0x001F5D4F on the same receiver.
class Rva001F648D
{
public:
	void rva001F648D(int a);
};
void Rva001F648D::rva001F648D(int a)
{
	((Rva001F5D4F *)this)->rva001F5D4F(a);
}

// 0x001F8BE3 (5B): tail jump to the rowed H1F8167 destructor 0x001F8167.
class Rva001F8BE3 : public H1F8167
{
public:
	~Rva001F8BE3();
};
Rva001F8BE3::~Rva001F8BE3()
{
}

// 0x001F9487 (5B): tail jump to the rowed Rva001F8E45::rva001F8E45 0x001F8E45 on the same receiver.
class Rva001F9487
{
public:
	void rva001F9487(void *a, void *b);
};
void Rva001F9487::rva001F9487(void *a, void *b)
{
	((Rva001F8E45 *)this)->rva001F8E45(a, b);
}

// 0x001F9B64 (5B): tail jump to the rowed Rva005C9D30 destructor 0x001F9025.
class Rva001F9B64 : public Rva005C9D30
{
public:
	~Rva001F9B64();
};
Rva001F9B64::~Rva001F9B64()
{
}

// 0x001FA831 (5B): tail jump to the rowed Rva001FA529::rva001FA529 0x001FA529 on the same receiver.
class Rva001FA831
{
public:
	void rva001FA831(void *a, void *b);
};
void Rva001FA831::rva001FA831(void *a, void *b)
{
	((Rva001FA529 *)this)->rva001FA529(a, b);
}

// 0x001FF5A7 (5B): tail jump to the rowed Rva001EAF7B::rva001EAF7B 0x001EAF7B on the same receiver.
class Rva001FF5A7
{
public:
	bool rva001FF5A7();
};
bool Rva001FF5A7::rva001FF5A7()
{
	return ((Rva001EAF7B *)this)->rva001EAF7B();
}

// 0x002055DF (5B): tail jump to the rowed Rva00204136::rva00204984 0x00204984 on the same receiver.
class Rva002055DF
{
public:
	void rva002055DF();
};
void Rva002055DF::rva002055DF()
{
	((Rva00204136 *)this)->rva00204984();
}

// 0x00205AF8 (5B): tail jump to the rowed Rva00204136 destructor 0x002055E4.
class Rva00205AF8 : public Rva00204136
{
public:
	~Rva00205AF8();
};
Rva00205AF8::~Rva00205AF8()
{
}

// 0x002075EE (5B): tail jump to the rowed Rva00206593::rva00206EC7 0x00206EC7 on the same receiver.
class Rva002075EE
{
public:
	void rva002075EE();
};
void Rva002075EE::rva002075EE()
{
	((Rva00206593 *)this)->rva00206EC7();
}

// 0x0021038B (5B): tail jump to the rowed Rva0021030E destructor 0x0021030E.
class Rva0021038B : public Rva0021030E
{
public:
	~Rva0021038B();
};
Rva0021038B::~Rva0021038B()
{
}

// 0x0021DE70 (5B): tail jump to the rowed Rva0021DB35 destructor 0x0021DB35.
class Rva0021DE70 : public Rva0021DB35
{
public:
	~Rva0021DE70();
};
Rva0021DE70::~Rva0021DE70()
{
}

// 0x00223FEC (5B): tail jump to the rowed Rva00223591::rva0022380B 0x0022380B on the same receiver.
class Rva00223FEC
{
public:
	void rva00223FEC();
};
void Rva00223FEC::rva00223FEC()
{
	((Rva00223591 *)this)->rva0022380B();
}

// 0x0022CA36 (5B): tail jump to the rowed Rva00226856 destructor 0x0022C5DA.
class Rva0022CA36 : public Rva00226856
{
public:
	~Rva0022CA36();
};
Rva0022CA36::~Rva0022CA36()
{
}

// 0x0022CA40 (5B): tail jump to the rowed Rva002268B0 destructor 0x0022C64A.
class Rva0022CA40 : public Rva002268B0
{
public:
	~Rva0022CA40();
};
Rva0022CA40::~Rva0022CA40()
{
}

// 0x0022DE29 (5B): tail jump to the rowed Rva0022DB29 destructor 0x0022DC62.
class Rva0022DE29 : public Rva0022DB29
{
public:
	~Rva0022DE29();
};
Rva0022DE29::~Rva0022DE29()
{
}

// 0x0022DF6F (5B): tail jump to the rowed Rva0022DD19 destructor 0x0022DEA8.
class Rva0022DF6F : public Rva0022DD19
{
public:
	~Rva0022DF6F();
};
Rva0022DF6F::~Rva0022DF6F()
{
}

// 0x0022DF74 (5B): tail jump to the rowed Rva0022DD62 destructor 0x0022DEE1.
class Rva0022DF74 : public Rva0022DD62
{
public:
	~Rva0022DF74();
};
Rva0022DF74::~Rva0022DF74()
{
}

// 0x0022DFCC (5B): tail jump to the rowed Rva0022DDAB destructor 0x0022DF1A.
class Rva0022DFCC : public Rva0022DDAB
{
public:
	~Rva0022DFCC();
};
Rva0022DFCC::~Rva0022DFCC()
{
}

// 0x0023C624 (5B): tail jump to the rowed Rva0039B20C::rva0039B227 0x0039B227 on the same receiver.
class Rva0023C624
{
public:
	void rva0023C624(int a);
};
void Rva0023C624::rva0023C624(int a)
{
	((Rva0039B20C *)this)->rva0039B227(a);
}

// 0x00247084 (5B): tail jump to the rowed _List_base<Rva0024076D> dtor 0x002461DA on the same receiver.
class Rva00247084
{
public:
	void rva00247084();
};
void Rva00247084::rva00247084()
{
	((Rva0024076DListBase *)this)->~Rva0024076DListBase();
}

// 0x00256424 (5B): tail jump to the rowed Rva00255CA8::rva00255CA8 0x00255CA8 on the same receiver.
class Rva00256424
{
public:
	void rva00256424();
};
void Rva00256424::rva00256424()
{
	((Rva00255CA8 *)this)->rva00255CA8();
}

// 0x00286815 (5B): tail jump to the rowed Rva0028614C::rva0028662D 0x0028662D on the same receiver.
class Rva00286815
{
public:
	void rva00286815();
};
void Rva00286815::rva00286815()
{
	((Rva0028614C *)this)->rva0028662D();
}

// 0x002885FA (5B): tail jump to the rowed Rva0039B20C::rva0039B246 0x0039B246 on the same receiver.
class Rva002885FA
{
public:
	void rva002885FA();
};
void Rva002885FA::rva002885FA()
{
	((Rva0039B20C *)this)->rva0039B246();
}

// 0x00288B4C (5B): tail jump to the rowed Rva0028881C::rva002889BB 0x002889BB on the same receiver.
class Rva00288B4C
{
public:
	void rva00288B4C();
};
void Rva00288B4C::rva00288B4C()
{
	((Rva0028881C *)this)->rva002889BB();
}

// 0x002895BA (5B): tail jump to the rowed Rva00289371HashTable::clear 0x00289371 on the same receiver.
class Rva002895BA
{
public:
	void rva002895BA();
};
void Rva002895BA::rva002895BA()
{
	((Rva00289371HashTable *)this)->clear();
}

// 0x002923A2 (5B): tail jump to the rowed Rva002913EB::rva002913EB 0x002913EB on the same receiver.
class Rva002923A2
{
public:
	void rva002923A2();
};
void Rva002923A2::rva002923A2()
{
	((Rva002913EB *)this)->rva002913EB();
}

// 0x0029B346 (5B): tail jump to the rowed Rva0029A407::rva0029A407 0x0029A407 on the same receiver.
class Rva0029B346
{
public:
	void rva0029B346();
};
void Rva0029B346::rva0029B346()
{
	((Rva0029A407 *)this)->rva0029A407();
}

// 0x0029FAB2 (5B): tail jump to the rowed Rva0029B63A::rva0029E015 0x0029E015 on the same receiver.
class Rva0029FAB2
{
public:
	void rva0029FAB2();
};
void Rva0029FAB2::rva0029FAB2()
{
	((Rva0029B63A *)this)->rva0029E015();
}

// 0x002A404D (5B): tail jump to the rowed Rva002A1D02::clear 0x002A1D02 on the same receiver.
class Rva002A404D
{
public:
	void rva002A404D();
};
void Rva002A404D::rva002A404D()
{
	((Rva002A1D02 *)this)->clear();
}

// 0x002A91D8 (5B): tail jump to the rowed Rva002A8FE0::rva002A8FE0 0x002A8FE0 on the same receiver.
class Rva002A91D8
{
public:
	void rva002A91D8();
};
void Rva002A91D8::rva002A91D8()
{
	((Rva002A8FE0 *)this)->rva002A8FE0();
}

// 0x002ABFFD (5B): tail jump to the rowed Rva001FD42B::rva001FD630 0x001FD630 on the same receiver.
class Rva002ABFFD
{
public:
	void rva002ABFFD();
};
void Rva002ABFFD::rva002ABFFD()
{
	((Rva001FD42B *)this)->rva001FD630();
}

// 0x002AC002 (5B): tail jump to the rowed Rva001FD458::rva001FD659 0x001FD659 on the same receiver.
class Rva002AC002
{
public:
	void rva002AC002();
};
void Rva002AC002::rva002AC002()
{
	((Rva001FD458 *)this)->rva001FD659();
}

// 0x002B5FEC (5B): tail jump to the rowed Rva002B54F9::rva002B54F9 0x002B54F9 on the same receiver.
class Rva002B5FEC
{
public:
	void rva002B5FEC();
};
void Rva002B5FEC::rva002B5FEC()
{
	((Rva002B54F9 *)this)->rva002B54F9();
}

// 0x002B6029 (5B): tail jump to the rowed Rva002B5522::rva002B5522 0x002B5522 on the same receiver.
class Rva002B6029
{
public:
	void rva002B6029();
};
void Rva002B6029::rva002B6029()
{
	((Rva002B5522 *)this)->rva002B5522();
}

// 0x002BFA48 (5B): tail jump to the rowed Rva002BF75A::rva002BF7BE 0x002BF7BE on the same receiver.
class Rva002BFA48
{
public:
	void rva002BFA48();
};
void Rva002BFA48::rva002BFA48()
{
	((Rva002BF75A *)this)->rva002BF7BE();
}

// 0x002CFF23 (5B): tail jump to the rowed Rva000427195::rva003A2A41 0x003A2A41 on the same receiver.
class Rva002CFF23
{
public:
	void rva002CFF23();
};
void Rva002CFF23::rva002CFF23()
{
	((Rva000427195 *)this)->rva003A2A41();
}

// 0x002CFF28 (5B): tail jump to the rowed Rva000427195::rva00212858 0x00212858 on the same receiver.
class Rva002CFF28
{
public:
	void rva002CFF28(unsigned int a);
};
void Rva002CFF28::rva002CFF28(unsigned int a)
{
	((Rva000427195 *)this)->rva00212858(a);
}

// 0x002E1E14 (5B): tail jump to the rowed Rva002E15E6::rva002E15E6 0x002E15E6 on the same receiver.
class Rva002E1E14
{
public:
	void rva002E1E14();
};
void Rva002E1E14::rva002E1E14()
{
	((Rva002E15E6 *)this)->rva002E15E6();
}

// 0x002E6324 (5B): tail jump to the rowed GameTextTable destructor 0x002E6158.
class Rva002E6324 : public GameTextTable
{
public:
	~Rva002E6324();
};
Rva002E6324::~Rva002E6324()
{
}

// 0x002F0B4D (5B): tail jump to the rowed Rva002EE9B7::rva002EE9B7 0x002EE9B7 on the same receiver.
class Rva002F0B4D
{
public:
	void rva002F0B4D();
};
void Rva002F0B4D::rva002F0B4D()
{
	((Rva002EE9B7 *)this)->rva002EE9B7();
}

// 0x003291EF (5B): tail jump to the rowed Out destructor 0x00329182.
class Rva003291EF : public Out
{
public:
	~Rva003291EF();
};
Rva003291EF::~Rva003291EF()
{
}

// 0x0033BE6B (5B): tail jump to the rowed Rva002CF7B5::rva002CF7B5 0x002CF7B5 on the same receiver.
class Rva0033BE6B
{
public:
	void rva0033BE6B();
};
void Rva0033BE6B::rva0033BE6B()
{
	((Rva002CF7B5 *)this)->rva002CF7B5();
}

// 0x0033BECC (5B): tail jump to the rowed Rva002CF7DE::rva002CF7DE 0x002CF7DE on the same receiver.
class Rva0033BECC
{
public:
	void rva0033BECC();
};
void Rva0033BECC::rva0033BECC()
{
	((Rva002CF7DE *)this)->rva002CF7DE();
}

// 0x0033D005 (5B): tail jump to the rowed Rva002D02FD::rva002D02FD 0x002D02FD on the same receiver.
class Rva0033D005
{
public:
	void rva0033D005();
};
void Rva0033D005::rva0033D005()
{
	((Rva002D02FD *)this)->rva002D02FD();
}

// ---- thunks over typed callees ----------------------------------------

class Rva001E6516 { public: void rva001E6516(Object *); };
class Rva00077710Value { public: bool operator!=(const Rva00077710Value &) const; };
struct Rva0039B24FInput;
class Rva0039B24F { public: void rva0039B24F(Rva0039B24FInput *, bool, bool); };
class Rva003BD306Target { public: void rva0039B28F(bool); void rva0039B2C7(int, bool); };
#include "../../Include/Common/Overridable.h"
class WeaponStore
{
	friend class Rva002C724E;
protected:
	WeaponTemplate *findWeaponTemplatePrivate(NameKeyType key) const;
};
class FunctionLexicon
{
	friend class Rva00314D11;
public:
	enum TableIndex { };
protected:
	void *findFunction(NameKeyType key, TableIndex index);
};

// 0x001E679E (5B) -> Rva001E6516::rva001E6516 0x001E6516.
class Rva001E679E { public: void rva001E679E(Object *object); };
void Rva001E679E::rva001E679E(Object *object) { ((Rva001E6516 *)this)->rva001E6516(object); }

// 0x00223FE7 (5B) -> Rva00223591::rva00223736 0x00223736.
class Rva00223FE7 { public: int rva00223FE7(const AsciiString *name); };
int Rva00223FE7::rva00223FE7(const AsciiString *name) { return ((Rva00223591 *)this)->rva00223736(name); }

// 0x002CFF1E (5B) -> Rva000427195::rva00223429 0x00223429.
class Rva002CFF1E { public: int rva002CFF1E(const AsciiString *name); };
int Rva002CFF1E::rva002CFF1E(const AsciiString *name) { return ((Rva000427195 *)this)->rva00223429(name); }

// 0x0031BF16 (5B) -> Rva000427195::bucketIndex 0x00223149.
class Rva0031BF16 { public: int rva0031BF16(const AsciiString *name); };
int Rva0031BF16::rva0031BF16(const AsciiString *name) { return ((Rva000427195 *)this)->bucketIndex(name); }

// 0x0022D15B (5B) -> Rva00077710Value::operator!= 0x0022CF4C.
class Rva0022D15B { public: bool rva0022D15B(const Rva00077710Value &other) const; };
bool Rva0022D15B::rva0022D15B(const Rva00077710Value &other) const { return *(const Rva00077710Value *)this != other; }

// 0x00288604 (5B) -> Rva0039B24F::rva0039B24F 0x0039B24F.
class Rva00288604 { public: void rva00288604(Rva0039B24FInput *input, bool a, bool b); };
void Rva00288604::rva00288604(Rva0039B24FInput *input, bool a, bool b) { ((Rva0039B24F *)this)->rva0039B24F(input, a, b); }

// 0x002885FF (5B) -> Rva003BD306Target::rva0039B28F 0x0039B28F.
class Rva002885FF { public: void rva002885FF(bool value); };
void Rva002885FF::rva002885FF(bool value) { ((Rva003BD306Target *)this)->rva0039B28F(value); }

// 0x0028C8C8 (5B) -> Overridable::friend_getFinalOverride 0x00288609.
class Rva0028C8C8 { public: const Overridable *rva0028C8C8() const; };
const Overridable *Rva0028C8C8::rva0028C8C8() const { return ((const Overridable *)this)->friend_getFinalOverride(); }

// 0x002C724E (5B) -> WeaponStore::findWeaponTemplatePrivate 0x002CADBE.
class Rva002C724E { public: WeaponTemplate *rva002C724E(NameKeyType key) const; };
WeaponTemplate *Rva002C724E::rva002C724E(NameKeyType key) const { return ((const WeaponStore *)this)->findWeaponTemplatePrivate(key); }

// 0x00314D11 (5B) -> FunctionLexicon::findFunction 0x002D225F.
class Rva00314D11 { public: void *rva00314D11(NameKeyType key, FunctionLexicon::TableIndex index); };
void *Rva00314D11::rva00314D11(NameKeyType key, FunctionLexicon::TableIndex index) { return ((FunctionLexicon *)this)->findFunction(key, index); }

// ---- third group ---------------------------------------------------------

template <typename T> class StringBase { public: void set(const StringBase<T> &other); };
enum CBCommandStatus { CBC_COMMAND_NOT_USED = 0, CBC_COMMAND_USED = 1 };
enum GadgetGameMessage { GGM_NONE = 0 };
class GameWindow;
class ControlBar
{
protected:
	CBCommandStatus processCommandTransitionUI(GameWindow *control, GadgetGameMessage gadgetMessage);
public:
	CBCommandStatus rva0053B1CF(GameWindow *button, unsigned int gadgetMessage);
	CBCommandStatus processContextSensitiveButtonClick(GameWindow *button, GadgetGameMessage gadgetMessage);
	CBCommandStatus processContextSensitiveButtonTransition(GameWindow *button, GadgetGameMessage gadgetMessage);
};
class ResourceEntryCollector { public: void rva004E551E(); };
struct Rva0030B6A6Range;
struct Rva0030BFE8Range;
int Rva0030B6A6Equal(const Rva0030B6A6Range *a, const Rva0030B6A6Range *b);
int Rva0030BFE8Equal(const Rva0030BFE8Range *a, const Rva0030BFE8Range *b);
class MixFileCreator { public: struct FileInfoStruct; };
void Rva002176A6Swap(MixFileCreator::FileInfoStruct *a, MixFileCreator::FileInfoStruct *b);
class Rva002B2F97;
void Rva002B2FF4Swap(Rva002B2F97 &a, Rva002B2F97 &b);
struct S4SortElem20;
struct S4Cmp002EB8E0 { bool operator()(const S4SortElem20 &a, const S4SortElem20 &b) const; };
class Locomotor;
class Drawable
{
	friend class Rva00278DF9;
public:
	struct PhysicsXformInfo;
protected:
	void calcPhysicsXformWheels(const Locomotor *locomotor, PhysicsXformInfo &info);
};

// 0x001FD2C5 (5B) -> StringBase<char>::set 0x000366F0 on the same receiver.
class Rva001FD2C5 { public: void rva001FD2C5(const StringBase<char> &other); };
void Rva001FD2C5::rva001FD2C5(const StringBase<char> &other) { ((StringBase<char> *)this)->set(other); }

// 0x0031ABCF / 0x0031ABD4 (5B each): the incremental-link entries for
// ControlBar::processContextSensitiveButtonClick and ...Transition (pinned in
// symbols.csv; the GUI system callbacks ControlBarSystem / GeneralsExpPoints
// call these addresses), tail jumps to the bodies 0x0053B1CF and 0x00539997
// (processCommandTransitionUI, as Zero Hour's ...Transition returns).
CBCommandStatus ControlBar::processContextSensitiveButtonClick(GameWindow *button, GadgetGameMessage gadgetMessage)
{
	return rva0053B1CF(button, gadgetMessage);
}
CBCommandStatus ControlBar::processContextSensitiveButtonTransition(GameWindow *button, GadgetGameMessage gadgetMessage)
{
	return processCommandTransitionUI(button, gadgetMessage);
}

// 0x0029A384 (5B) -> ResourceEntryCollector::rva004E551E 0x004E551E.
class Rva0029A384 { public: void rva0029A384(); };
void Rva0029A384::rva0029A384() { ((ResourceEntryCollector *)this)->rva004E551E(); }

// 0x0030B7BD / 0x0030C10F (5B, cdecl) -> the rowed range equality tests.
int Rva0030B7BDEqual(const Rva0030B6A6Range *a, const Rva0030B6A6Range *b) { return Rva0030B6A6Equal(a, b); }
int Rva0030C10FEqual(const Rva0030BFE8Range *a, const Rva0030BFE8Range *b) { return Rva0030BFE8Equal(a, b); }

// 0x002178F8 / 0x002B4536 (5B, cdecl) -> the rowed swaps.
void Rva002178F8Swap(MixFileCreator::FileInfoStruct *a, MixFileCreator::FileInfoStruct *b) { Rva002176A6Swap(a, b); }
void Rva002B4536Swap(Rva002B2F97 &a, Rva002B2F97 &b) { Rva002B2FF4Swap(a, b); }

// 0x00334A38 (5B) -> S4Cmp002EB8E0::operator() 0x003340A8.
class Rva00334A38 { public: bool rva00334A38(const S4SortElem20 &a, const S4SortElem20 &b) const; };
bool Rva00334A38::rva00334A38(const S4SortElem20 &s4SortElem20, const S4SortElem20 &b) const { return (*(const S4Cmp002EB8E0 *)this)(s4SortElem20, b); }

// 0x00278DF9 (5B) -> Drawable::calcPhysicsXformWheels 0x00276CFB.
class Rva00278DF9 { public: void rva00278DF9(const Locomotor *locomotor, Drawable::PhysicsXformInfo &info); };
void Rva00278DF9::rva00278DF9(const Locomotor *locomotor, Drawable::PhysicsXformInfo &info) { ((Drawable *)this)->calcPhysicsXformWheels(locomotor, info); }

// ---- fourth group ----------------------------------------------------------
class Rva0021915B;
void Rva0021ACB9Swap(Rva0021915B *a, Rva0021915B *b);
class Rva002BBBE7 { public: void rva002BC39D(); };

// 0x0021BA41 (5B, cdecl) -> the rowed Rva0021ACB9Swap.
void Rva0021BA41Swap(Rva0021915B *a, Rva0021915B *b) { Rva0021ACB9Swap(a, b); }

// 0x002BC588 (5B) -> Rva002BBBE7::rva002BC39D 0x002BC39D.
class Rva002BC588 { public: void rva002BC588(); };
void Rva002BC588::rva002BC588() { ((Rva002BBBE7 *)this)->rva002BC39D(); }

// 0x002BC5C9 (10B, cdecl) -> Rva002BBBE7::rva002BC39D 0x002BC39D on the
// int-keyed LivingWorld map global at VA 0x00E04544 (the tree clear), with
// ecx loaded from the immediate; no direct callers.
extern unsigned int g_Va00E04544;
void Rva002BC5C9ClearMap() { ((Rva002BBBE7 *)&g_Va00E04544)->rva002BC39D(); }

// ---- fifth group -----------------------------------------------------------
class GeometryInfo { public: virtual ~GeometryInfo(); };
class Dict { public: void clear(); };
class Rva004DFC20 { public: void clear(); };
struct BfmeOpaqueOwnedRecord492;
struct BfmeOpaqueOwnedRecord840;
struct BfmeE12;
class ModuleData;
class GameInfo { public: void setSeed(int); };
class Rva005E626DListener { public: virtual void notify(void *); };
enum ObjectID { INVALID_ID = 0 };
class GarrisonContain { public: virtual int getObjectGarrisonPointIndex(ObjectID); };
class TransportContain { public: virtual bool isExitBusy() const; };
class Module;
class Object
{
	friend class Rva00487075;
protected:
	Module *findModule(NameKeyType) const;
};
class NetCommandList { public: void reset(); };
class RenderObjClass { public: virtual void Update_Sub_Object_Transforms(); };

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class deque
{
public:
	void push_back(const T &);
};
template <class T, class A> class vector
{
public:
	void reserve(unsigned int);
	void swap(vector<T, A> &);
};
template <class T> struct _Deque_iterator_base
{
	int _M_subtract(const _Deque_iterator_base<T> &) const;
};
template <unsigned int N> class bitset
{
public:
	bitset<N> &_Unchecked_set(unsigned int, int);
	bitset<N> &_Unchecked_reset(unsigned int);
	bool _Unchecked_test(unsigned int) const;
};
}

// 0x00283E97 (5B) -> GeometryInfo::~GeometryInfo 0x00050B2A.
class Rva00283E97 { public: void rva00283E97(); };
void Rva00283E97::rva00283E97() { ((GeometryInfo *)this)->GeometryInfo::~GeometryInfo(); }

// 0x00329DBD (5B) -> Dict::clear 0x00313574.
class Rva00329DBD { public: void rva00329DBD(); };
void Rva00329DBD::rva00329DBD() { ((Dict *)this)->clear(); }

// 0x00360961 (5B) -> Rva004DFC20::clear 0x001DBCDC.
class Rva00360961 { public: void rva00360961(); };
void Rva00360961::rva00360961() { ((Rva004DFC20 *)this)->clear(); }

// 0x0038D55B (5B) -> deque<BfmeOpaqueOwnedRecord492>::push_back 0x0038D2A3.
class Rva0038D55B { public: void rva0038D55B(const BfmeOpaqueOwnedRecord492 &v); };
void Rva0038D55B::rva0038D55B(const BfmeOpaqueOwnedRecord492 &v)
{
	((_STL::deque<BfmeOpaqueOwnedRecord492, _STL::allocator<BfmeOpaqueOwnedRecord492> > *)this)->push_back(v);
}

// 0x0038D560 (5B) -> deque<BfmeOpaqueOwnedRecord840>::push_back 0x0038D2D5.
class Rva0038D560 { public: void rva0038D560(const BfmeOpaqueOwnedRecord840 &v); };
void Rva0038D560::rva0038D560(const BfmeOpaqueOwnedRecord840 &v)
{
	((_STL::deque<BfmeOpaqueOwnedRecord840, _STL::allocator<BfmeOpaqueOwnedRecord840> > *)this)->push_back(v);
}

// 0x003B02EF (5B) -> vector<BfmeE12>::reserve 0x003B0224.
class Rva003B02EF { public: void rva003B02EF(unsigned int n); };
void Rva003B02EF::rva003B02EF(unsigned int n)
{
	((_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)this)->reserve(n);
}

// 0x003B0325 (5B) -> vector<const ModuleData *>::reserve 0x002B712E.
class Rva003B0325 { public: void rva003B0325(unsigned int n); };
void Rva003B0325::rva003B0325(unsigned int n)
{
	((_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *)this)->reserve(n);
}

// 0x00421DC3 (5B) -> _Deque_iterator_base<void *>::_M_subtract 0x00051A98.
class Rva00421DC3 { public: int rva00421DC3(const _STL::_Deque_iterator_base<void *> &x) const; };
int Rva00421DC3::rva00421DC3(const _STL::_Deque_iterator_base<void *> &x) const
{
	return ((const _STL::_Deque_iterator_base<void *> *)this)->_M_subtract(x);
}

// 0x004477DB (5B) -> GameInfo::setSeed 0x003FF328.
class Rva004477DB { public: void rva004477DB(int seed); };
void Rva004477DB::rva004477DB(int seed) { ((GameInfo *)this)->setSeed(seed); }

// 0x00466E05 (5B) -> Rva005E626DListener::notify 0x0047A69C.
class Rva00466E05 { public: void rva00466E05(void *p); };
void Rva00466E05::rva00466E05(void *p) { ((Rva005E626DListener *)this)->Rva005E626DListener::notify(p); }

// 0x00479BC5 (5B) -> GarrisonContain::getObjectGarrisonPointIndex 0x00479292.
class Rva00479BC5 { public: int rva00479BC5(ObjectID id); };
int Rva00479BC5::rva00479BC5(ObjectID id) { return ((GarrisonContain *)this)->GarrisonContain::getObjectGarrisonPointIndex(id); }

// 0x0047CA2D (5B) -> TransportContain::isExitBusy 0x00466DA9.
class Rva0047CA2D { public: bool rva0047CA2D() const; };
bool Rva0047CA2D::rva0047CA2D() const { return ((const TransportContain *)this)->TransportContain::isExitBusy(); }

// 0x00487075 (5B) -> Object::findModule 0x0028B6D6.
class Rva00487075 { public: Module *rva00487075(NameKeyType key) const; };
Module *Rva00487075::rva00487075(NameKeyType key) const { return ((const Object *)this)->findModule(key); }

// 0x004CEF01 (5B) -> NetCommandList::reset 0x0058B283.
class Rva004CEF01 { public: void rva004CEF01(); };
void Rva004CEF01::rva004CEF01() { ((NetCommandList *)this)->reset(); }

// 0x004D1A9B (5B) -> bitset<117>::_Unchecked_set 0x004D0F39.
class Rva004D1A9B { public: _STL::bitset<117> &rva004D1A9B(unsigned int pos, int val); };
_STL::bitset<117> &Rva004D1A9B::rva004D1A9B(unsigned int pos, int val)
{
	return ((_STL::bitset<117> *)this)->_Unchecked_set(pos, val);
}

// 0x004D1AA0 (5B) -> bitset<86>::_Unchecked_reset 0x004D0F63.
class Rva004D1AA0 { public: _STL::bitset<86> &rva004D1AA0(unsigned int pos); };
_STL::bitset<86> &Rva004D1AA0::rva004D1AA0(unsigned int pos)
{
	return ((_STL::bitset<86> *)this)->_Unchecked_reset(pos);
}

// 0x004D1AA5 (5B) -> bitset<45>::_Unchecked_test 0x001E37E8.
class Rva004D1AA5 { public: bool rva004D1AA5(unsigned int pos) const; };
bool Rva004D1AA5::rva004D1AA5(unsigned int pos) const
{
	return ((const _STL::bitset<45> *)this)->_Unchecked_test(pos);
}

// 0x005048B0 (5B) -> vector<AsciiString>::swap 0x00567ECD.
class Rva005048B0 { public: void rva005048B0(_STL::vector<AsciiString, _STL::allocator<AsciiString> > &other); };
void Rva005048B0::rva005048B0(_STL::vector<AsciiString, _STL::allocator<AsciiString> > &other)
{
	((_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)this)->swap(other);
}

// 0x006CC4D0 (5B) -> RenderObjClass::Update_Sub_Object_Transforms 0x0069E440.
class Rva006CC4D0 { public: void rva006CC4D0(); };
void Rva006CC4D0::rva006CC4D0() { ((RenderObjClass *)this)->RenderObjClass::Update_Sub_Object_Transforms(); }

bool __cdecl Rva0056815AAny();
int __cdecl Rva0043C99AGet();
class SiegeEngineContain { public: virtual void LoadPostProcess(); };

// 0x003E549E (5B) -> Rva0056815AAny 0x0056815A.
bool __cdecl Rva003E549E() { return Rva0056815AAny(); }

// 0x003E54A3 (5B) -> Rva0043C99AGet 0x0043C99A.
int __cdecl Rva003E54A3() { return Rva0043C99AGet(); }

struct GlobalA04450;
extern GlobalA04450 *g_Va00A04450;

// 0x003E54A8 (12B) -> test g_Va00A04450 != 0.
bool __cdecl Rva003E54A8() { return g_Va00A04450 != 0; }

// 0x00468A2A (5B) -> Rva003BD306Target::rva0039B2C7 0x0039B2C7.
class Rva00468A2A { public: void rva00468A2A(int a, bool b); };
void Rva00468A2A::rva00468A2A(int a, bool b) { ((Rva003BD306Target *)this)->rva0039B2C7(a, b); }

// 0x0047E38F (5B) -> SiegeEngineContain::LoadPostProcess 0x0047C173.
class Rva0047E38F { public: void rva0047E38F(); };
void Rva0047E38F::rva0047E38F() { ((SiegeEngineContain *)this)->SiegeEngineContain::LoadPostProcess(); }
