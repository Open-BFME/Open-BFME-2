// ??1Player@@UAE@XZ
// partial score=0.93 date=2026-10-06
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??1Player@@UAE@XZ, retail 0x002B11A7 (625 bytes): Player destructor.
// Evidence: pin ??1Player@@UAE@XZ; caller ??_GPlayer 0x002B14CF in PlayerDeleter.cpp;
// vtable 0x00BFDF3C slot-2 name getter returns Player; BFME1 donor
// GameEngine/Source/Common/RTS/PlayerDestructor.cpp; Zero Hour Player.h layout.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <list>

void __cdecl operator delete(void *p);
void __cdecl free(void *p);

class Rva002AAC74PoolList
{
public:
	void clear();
	void destroy() throw();
	~Rva002AAC74PoolList() { destroy(); }
	void *m_head;
};

class PoolMember
{
public:
	void Rva00268902() throw();
	~PoolMember() { Rva00268902(); }
private:
	void *m_head;
};

class DelBase
{
public:
	virtual void *Delete(int flags);
	virtual ~DelBase();
};

struct TeamPrototypeRef
{
	char m_pad[8];
	void *m_owner;
};

struct PoolListNode
{
	PoolListNode *m_next;
	void *m_pad4;
	TeamPrototypeRef *m_tp;
};

struct Rva002E2690Element
{
	int m_a;
	int m_b;
};

struct BfmeVectorRecord002AF478
{
	int m_a[4];
};

class ScoreKeeper
{
public:
	virtual ~ScoreKeeper();
private:
	char m_pad[824 - 4];
};

class Rva002AC340
{
	friend class Player;
protected:
	virtual ~Rva002AC340();
private:
	char m_pad[20 - 4];
};

struct Rva001FD458
{
	void rva001FD659();
	~Rva001FD458();
	char m_pad[8];
};

struct Rva001FD42B
{
	void rva001FD630();
	~Rva001FD42B();
	char m_pad[8];
};

struct Rva000427195
{
	void rva003A2A41();
	~Rva000427195();
	char m_pad[20];
};

class Rva002AE627
{
public:
	virtual ~Rva002AE627();
private:
	char m_pad[48 - 4];
};

class PlayerBase0
{
public:
	virtual ~PlayerBase0() {}
};

class PlayerBase4
{
public:
	virtual ~PlayerBase4() {}
};

class PlayerBase8
{
public:
	virtual ~PlayerBase8() {}
};

struct FreeBlock
{
	~FreeBlock()
	{
		if (m_ptr)
			free(m_ptr);
	}
	void *m_ptr;
};

class Player : public PlayerBase0, public PlayerBase4, public PlayerBase8
{
public:
	virtual ~Player();
private:
	char m_pad0c[0x34 - 0x0C];
	int m_34;
	UnicodeString m_38;
	char m_pad3c[0x4C - 0x38 - 4];
	AsciiString m_4c;
	char m_pad50[0x58 - 0x4C - 4];
	AsciiString m_58;
	char m_pad5c[0x60 - 0x58 - 4];
	Rva002AE627 m_60;
	char m_pad90[0xB8 - 0x90];
	void *m_b8;
	char m_padbc[0x288 - 0xBC];
	Rva001FD42B m_288;
	char m_pad290[0x294 - 0x288 - 8];
	Rva000427195 m_294;
	Rva000427195 m_2a8;
	Rva000427195 m_2bc;
	Rva001FD458 m_2d0;
	char m_pad2d8[0x2EC - 0x2D0 - 8];
	int m_2ec;
	FreeBlock m_2f0;
	char m_pad2f4[0x2FC - 0x2F0 - 4];
	FreeBlock m_2fc;
	char m_pad300[0x308 - 0x2FC - 4];
	FreeBlock m_308;
	char m_pad30c[0x318 - 0x308 - 4];
	Rva002AC340 m_318;
	Rva002AAC74PoolList m_32c;
	DelBase *m_330;
	DelBase *m_334;
	char m_pad338[0x3B0 - 0x338];
	_STL::vector<BfmeVectorRecord002AF478> m_3b0;
	ScoreKeeper m_3bc;
	_STL::list<int> m_6f4;
	_STL::_List_base<int, _STL::allocator<int> > m_700;
	_STL::_List_base<int, _STL::allocator<int> > m_704;
	DelBase *m_708[10];
	DelBase *m_730;
	char m_pad734[0x73C - 0x730 - 4];
	_STL::vector<Rva002E2690Element> m_73c;
	char m_pad748[0x74C - 0x73C - 12];
	AsciiString m_74c;
	char m_pad750[0x754 - 0x74C - 4];
	PoolMember m_754;
};

Player::~Player()
{
	int zero = 0;
	PoolListNode *head = (PoolListNode *)m_32c.m_head;
	m_2ec = zero;
	m_34 = zero;
	for (PoolListNode *nn = head->m_next; nn != head; nn = nn->m_next)
		nn->m_tp->m_owner = (void *)zero;
	m_32c.clear();
	if (m_334) {
		void *q = m_334->Delete(zero);
		::operator delete(q);
	}
	m_334 = (DelBase *)zero;
	if (m_330) {
		void *q = m_330->Delete(zero);
		::operator delete(q);
	}
	m_330 = (DelBase *)zero;
	DelBase **p = m_708;
	int count = 10;
	do {
		if (*p) {
			void *q = (*p)->Delete(zero);
			::operator delete(q);
		}
		*p = (DelBase *)zero;
		++p;
	} while (--count);
	if (m_730) {
		void *q = m_730->Delete(zero);
		::operator delete(q);
	}
	m_730 = (DelBase *)zero;
	if (m_b8)
		::operator delete(m_b8);
	m_b8 = (void *)zero;
}
