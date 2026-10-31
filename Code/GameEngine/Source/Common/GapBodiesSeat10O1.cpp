// Small unrowed .text bodies from the 0x0051xxxx..0x005Fxxxx (/O1) region.
// Retail bytes establish every shape; the owning classes are not recovered,
// so each keeps an address-derived name and a view of only the fields it
// touches. Bodies reached through a vftable slot (an absolute reference in
// .rdata, no direct caller) are declared virtual; the others have no
// recovered caller. Callees are the rowed bodies the retail jmp targets.

// ?rva00531041@Rva00531041@@QAEXXZ @0x00531041 9B: clear +0x10 then +0x0C.
class Rva00531041
{
public:
	void rva00531041();
private:
	char m_pad[0xc];
	int m_0c;
	int m_10;
};

// ?rva0054C836@Rva0054C836@@QBE_NXZ @0x0054C836 9B: pointer at +0x14 non-null.
class Rva0054C836
{
public:
	bool rva0054C836() const;
private:
	char m_pad[0x14];
	void *m_14;
};
bool Rva0054C836::rva0054C836() const
{
	return m_14 != 0;
}

// ?rva005FC6EE@Rva005FC6EE@@QBE_NXZ @0x005FC6EE 9B: bit 0 of the byte at +0x34
// of the object held at +0x18 (same shape as the rowed 0x005F273B).
struct Rva005FC6EEFlags
{
	char m_pad[0x34];
	unsigned char m_bit0 : 1;
};
class Rva005FC6EE
{
public:
	bool rva005FC6EE() const;
private:
	char m_pad[0x18];
	Rva005FC6EEFlags *m_18;
};
bool Rva005FC6EE::rva005FC6EE() const
{
	return m_18->m_bit0;
}

// ?rva005CCBA8@Rva005CCBA8@@QAEXXZ @0x005CCBA8 8B: clear the byte at +0x20 of
// the object held at +0x08.
struct Rva005CCBA8Pointee
{
	char m_pad[0x20];
	unsigned char m_flag;
};
class Rva005CCBA8
{
public:
	void rva005CCBA8();
private:
	char m_pad[0x08];
	Rva005CCBA8Pointee *m_08;
};
void Rva005CCBA8::rva005CCBA8()
{
	m_08->m_flag = 0;
}

// Vector members whose rowed grow/resize bodies the slots tail-jump to.
template <class T>
struct Rva00584A7DVector
{
	void grow(unsigned int count);
};
struct Rva00584A7DEntry;
struct Rva00587057Entry;
struct BfmePod60;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> >
	class vector
	{
	public:
		void resize(unsigned int count);
		T *erase(T *first, T *last);
		void clear();
		void _M_fill_insert(T *position, unsigned int count, const T &value);
	private:
		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};
	template <class T, class A = allocator<T> >
	class deque
	{
	public:
		~deque();
		void pop_front();
		void push_back(const T &value);
	};
	template <class A, class B> struct pair;
	template <class P> struct _Select1st;
	template <class T> struct less;
	template <class K, class V, class KoV, class C, class A>
	class _Rb_tree
	{
	public:
		~_Rb_tree();
		void clear();
		unsigned int erase(const K &key);
	};
	template <class T> struct _Identity;
}

// ?rva00584A75@Rva00584A75@@UAEXI@Z @0x00584A75 8B (vftable slot at VA
// 0x00C6FC84): grow the +0x08 vector through rowed 0x00584A3D.
class Rva00584A75
{
public:
	virtual void rva00584A75(unsigned int count);
private:
	int m_04;
	Rva00584A7DVector<Rva00584A7DEntry> m_08;
};
void Rva00584A75::rva00584A75(unsigned int count)
{
	m_08.grow(count);
}

// ?rva0058704F@Rva0058704F@@UAEXI@Z @0x0058704F 8B (vftable slot at VA
// 0x00C6FD94): grow the +0x08 vector through rowed 0x0058702C.
class Rva0058704F
{
public:
	virtual void rva0058704F(unsigned int count);
private:
	int m_04;
	Rva00584A7DVector<Rva00587057Entry> m_08;
};
void Rva0058704F::rva0058704F(unsigned int count)
{
	m_08.grow(count);
}

// ?rva00588A95@Rva00588A95@@UAEXI@Z @0x00588A95 8B (vftable slot at VA
// 0x00C6FF3C): resize the +0x08 vector through rowed 0x00588A72.
class Rva00588A95
{
public:
	virtual void rva00588A95(unsigned int count);
private:
	int m_04;
	_STL::vector<BfmePod60> m_08;
};
void Rva00588A95::rva00588A95(unsigned int count)
{
	m_08.resize(count);
}

// ?rva005CFACB@Rva005CFACB@@UAEXXZ @0x005CFACB 8B (vftable slot at VA
// 0x00C75558): forward to the rowed 0x005EA91A on the +0x0C member.
class Rva005EA91A
{
public:
	void rva005EA91A();
};
class Rva005CFACB
{
public:
	virtual void rva005CFACB();
private:
	char m_pad[0x08];
	Rva005EA91A m_0c;
};
void Rva005CFACB::rva005CFACB()
{
	m_0c.rva005EA91A();
}

// ?rva00574AB3@Rva00574AB3@@UAE_NXZ @0x00574AB3 8B (vftable slot at VA
// 0x00C3C6D0): direct (qualified) call of the rowed Rva005743C0 slot body
// 0x005743C0 on the object held at +0x04.
class Rva005743C0
{
public:
	virtual bool rva005743C0();
};
class Rva00574AB3
{
public:
	virtual bool rva00574AB3();
private:
	Rva005743C0 *m_04;
};
bool Rva00574AB3::rva00574AB3()
{
	return m_04->Rva005743C0::rva005743C0();
}

