// cl: /DNDEBUG /MD /GX-
// SmudgeManager::addSmudgeSet at retail 0x002D291B (95B).
//
// Dedicated TU: the home TU (Smudge.cpp) defines SmudgeSet::SmudgeSet, so a
// `new SmudgeSet()` placed there inlines the ctor instead of calling the
// 0x002D2859 row. Here the ctor is declare-only and resolves to the row.
// Likewise Remove/Add_Tail are declare-only and resolve to their pins
// (0x002D2700 / 0x002D2634); only Head is inline (retail reads the head
// member directly, no call). Layout mirrors Smudge.cpp exactly: DLList
// carries a vptr (12B), so the used list object sits at +0x08 and the free
// list object at +0x14 (heads at +0x0C/+0x18); SmudgeSet seats its DLNode
// base at +4 behind its vptr (free-node to object folds head-4).
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/Smudge.cpp
// (SmudgeManager::addSmudgeSet, b1 0x005D4240) verbatim.

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
	DLListClass() : head(0), tail(0) {}
	virtual ~DLListClass() { }

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

struct Smudge;

struct SmudgeSet : public DLNodeClass<SmudgeSet>
{
public:
	SmudgeSet(void);
	virtual ~SmudgeSet();
	void reset(void);

private:
	DLListClass<Smudge> m_usedSmudgeList;
	Int m_usedSmudgeCount;
};

class SmudgeManager
{
public:
	SmudgeManager(void);
	virtual ~SmudgeManager();

	virtual void init(void);
	virtual void reset(void);

	SmudgeSet *addSmudgeSet(void);
	void removeSmudgeSet(SmudgeSet &mySmudge);

protected:
	Int m_hardwareSupportStatus;
	DLListClass<SmudgeSet> m_usedSmudgeSetList;
	DLListClass<SmudgeSet> m_freeSmudgeSetList;
	Int m_smudgeCountLastFrame;
};

// ?addSmudgeSet@SmudgeManager@@QAEPAUSmudgeSet@@XZ
SmudgeSet *SmudgeManager::addSmudgeSet(void)
{
	SmudgeSet *set = m_freeSmudgeSetList.Head();
	if (set) {
		set->Remove();	//remove from free list
		m_usedSmudgeSetList.Add_Tail(set);	//add to used list.
		return set;
	}
	set = new SmudgeSet();
	m_usedSmudgeSetList.Add_Tail(set);	//add to used list.
	return set;
}
