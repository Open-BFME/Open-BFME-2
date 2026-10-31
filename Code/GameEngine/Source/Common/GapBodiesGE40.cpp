// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (fortieth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

// Declaration-only view of the STLport vector member these bodies call; no
// container code is instantiated here.
namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *first, T *last);
	void clear() { erase(m_start, m_finish); }
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// --- 0x005E68A7 (25B): assign the pair through the two stored pointers.
struct Rva005E68A7Pair
{
	int m_first;
	int m_second;
};

class Rva005E68A7
{
public:
	Rva005E68A7 &operator=(const Rva005E68A7Pair &pair);
private:
	int *m_first;
	int *m_second;
};

Rva005E68A7 &Rva005E68A7::operator=(const Rva005E68A7Pair &pair)
{
	*m_first = pair.m_first;
	*m_second = pair.m_second;
	return *this;
}

// --- 0x005E7BD6 (12B, cdecl) / 0x005E7D2A (15B): release an element through
// the rowed 0x005E74AA; drop the last element of the +0x04-ended range the
// same way. 0x005F0A44 (12B, cdecl): release through the rowed 0x005F0647.
class Rva005E74AA
{
public:
	void *rva005E74AA(unsigned flags);						// 0x005E74AA
private:
	int m_00;
};

void Rva005E7BD6(Rva005E74AA *element)
{
	element->rva005E74AA(0);
}

class Rva005E7D2A
{
public:
	void popBack();
private:
	Rva005E74AA *m_begin;
	Rva005E74AA *m_end;
};

void Rva005E7D2A::popBack()
{
	--m_end;
	m_end->rva005E74AA(0);
}

class Rva005F0647
{
public:
	void *rva005F0647(unsigned flags);						// 0x005F0647
};

void Rva005F0A44(Rva005F0647 *element)
{
	element->rva005F0647(0);
}

// --- 0x005E8872 (24B, cdecl): the rowed 0x004E0625 value of the rowed
// 0x005F88D6 lookup's record, 0 without one.
int Rva005F88D6Get(int key);								// 0x005F88D6

class Rva004E0625
{
public:
	int rva004E0625() const;								// 0x004E0625
};

int Rva005E8872(int key)
{
	Rva004E0625 *record = (Rva004E0625 *)Rva005F88D6Get(key);
	if (record)
		return record->rva004E0625();
	return 0;
}

// --- 0x005EC288 (14B): whether the referenced record's +0x08 kind is 3.
struct Rva005EC288Record
{
	int m_00;
	int m_04;
	int m_kind;
};

class Rva005EC288
{
public:
	bool rva005EC288() const;
private:
	Rva005EC288Record *m_record;
};

bool Rva005EC288::rva005EC288() const
{
	return m_record->m_kind == 3;
}

// --- 0x005ED291 (14B) / 0x005F17B8 (14B) / 0x005ED29F (18B) / 0x005EEF9A
// (15B) / 0x005F05D7 (15B): the +0x04 record's indexed +0x2C slot (address,
// value) and the sizes of its +0x44 (20-byte), +0x24 and +0x34 (pointer)
// ranges.
struct Rva005ED29FEntry
{
	int m_words[5];
};

template <class T> struct Rva005ED291Range
{
	int size() const { return m_end - m_begin; }
	T *m_begin;
	T *m_end;
	T *m_storage;
};

struct Rva005ED291Record
{
	char m_pad[0x24];
	Rva005ED291Range<void *> m_24;							// +0x24
	int m_30;
	Rva005ED291Range<void *> m_34;							// +0x34
	int m_40;
	Rva005ED291Range<Rva005ED29FEntry> m_44;				// +0x44
};

struct Rva005ED291Slots
{
	char m_pad[0x2C];
	int m_slots[1];
};

class Rva005ED291
{
public:
	int *rva005ED291(int index);
	int rva005F17B8(int index) const;
	int rva005ED29F() const;
	int rva005EEF9A() const;
	int rva005F05D7() const;
private:
	int m_00;
	Rva005ED291Record *m_record;
};

int *Rva005ED291::rva005ED291(int index)
{
	return &((Rva005ED291Slots *)m_record)->m_slots[index];
}

int Rva005ED291::rva005F17B8(int index) const
{
	return ((Rva005ED291Slots *)m_record)->m_slots[index];
}

int Rva005ED291::rva005ED29F() const
{
	return m_record->m_44.size();
}

int Rva005ED291::rva005EEF9A() const
{
	return m_record->m_24.size();
}

int Rva005ED291::rva005F05D7() const
{
	return m_record->m_34.size();
}

// --- 0x005EFF68 (31B) / 0x005EFF87 (31B): field-parse callbacks reading the
// string the user data indexes in the +0x08 / +0x1C string arrays (rowed
// INI::parseAsciiString).
class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);	// 0x0002F11E
};

struct Rva005EFF68Store
{
	int m_00;
	int m_04;
	int m_08[5];
	int m_1C[1];
};

void Rva005EFF68(INI *ini, void *instance, void *store, const void *userData)
{
	int *name = &((Rva005EFF68Store *)instance)->m_08[*(const int *)userData];
	INI::parseAsciiString(ini, name, name, 0);
}

void Rva005EFF87(INI *ini, void *instance, void *store, const void *userData)
{
	int *name = &((Rva005EFF68Store *)instance)->m_1C[*(const int *)userData];
	INI::parseAsciiString(ini, name, name, 0);
}

// --- 0x005F0612 (18B): share a counted record (+0x08 count).
struct Rva005F0612Record
{
	int m_00;
	int m_04;
	int m_refs;
};

class Rva005F0612
{
public:
	Rva005F0612(Rva005F0612Record *record);
private:
	Rva005F0612Record *m_record;
};

Rva005F0612::Rva005F0612(Rva005F0612Record *record) : m_record(record)
{
	if (record)
		++record->m_refs;
}

// --- 0x005F5FF1 (14B) / 0x005F5FFF (14B): clear / set the +0x34 flag and run
// slot 5 / slot 4 of the referenced object.
class Rva005F5FF1Target
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
};

class Rva005F5FF1
{
public:
	void rva005F5FF1(int unused);
	void rva005F5FFF(int unused);
private:
	Rva005F5FF1Target *m_target;
	char m_pad04[0x34 - 0x04];
	bool m_34;
};

void Rva005F5FF1::rva005F5FF1(int unused)
{
	m_34 = false;
	m_target->slot14();
}

void Rva005F5FF1::rva005F5FFF(int unused)
{
	m_34 = true;
	m_target->slot10();
}

// --- 0x005F8820 (14B): empty the +0x20 element vector (rowed erase
// 0x005F8620).
struct Rva005F8620Element;

class Rva005F8820
{
public:
	void rva005F8820();
private:
	char m_pad[0x20];
	_STL::vector<Rva005F8620Element> m_elements;
};

void Rva005F8820::rva005F8820()
{
	m_elements.clear();
}

// ?rva005F8845@Rva005F8845@@QAEXXZ @0x005F8845 8B member forwarder to rowed
// ?rva005F8820@Rva005F8820@@QAEXXZ (0x005F8820). No callers. Honest address name.
class Rva005F8845
{
public:
	void rva005F8845();
private:
	char m_pad[4];
	Rva005F8820 *m_member;
};
void Rva005F8845::rva005F8845()
{
	return m_member->rva005F8820();
}