// Out-of-line destructors whose only non-trivial member sits at +0, so each
// is a bare tail jump to that member's rowed destructor. Each is reached
// only from EH unwind funclets (0x0079xxxx..0x007Axxxx), i.e. it destroys a
// local of its type; the owning types are unrecovered.
class AsciiString;
struct TreeHintRef0051030C;
struct BfmeOpaque2148;
struct SBServer;
class BfmeMsg
{
public:
	virtual ~BfmeMsg();
};
struct Rva0060D031Member
{
	~Rva0060D031Member();
};

typedef _STL::pair<const AsciiString, TreeHintRef0051030C> Rva00510D07Pair;
typedef _STL::pair<const int, SBServer> Rva005E4920Pair;

// ??1Rva00510D07@@QAE@XZ @0x00510D07 5B: tree member, rowed dtor 0x0051097F.
class Rva00510D07
{
public:
	~Rva00510D07();
private:
	_STL::_Rb_tree<AsciiString, Rva00510D07Pair, _STL::_Select1st<Rva00510D07Pair>, _STL::less<AsciiString>, _STL::allocator<Rva00510D07Pair> > m_tree;
};
Rva00510D07::~Rva00510D07()
{
}

// ??1Rva00550634@@QAE@XZ @0x00550634 5B: BfmeMsg member, rowed dtor 0x00655780.
class Rva00550634
{
public:
	~Rva00550634();
private:
	BfmeMsg m_msg;
};
Rva00550634::~Rva00550634()
{
}

// ??1Rva00551983@@QAE@XZ @0x00551983 5B: deque member, rowed dtor 0x00551868.
class Rva00551983
{
public:
	~Rva00551983();
private:
	_STL::deque<BfmeOpaque2148> m_deque;
};
Rva00551983::~Rva00551983()
{
}

// ??1Rva005E4920@@QAE@XZ @0x005E4920 5B: tree member, rowed dtor 0x005E4670.
class Rva005E4920
{
public:
	~Rva005E4920();
private:
	_STL::_Rb_tree<int, Rva005E4920Pair, _STL::_Select1st<Rva005E4920Pair>, _STL::less<int>, _STL::allocator<Rva005E4920Pair> > m_tree;
};
Rva005E4920::~Rva005E4920()
{
}

// ??1Rva0060D0AE@@QAE@XZ @0x0060D0AE 5B: member, rowed dtor 0x0060D031.
class Rva0060D0AE
{
public:
	~Rva0060D0AE();
private:
	Rva0060D031Member m_member;
};
Rva0060D0AE::~Rva0060D0AE()
{
}

// ?rva00525E00@Rva00525E00@@QAEXPAVXfer@@@Z @0x00525E00 7B (called from
// 0x002D64C7): forward the Xfer to the rowed 0x00525ABF on the object held
// at +0.
class Xfer;
class Rva00525ABF
{
public:
	void rva00525ABF(Xfer *xfer);
};
class Rva00525E00
{
public:
	void rva00525E00(Xfer *xfer);
private:
	Rva00525ABF *m_00;
};


// ?rva0050EE1C@Rva0050EE1C@@QBEHXZ @0x0050EE1C 7B: the rowed
// AsciiStringPlusString::length 0x002198C8 of this object plus one.
struct AsciiStringPlusString
{
	int length() const;
};
struct Rva0050EE1C : AsciiStringPlusString
{
	int rva0050EE1C() const;
};
int Rva0050EE1C::rva0050EE1C() const
{
	return length() + 1;
}

// ?rva00522AFC@Rva00522AFC@@QAEAAV1@ABV1@@Z @0x00522AFC 18B: assignment of an
// object whose only member is an AsciiString->AsciiString tree, through the
// rowed tree operator= 0x0052274D, returning this.
typedef _STL::pair<const AsciiString, AsciiString> Rva00522AFCPair;
namespace _STL
{
	template <>
	class _Rb_tree<AsciiString, Rva00522AFCPair, _Select1st<Rva00522AFCPair>, less<AsciiString>, allocator<Rva00522AFCPair> >
	{
	public:
		_Rb_tree &operator=(const _Rb_tree &other);
	};
}
class Rva00522AFC
{
public:
	Rva00522AFC &rva00522AFC(const Rva00522AFC &other);
private:
	_STL::_Rb_tree<AsciiString, Rva00522AFCPair, _STL::_Select1st<Rva00522AFCPair>, _STL::less<AsciiString>, _STL::allocator<Rva00522AFCPair> > m_tree;
};
Rva00522AFC &Rva00522AFC::rva00522AFC(const Rva00522AFC &other)
{
	m_tree = other.m_tree;
	return *this;
}

// ?Rva0051C3AB@@YAXAAUBfmeE12@@0@Z @0x0051C3AB 5B: swap two 12-byte records
// through the rowed _STL::swap<BfmeE12> 0x004219CD (a tail jump).
struct BfmeE12;
namespace _STL
{
	template <class T> void swap(T &a, T &b);
}
void Rva0051C3AB(BfmeE12 &a, BfmeE12 &b)
{
	_STL::swap(a, b);
}

// ?rva005206FE@Rva005206FE@@QAEXPAURva005205DAElement@@IABU2@@Z @0x005206FE
// 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert
// 0x005205DA (a tail jump with the arguments forwarded).
struct Rva005205DAElement;
namespace _STL
{
	template <>
	class vector<Rva005205DAElement, allocator<Rva005205DAElement> >
	{
	public:
		void _M_fill_insert(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value);
	};
}
class Rva005206FE
{
public:
	void rva005206FE(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value);
private:
	_STL::vector<Rva005205DAElement> m_vector;
};
void Rva005206FE::rva005206FE(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value)
{
	m_vector._M_fill_insert(position, count, value);
}

