// cl: /DNDEBUG /MD /EHsc
// SmudgeSet::removeSmudgeFromSet at retail 0x002D282E (31B).
//
// Dedicated TU. BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/Smudge.cpp,
// SmudgeSet::removeSmudgeFromSet) verbatim: mySmudge.Remove, static free
// list Add_Head, count decrement. The static free list lives at retail
// 0x00DBCBF4 (sacrificial definition here; DIR32 auto-patches); the count
// sits at +0x1C (vptr + DLNode base at +4 + 12B used list at +0x10).
// Calls resolve to the DLNode<Smudge> Remove pin at 0x002D26BE and the
// DLList<Smudge> Add_Head pin at 0x002D25E2 (same address as the
// DLList<SmudgeSet> Add_Head row: ICF-shared list code, same-address
// spelling per drainChain/KAX precedent).

typedef int Int;
typedef int Bool;

class W3DMPO {};

template <class T> class DLNodeClass;

template <class T>
class DLListClass
{
	friend DLNodeClass<T>;
	DLNodeClass<T> *head;
	DLNodeClass<T> *tail;

public:
	DLListClass();
	virtual ~DLListClass() { }

	void Add_Head(DLNodeClass<T> *node);
	void Add_Tail(DLNodeClass<T> *node);

	T *Head() { return static_cast<T *>(head); }
};

template <class T>
class DLNodeClass : public W3DMPO
{
	friend DLListClass<T>;
	DLNodeClass<T> *succ;
	DLNodeClass<T> *pred;
	DLListClass<T> *list;
public:
	DLNodeClass() : succ(0), pred(0), list(0) {}
	~DLNodeClass() { Remove(); }

	void Remove();
};

struct Smudge : public DLNodeClass<Smudge>
{
};

struct SmudgeSet : public DLNodeClass<SmudgeSet>
{
public:
	SmudgeSet(void);
	virtual ~SmudgeSet();
	void reset(void);
	void removeSmudgeFromSet(Smudge &mySmudge);

private:
	DLListClass<Smudge> m_usedSmudgeList;
	static DLListClass<Smudge> m_freeSmudgeList;
	Int m_usedSmudgeCount;
};

DLListClass<Smudge> SmudgeSet::m_freeSmudgeList;

// ?removeSmudgeFromSet@SmudgeSet@@QAEXAAUSmudge@@@Z
void SmudgeSet::removeSmudgeFromSet(Smudge &mySmudge)
{
	mySmudge.Remove();	//remove from used list.
	m_freeSmudgeList.Add_Head(&mySmudge);	//add to free list
	m_usedSmudgeCount--;
}