// ?rva00531C54@Rva00531C54@@QAEXXZ @0x00531C54 6B: clear the 16-bit field at +2.
class Rva00531C54
{
public:
	void rva00531C54();
private:
	unsigned short m_00;
	unsigned short m_02;
};
void Rva00531C54::rva00531C54()
{
	m_02 = 0;
}

// ?Rva00531EF6@@YAHG@Z @0x00531EF6 6B: cdecl zero-extension of a 16-bit argument.
int Rva00531EF6(unsigned short value)
{
	return value;
}

// ?rva0053B8F1@Rva0053B8F1@@QBE_NXZ @0x0053B8F1 7B: the flag byte at +0x106.
class Rva0053B8F1
{
public:
	bool rva0053B8F1() const;
private:
	char m_pad[0x106];
	bool m_106;
};
bool Rva0053B8F1::rva0053B8F1() const
{
	return m_106;
}

// ?rva0056864A@Rva0056864A@@QBEEXZ @0x0056864A 7B: high nibble of the byte at +0x47.
class Rva0056864A
{
public:
	unsigned char rva0056864A() const;
private:
	char m_pad[0x47];
	unsigned char m_lo : 4;
	unsigned char m_hi : 4;
};
unsigned char Rva0056864A::rva0056864A() const
{
	return m_hi;
}

// ?rva005778D1@Rva005778D1@@QBEHXZ @0x005778D1 9B and
// ?rva005778DA@Rva005778D1@@QAEPAXXZ @0x005778DA 9B: through the object held
// at +0x40 to its first-word pointee, read its +4 word / take its +8 address.
struct Rva005778D1Record
{
	int m_00;
	int m_04;
	char m_08[4];
};
struct Rva005778D1Holder
{
	Rva005778D1Record *m_00;
};
class Rva005778D1
{
public:
	int rva005778D1() const;
	void *rva005778DA();
private:
	char m_pad[0x40];
	Rva005778D1Holder *m_40;
};
int Rva005778D1::rva005778D1() const
{
	return m_40->m_00->m_04;
}
void *Rva005778D1::rva005778DA()
{
	return m_40->m_00->m_08;
}

// ?rva00564B12@Rva00564B12@@QAEAAVRva005045DBTree@@ABV2@@Z @0x00564B12 8B:
// assign the +0x0C tree through the rowed Rva005045DBTree::assign 0x005045DB.
class Rva005045DBTree
{
public:
	Rva005045DBTree &assign(const Rva005045DBTree &other);
	Rva005045DBTree &self();
	int storage[3];
};
class Rva00564B12
{
public:
	Rva005045DBTree &rva00564B12(const Rva005045DBTree &other);
private:
	char m_pad[0x0c];
	Rva005045DBTree m_0c;
};
Rva005045DBTree &Rva00564B12::rva00564B12(const Rva005045DBTree &other)
{
	return m_0c.assign(other);
}

// ?rva005CCB54@Rva005CCB54@@QBEEXZ @0x005CCB54 7B: the byte at +0x23 of the
// object held at +0x08.
struct Rva005CCB54Pointee
{
	char m_pad[0x23];
	unsigned char m_23;
};
class Rva005CCB54
{
public:
	unsigned char rva005CCB54() const;
private:
	char m_pad[0x08];
	Rva005CCB54Pointee *m_08;
};
unsigned char Rva005CCB54::rva005CCB54() const
{
	return m_08->m_23;
}

// ?rva005CDD20@Rva005CDD20@@QAEXXZ @0x005CDD20 5B: clear the +0x24 word.
class Rva005CDD20
{
public:
	void rva005CDD20();
private:
	char m_pad[0x24];
	int m_24;
};
void Rva005CDD20::rva005CDD20()
{
	m_24 = 0;
}

// ?rva005E2D46@Rva005E2D46@@QBEHXZ @0x005E2D46 5B: the +0x08 word plus one.
class Rva005E2D46
{
public:
	int rva005E2D46() const;
private:
	char m_pad[0x08];
	int m_08;
};
int Rva005E2D46::rva005E2D46() const
{
	return m_08 + 1;
}

// ?rva005FF1F8@Rva005FF1F8@@QBEHXZ @0x005FF1F8 15B: element count of the
// 8-byte-element vector at +0x30 of the object held at +0x04 (same shape as
// the rowed Rva005F8427::rva005F8408).
struct Rva005FF1F8Element
{
	int m_words[2];
};
struct Rva005FF1F8Vector
{
	Rva005FF1F8Element *m_begin;
	Rva005FF1F8Element *m_end;
	int size() const { return m_end - m_begin; }
};
struct Rva005FF1F8Owner
{
	char m_pad[0x30];
	Rva005FF1F8Vector m_vec;
};
class Rva005FF1F8
{
public:
	int rva005FF1F8() const;
private:
	char m_pad[4];
	Rva005FF1F8Owner *m_04;
};
int Rva005FF1F8::rva005FF1F8() const
{
	return m_04->m_vec.size();
}

// ?rva005E88E4@Rva005E88E4@@QAEXXZ @0x005E88E4 10B: the rowed 0x005F884D on
// the +0x04 member of the object held at +0.
class Rva005F884D
{
public:
	void rva005F884D();
};
struct Rva005E88E4Pointee
{
	int m_00;
	Rva005F884D m_04;
};
class Rva005E88E4
{
public:
	void rva005E88E4();
private:
	Rva005E88E4Pointee *m_00;
};
void Rva005E88E4::rva005E88E4()
{
	m_00->m_04.rva005F884D();
}

// ?rva005E358A@Rva005E358A@@QAEXXZ @0x005E358A 5B and
// ?rva005EB8D1@Rva005EB8D1@@QAEXXZ @0x005EB8D1 5B: tail jumps to the rowed
// 0x005F1B51 / 0x0022999F on the member at +0.
class Rva005F1B51
{
public:
	void rva005F1B51();
};
class Rva00226883
{
public:
	void rva0022999F();
};
class Rva005E358A
{
public:
	void rva005E358A();
private:
	Rva005F1B51 m_00;
};
void Rva005E358A::rva005E358A()
{
	m_00.rva005F1B51();
}
class Rva005EB8D1
{
public:
	void rva005EB8D1();
private:
	Rva00226883 m_00;
};
void Rva005EB8D1::rva005EB8D1()
{
	m_00.rva0022999F();
}

// By-value iterator/pair wrappers over a rowed lookup on the member at +0:
// the hidden return slot is passed straight through (or filled from eax)
// and returned.

// ?rva005538BA@Rva005538BA@@QAE?AURva005538BAIterator@@PBX@Z @0x005538BA 20B:
// wrap the node pointer from the rowed 0x005533BC lookup.
class Rva005533BC
{
public:
	void *rva005533BC(const void *key);
};
struct Rva005538BAIterator
{
	Rva005538BAIterator(void *node) : m_node(node) {}
	void *m_node;
};
class Rva005538BA
{
public:
	Rva005538BAIterator rva005538BA(const void *key);
private:
	Rva005533BC m_00;
};
Rva005538BAIterator Rva005538BA::rva005538BA(const void *key)
{
	return Rva005538BAIterator(m_00.rva005533BC(key));
}

// ?rva00601457@Rva00601457@@QAE?AURva006013B7Pair@@ABURva00600F9CElement@@@Z
// @0x00601457 20B: forward to the rowed 0x006013B7.
struct Rva00600F9CElement;
struct Rva006013B7Pair
{
	Rva006013B7Pair(const Rva006013B7Pair &other);
	void *m_first;
	bool m_second;
};
class Rva0060126D
{
public:
	Rva006013B7Pair rva006013B7(const Rva00600F9CElement &element);
};
class Rva00601457
{
public:
	Rva006013B7Pair rva00601457(const Rva00600F9CElement &element);
private:
	Rva0060126D m_00;
};
Rva006013B7Pair Rva00601457::rva00601457(const Rva00600F9CElement &element)
{
	return m_00.rva006013B7(element);
}

// ?rva0060CC71@Rva0060CC71@@QAE?AURva0060CAEAIterator@@ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z
// @0x0060CC71 20B: forward to the rowed 0x0060CB61.
namespace _STL
{
	template <class C> class char_traits;
	template <class C, class T, class A> class basic_string;
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva0060CC71String;
struct Rva0060CAEAIterator
{
	Rva0060CAEAIterator(const Rva0060CAEAIterator &other);
	void *m_node;
};
class Rva0060CAEA
{
public:
	Rva0060CAEAIterator rva0060CB61(const Rva0060CC71String &key);
};
class Rva0060CC71
{
public:
	Rva0060CAEAIterator rva0060CC71(const Rva0060CC71String &key);
private:
	Rva0060CAEA m_00;
};
Rva0060CAEAIterator Rva0060CC71::rva0060CC71(const Rva0060CC71String &key)
{
	return m_00.rva0060CB61(key);
}

// STLport vector::clear() is erase(begin(), end()): these instantiations
// push the +4 finish and +0 start words and call the rowed erase(first,
// last) of the same vector. ?clear@?$vector@URva0054107FRecord@@...@QAEXXZ
// @0x00541BC9 11B (erase 0x0054152D), ?clear@?$vector@VRva0054103E@@...
// @0x00541BD4 11B (erase 0x00541553) and ?clear@?$vector@URva00565865Element@@...
// @0x00565A7E 11B (erase 0x00565865).
template <class T, class A>
void _STL::vector<T, A>::clear()
{
	erase(_M_start, _M_finish);
}
struct Rva0054107FRecord;
class Rva0054103E;
struct Rva00565865Element;
template void _STL::vector<Rva0054107FRecord>::clear();
template void _STL::vector<Rva0054103E>::clear();
template void _STL::vector<Rva00565865Element>::clear();

// ?rva00600396@Rva00600396@@QAEHXZ @0x00600396 15B: the rowed 0x003F468D on
// the object held at +0x14 with the +0x18 and +0x1C words.
class Rva003F468D
{
public:
	int rva003F468D(int a, int b);
};
class Rva00600396
{
public:
	int rva00600396();
private:
	char m_pad[0x14];
	Rva003F468D *m_14;
	int m_18;
	int m_1c;
};
int Rva00600396::rva00600396()
{
	return m_14->rva003F468D(m_18, m_1c);
}

// Queue-style wrappers over a deque held at +0: each is a bare tail jump to
// the rowed deque<T>::pop_front / push_back of the same instantiation. The
// owning adaptor types are unrecovered, so each keeps an address name.
class PingRequest;
class BuddyRequest;
struct BfmeOpaqueOwnedRecord1432;
struct BfmeOpaqueOwnedRecord1408;

// ?rva0054FF12@Rva0054FF12@@QAEXXZ @0x0054FF12 5B: deque<PingRequest>::pop_front.
class Rva0054FF12
{
public:
	void rva0054FF12();
private:
	_STL::deque<PingRequest> m_queue;
};
void Rva0054FF12::rva0054FF12()
{
	m_queue.pop_front();
}

// ?rva00550C81@Rva00550C81@@QAEXXZ @0x00550C81 5B: deque<BuddyRequest>::pop_front.
class Rva00550C81
{
public:
	void rva00550C81();
private:
	_STL::deque<BuddyRequest> m_queue;
};
void Rva00550C81::rva00550C81()
{
	m_queue.pop_front();
}

// ?rva00550C86@Rva00550C86@@QAEXXZ @0x00550C86 5B: deque<BfmeOpaque2148>::pop_front.
class Rva00550C86
{
public:
	void rva00550C86();
private:
	_STL::deque<BfmeOpaque2148> m_queue;
};
void Rva00550C86::rva00550C86()
{
	m_queue.pop_front();
}

// ?rva00551B1E@Rva00551B1E@@QAEXABVBuddyRequest@@@Z @0x00551B1E 5B: deque<BuddyRequest>::push_back.
class Rva00551B1E
{
public:
	void rva00551B1E(const BuddyRequest &value);
private:
	_STL::deque<BuddyRequest> m_queue;
};
void Rva00551B1E::rva00551B1E(const BuddyRequest &value)
{
	m_queue.push_back(value);
}

// ?rva00551B23@Rva00551B23@@QAEXABUBfmeOpaque2148@@@Z @0x00551B23 5B: deque<BfmeOpaque2148>::push_back.
class Rva00551B23
{
public:
	void rva00551B23(const BfmeOpaque2148 &value);
private:
	_STL::deque<BfmeOpaque2148> m_queue;
};
void Rva00551B23::rva00551B23(const BfmeOpaque2148 &value)
{
	m_queue.push_back(value);
}

// ?rva00557B46@Rva00557B46@@QAEXXZ @0x00557B46 5B: deque<BfmeOpaqueOwnedRecord1432>::pop_front.
class Rva00557B46
{
public:
	void rva00557B46();
private:
	_STL::deque<BfmeOpaqueOwnedRecord1432> m_queue;
};
void Rva00557B46::rva00557B46()
{
	m_queue.pop_front();
}

// ?rva00557BA2@Rva00557BA2@@QAEXXZ @0x00557BA2 5B: deque<BfmeOpaqueOwnedRecord1408>::pop_front.
class Rva00557BA2
{
public:
	void rva00557BA2();
private:
	_STL::deque<BfmeOpaqueOwnedRecord1408> m_queue;
};
void Rva00557BA2::rva00557BA2()
{
	m_queue.pop_front();
}

// ?rva00559131@Rva00559131@@QAEXABUBfmeOpaqueOwnedRecord1432@@@Z @0x00559131 5B: deque<BfmeOpaqueOwnedRecord1432>::push_back.
class Rva00559131
{
public:
	void rva00559131(const BfmeOpaqueOwnedRecord1432 &value);
private:
	_STL::deque<BfmeOpaqueOwnedRecord1432> m_queue;
};
void Rva00559131::rva00559131(const BfmeOpaqueOwnedRecord1432 &value)
{
	m_queue.push_back(value);
}

// ?rva00559136@Rva00559136@@QAEXABUBfmeOpaqueOwnedRecord1408@@@Z @0x00559136 5B: deque<BfmeOpaqueOwnedRecord1408>::push_back.
class Rva00559136
{
public:
	void rva00559136(const BfmeOpaqueOwnedRecord1408 &value);
private:
	_STL::deque<BfmeOpaqueOwnedRecord1408> m_queue;
};
void Rva00559136::rva00559136(const BfmeOpaqueOwnedRecord1408 &value)
{
	m_queue.push_back(value);
}

// cdecl destroy helpers: ecx = the argument, then a tail jump to the rowed
// destructor (or reset member) of the pointee.
class Rva004E1A04
{
public:
	~Rva004E1A04();
};
class Rva004E366E
{
public:
	void rva004E366E();
};
class Rva005344C0
{
public:
	~Rva005344C0();
};
class Rva00568C4E
{
public:
	~Rva00568C4E();
};
class BfmePoolRef10
{
public:
	~BfmePoolRef10();
};
void Rva0052BFCF(Rva004E1A04 *p)
{
	p->~Rva004E1A04();
}
void Rva0052BFD8(Rva004E366E *p)
{
	p->rva004E366E();
}
void Rva00534626(Rva005344C0 *p)
{
	p->~Rva005344C0();
}
void Rva005690DE(Rva00568C4E *p)
{
	p->~Rva00568C4E();
}
void Rva005690E7(BfmePoolRef10 *p)
{
	p->~BfmePoolRef10();
}

// Bare tail jumps to a rowed member of the object at +0.
class Rva0038201D { public: void rva003828B6(); };
class Rva0038204A { public: void rva003828DF(); };
class Rva00382077 { public: void rva00382908(); };
class Rva005532D6 { public: void rva005532D6(); };

// ?rva0055381C@Rva0055381C@@QAEXXZ @0x0055381C 5B: Rva0038201D::rva003828B6 on the member at +0.
class Rva0055381C
{
public:
	void rva0055381C();
private:
	Rva0038201D m_00;
};
void Rva0055381C::rva0055381C()
{
	m_00.rva003828B6();
}

// ?rva00553821@Rva00553821@@QAEXXZ @0x00553821 5B: Rva0038204A::rva003828DF on the member at +0.
class Rva00553821
{
public:
	void rva00553821();
private:
	Rva0038204A m_00;
};
void Rva00553821::rva00553821()
{
	m_00.rva003828DF();
}

// ?rva00553826@Rva00553826@@QAEXXZ @0x00553826 5B: Rva00382077::rva00382908 on the member at +0.
class Rva00553826
{
public:
	void rva00553826();
private:
	Rva00382077 m_00;
};
void Rva00553826::rva00553826()
{
	m_00.rva00382908();
}

// ?rva0055382B@Rva0055382B@@QAEXXZ @0x0055382B 5B: Rva005532D6::rva005532D6 on the member at +0.
class Rva0055382B
{
public:
	void rva0055382B();
private:
	Rva005532D6 m_00;
};
void Rva0055382B::rva0055382B()
{
	m_00.rva005532D6();
}

class Gen_0054EC50 { public: bool bfmeDiffers(const Gen_0054EC50 &other) const; };
class Gen_0054EC80 { public: bool bfmeDiffers(const Gen_0054EC80 &other) const; };
class Rva0056FA50 { public: bool rva0056FA50(const Rva0056FA50 &other) const; };
class Rva0056FA72 { public: bool rva0056FA72(const Rva0056FA72 &other) const; };

// ?rva0056FCC7@Rva0056FCC7@@QBE_NABVGen_0054EC50@@@Z @0x0056FCC7 5B: Gen_0054EC50::bfmeDiffers on the member at +0.
class Rva0056FCC7
{
public:
	bool rva0056FCC7(const Gen_0054EC50 &other) const;
private:
	Gen_0054EC50 m_00;
};
bool Rva0056FCC7::rva0056FCC7(const Gen_0054EC50 &other) const
{
	return m_00.bfmeDiffers(other);
}

// ?rva0056FCCC@Rva0056FCCC@@QBE_NABVGen_0054EC80@@@Z @0x0056FCCC 5B: Gen_0054EC80::bfmeDiffers on the member at +0.
class Rva0056FCCC
{
public:
	bool rva0056FCCC(const Gen_0054EC80 &other) const;
private:
	Gen_0054EC80 m_00;
};
bool Rva0056FCCC::rva0056FCCC(const Gen_0054EC80 &other) const
{
	return m_00.bfmeDiffers(other);
}

// ?rva0056FCD1@Rva0056FCD1@@QBE_NABVRva0056FA50@@@Z @0x0056FCD1 5B: Rva0056FA50::rva0056FA50 on the member at +0.
class Rva0056FCD1
{
public:
	bool rva0056FCD1(const Rva0056FA50 &other) const;
private:
	Rva0056FA50 m_00;
};
bool Rva0056FCD1::rva0056FCD1(const Rva0056FA50 &other) const
{
	return m_00.rva0056FA50(other);
}

// ?rva0056FCD6@Rva0056FCD6@@QBE_NABVRva0056FA72@@@Z @0x0056FCD6 5B: Rva0056FA72::rva0056FA72 on the member at +0.
class Rva0056FCD6
{
public:
	bool rva0056FCD6(const Rva0056FA72 &other) const;
private:
	Rva0056FA72 m_00;
};
bool Rva0056FCD6::rva0056FCD6(const Rva0056FA72 &other) const
{
	return m_00.rva0056FA72(other);
}

// ?rva005709CC@Rva005709CC@@QAE_NXZ @0x005709CC 5B: the rowed
// AptOnlineLogin::rva005706D4 0x005706D4 on the member at +0.
class AptOnlineLogin { public: bool rva005706D4(); };
class Rva005709CC
{
public:
	bool rva005709CC();
private:
	AptOnlineLogin m_00;
};
bool Rva005709CC::rva005709CC()
{
	return m_00.rva005706D4();
}

// ?rva005693CF@Rva005693CF@@QAEXXZ @0x005693CF 5B: clear the key tree at +0
// through the rowed _Rb_tree::clear 0x0056926C.
struct Rva00568FE4Key;
struct Rva00568FE4Less;
class Rva005693CF
{
public:
	void rva005693CF();
private:
	_STL::_Rb_tree<Rva00568FE4Key, Rva00568FE4Key, _STL::_Identity<Rva00568FE4Key>, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > m_tree;
};
void Rva005693CF::rva005693CF()
{
	m_tree.clear();
}

// ??1Rva00534765@@QAE@XZ @0x00534765 5B: member-only dtor, rowed 0x0053470B.
class Rva00534641
{
public:
	~Rva00534641();
};
class Rva00534765
{
public:
	~Rva00534765();
private:
	Rva00534641 m_00;
};
Rva00534765::~Rva00534765()
{
}

// ?rva00531EB8@Rva00531EB8@@QAEXXZ @0x00531EB8 4B: advance the +0 pointer by one word.
class Rva00531EB8
{
public:
	void rva00531EB8();
private:
	int *m_cur;
};
void Rva00531EB8::rva00531EB8()
{
	++m_cur;
}

// ?rva00586FBB@Rva00586FBB@@QAEXPAVRva00585B16@@IABV2@@Z @0x00586FBB 5B and
// ?rva005880B8@Rva005880B8@@QAEXPAURva00587375@@IABU2@@Z @0x005880B8 5B:
// fill-insert into the vector at +0 through the rowed _M_fill_insert.
class Rva00585B16;
struct Rva00587375;
class Rva00586FBB
{
public:
	void rva00586FBB(Rva00585B16 *position, unsigned int count, const Rva00585B16 &value);
private:
	_STL::vector<Rva00585B16> m_vector;
};
void Rva00586FBB::rva00586FBB(Rva00585B16 *position, unsigned int count, const Rva00585B16 &value)
{
	m_vector._M_fill_insert(position, count, value);
}
class Rva005880B8
{
public:
	void rva005880B8(Rva00587375 *position, unsigned int count, const Rva00587375 &value);
private:
	_STL::vector<Rva00587375> m_vector;
};
void Rva005880B8::rva005880B8(Rva00587375 *position, unsigned int count, const Rva00587375 &value)
{
	m_vector._M_fill_insert(position, count, value);
}

// ?rva005F600D@Rva005F600D@@QAEXH@Z @0x005F600D 7B and
// ?rva005F6014@Rva005F600D@@QAEXH@Z @0x005F6014 7B: clear / set the +0x35
// flag byte; the word argument is unused.
class Rva005F600D
{
public:
	void rva005F600D(int unused);
	void rva005F6014(int unused);
private:
	char m_pad[0x35];
	bool m_35;
};
void Rva005F600D::rva005F600D(int)
{
	m_35 = false;
}
void Rva005F600D::rva005F6014(int)
{
	m_35 = true;
}

// StrategicHUD::BattlePromptMovieClip::Impl::OnAllyTabsUnloaded @0x005F8F80 12B and
// OnEnemyTabsUnloaded @0x005F8F8B 11B (bound to "_OnAllyTabsUnloaded" /
// "_OnEnemyTabsUnloaded" by the Impl constructor 0x005FA3B1, after the rowed
// OnAllyTabsLoaded/OnEnemyTabsLoaded): clear the owned handle at +0x2C /
// +0x3C through the rowed Rva000AD6F4::clear 0x000AD6F4; the command
// argument is unused.
class Rva000AD6F4
{
public:
	void clear();
private:
	void *m_pointer;
};
namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl;
};
}
class StrategicHUD::BattlePromptMovieClip::Impl
{
public:
	void OnAllyTabsUnloaded(const char *unused);
	void OnEnemyTabsUnloaded(const char *unused);
private:
	char m_pad[0x2c];
	Rva000AD6F4 m_2c;
	char m_pad30[0x3c - 0x30];
	Rva000AD6F4 m_3c;
};
void StrategicHUD::BattlePromptMovieClip::Impl::OnAllyTabsUnloaded(const char *)
{
	m_2c.clear();
}
void StrategicHUD::BattlePromptMovieClip::Impl::OnEnemyTabsUnloaded(const char *)
{
	m_3c.clear();
}

// ?rva005B1903@Rva005B1903@@QAEXPAUBfmePod8@@IABU2@@Z @0x005B1903 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x000B02B6.
struct BfmePod8;
class Rva005B1903
{
public:
	void rva005B1903(BfmePod8 *position, unsigned int count, const BfmePod8 &value);
private:
	_STL::vector<BfmePod8> m_vector;
};


// ?rva005B1908@Rva005B1908@@QAEXPAUBfmePod20@@IABU2@@Z @0x005B1908 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x005B1748.
struct BfmePod20;
class Rva005B1908
{
public:
	void rva005B1908(BfmePod20 *position, unsigned int count, const BfmePod20 &value);
private:
	_STL::vector<BfmePod20> m_vector;
};


// ?rva005EE00F@Rva005EE00F@@QAEXPAUBfmeStringRecord005ED5F3@@IABU2@@Z @0x005EE00F 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x005EDEF3.
struct BfmeStringRecord005ED5F3;
class Rva005EE00F
{
public:
	void rva005EE00F(BfmeStringRecord005ED5F3 *position, unsigned int count, const BfmeStringRecord005ED5F3 &value);
private:
	_STL::vector<BfmeStringRecord005ED5F3> m_vector;
};
void Rva005EE00F::rva005EE00F(BfmeStringRecord005ED5F3 *position, unsigned int count, const BfmeStringRecord005ED5F3 &value)
{
	m_vector._M_fill_insert(position, count, value);
}

// ?rva005EFD8A@Rva005EFD8A@@QAEXPAURva005EFD53Element@@IABU2@@Z @0x005EFD8A 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x005EFC30.
struct Rva005EFD53Element;
class Rva005EFD8A
{
public:
	void rva005EFD8A(Rva005EFD53Element *position, unsigned int count, const Rva005EFD53Element &value);
private:
	_STL::vector<Rva005EFD53Element> m_vector;
};
void Rva005EFD8A::rva005EFD8A(Rva005EFD53Element *position, unsigned int count, const Rva005EFD53Element &value)
{
	m_vector._M_fill_insert(position, count, value);
}

// Tail jumps to a rowed member of the tree / array at +0.
struct Rva0027EA49;
class Rva009F68C6PointerArray
{
public:
	void RemoveAll();
};
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva005C6BF0Tree;
typedef _STL::_Rb_tree<int, Rva005E4920Pair, _STL::_Select1st<Rva005E4920Pair>, _STL::less<int>, _STL::allocator<Rva005E4920Pair> > Rva005E466BTree;

// ?rva005C6BF0@Rva005C6BF0@@QAEXXZ @0x005C6BF0 5B: rowed tree clear 0x005C6B83.
// ??1Rva005C6C76@@QAE@XZ @0x005C6C76 5B: member-only dtor, rowed tree dtor 0x005C6BF5.
class Rva005C6BF0
{
public:
	void rva005C6BF0();
private:
	Rva005C6BF0Tree m_tree;
};
void Rva005C6BF0::rva005C6BF0()
{
	m_tree.clear();
}
class Rva005C6C76
{
public:
	~Rva005C6C76();
private:
	Rva005C6BF0Tree m_tree;
};
Rva005C6C76::~Rva005C6C76()
{
}

// ?rva005E466B@Rva005E466B@@QAEXXZ @0x005E466B 5B: rowed int->SBServer tree clear 0x005E43A8.
class Rva005E466B
{
public:
	void rva005E466B();
private:
	Rva005E466BTree m_tree;
};
void Rva005E466B::rva005E466B()
{
	m_tree.clear();
}

// ?rva00628C69@Rva00628C69@@QAEXXZ @0x00628C69 5B: rowed RemoveAll 0x00628C25.
class Rva00628C69
{
public:
	void rva00628C69();
private:
	Rva009F68C6PointerArray m_array;
};
void Rva00628C69::rva00628C69()
{
	m_array.RemoveAll();
}

// Fill wrappers over the rowed cdecl Rva005EA1B1Fill 0x005EA1B1:
// ?Rva005EA966@@YAPAMPAMHABH@Z @0x005EA966 5B forwards the same three
// arguments (a tail jump); ?Rva005EA5CE@@YAPAMPAMHABHABURva005EA5CETag@@@Z
// @0x005EA5CE 21B takes an extra empty tag argument, so it re-pushes the
// three and calls (the shape of STLport's __uninitialized_fill_n dispatch).
float *Rva005EA1B1Fill(float *dest, int count, const int &value);
struct Rva005EA5CETag
{
};
float *Rva005EA966(float *dest, int count, const int &value)
{
	return Rva005EA1B1Fill(dest, count, value);
}
float *Rva005EA5CE(float *dest, int count, const int &value, const Rva005EA5CETag &)
{
	return Rva005EA1B1Fill(dest, count, value);
}

// ?rva005C6D48@Rva005C6D48@@QAEIABURva0027EA49@@@Z @0x005C6D48 5B and
// ?rva005CABBB@Rva005CABBB@@QAEIABVAsciiString@@@Z @0x005CABBB 5B: erase a key
// from the set tree at +0 through its rowed _Rb_tree::erase(const key &).
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva005CABBBTree;
class Rva005C6D48
{
public:
	unsigned int rva005C6D48(const Rva0027EA49 &key);
private:
	Rva005C6BF0Tree m_tree;
};
unsigned int Rva005C6D48::rva005C6D48(const Rva0027EA49 &key)
{
	return m_tree.erase(key);
}
class Rva005CABBB
{
public:
	unsigned int rva005CABBB(const AsciiString &key);
private:
	Rva005CABBBTree m_tree;
};


// ?rva00549420@Rva00549420@@QBEHABV1@@Z @0x00549420 5B and
// ?rva00584D50@Rva00584D50@@QBEHABV1@@Z @0x00584D50 5B: deque iterator
// difference through the rowed _Deque_iterator_base::_M_subtract.
struct BfmeE8;
namespace _STL
{
	template <class T>
	struct _Deque_iterator_base
	{
		int _M_subtract(const _Deque_iterator_base &other) const;
		T *_M_cur;
		T *_M_first;
		T *_M_last;
		T **_M_node;
	};
}
class Rva00549420 : public _STL::_Deque_iterator_base<BfmeE8>
{
public:
	int rva00549420(const Rva00549420 &other) const;
};
int Rva00549420::rva00549420(const Rva00549420 &other) const
{
	return _M_subtract(other);
}
class Rva00584D50 : public _STL::_Deque_iterator_base<BfmeE12>
{
public:
	int rva00584D50(const Rva00584D50 &other) const;
};
int Rva00584D50::rva00584D50(const Rva00584D50 &other) const
{
	return _M_subtract(other);
}

// ?rva005D7357@Rva005D7357@@QBEIXZ @0x005D7357 5B: bucket count of the
// int->int hash_map at +0 through its rowed bucket_count.
namespace _STL
{
	template <class T> struct hash;
	template <class T> struct equal_to;
	template <class K, class V, class H, class E, class A>
	class hash_map
	{
	public:
		unsigned int bucket_count() const;
	};
}
class Rva005D7357
{
public:
	unsigned int rva005D7357() const;
private:
	_STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > m_map;
};
unsigned int Rva005D7357::rva005D7357() const
{
	return m_map.bucket_count();
}

// ?rva0052B488@Rva0052B488@@QAEHPBD@Z @0x0052B488 5B: rowed
// XferSave::rva0060D435 0x0060D435 on the saver at +0 (a tail jump).
class XferSave
{
public:
	int rva0060D435(const char *name);
};
class Rva0052B488
{
public:
	int rva0052B488(const char *name);
private:
	XferSave m_xfer;
};


// ?Rva005676FB@@YAPAXPAVGameWindow@@@Z @0x005676FB 5B: cdecl forward to the
// rowed GadgetButtonGetData 0x00327D56.
class GameWindow;
void *GadgetButtonGetData(GameWindow *window);
void *Rva005676FB(GameWindow *window)
{
	return GadgetButtonGetData(window);
}

// ?Rva005BE344@@YAPAHPAHHPBH@Z @0x005BE344 5B: cdecl forward to the rowed
// rva499ed0 0x005BE225 with the same arguments.
int *rva499ed0(int *dest, int count, const int *value);
int *Rva005BE344(int *dest, int count, const int *value)
{
	return rva499ed0(dest, count, value);
}

// ?rva00603912@Rva00603912@@QBEIXZ @0x00603912 9B and
// ?rva0060391B@Rva00603912@@QBEIXZ @0x0060391B 10B: byte-swap the +0 / +4 word
// through the rowed cdecl Rva009CC290Swap 0x006038EF.
unsigned int Rva009CC290Swap(unsigned int value);
class Rva00603912
{
public:
	unsigned int rva00603912() const;
	unsigned int rva0060391B() const;
private:
	unsigned int m_00;
	unsigned int m_04;
};
unsigned int Rva00603912::rva00603912() const
{
	return Rva009CC290Swap(m_00);
}
unsigned int Rva00603912::rva0060391B() const
{
	return Rva009CC290Swap(m_04);
}

// ?Rva006D3850@@YA_NH@Z @0x006D3850 12B: code point within the Unicode range.
bool Rva006D3850(int codePoint)
{
	if (codePoint > 0x10ffff)
		return false;
	return true;
}

// 00564B0A is the +0C receiver accessor through the already rowed self()
// provider at 0047A6A9. Native565402 and WB12CAB90 independently establish
// that provider's borrow role; the original owner of this unused outline
// remains unknown. Keep it separate from the neighboring assignment view.
class Rva00564B0A
{
public:
    Rva005045DBTree &rva00564B0A();
private:
    char m_unknown00[0x0c];
    Rva005045DBTree m_0c;
};
Rva005045DBTree &Rva00564B0A::rva00564B0A()
{
    return m_0c.self();
}
