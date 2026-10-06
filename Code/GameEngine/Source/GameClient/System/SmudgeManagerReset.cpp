// cl: /DNDEBUG /MD /EHsc
// SmudgeManager::reset at retail 0x002D27CC (57B).
//
// Dedicated TU. BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/Smudge.cpp,
// SmudgeManager::reset) verbatim: Head loop over the used SmudgeSet list at
// +0x08 (head at +0x0C, DLNode base at +4 so the node folds head-4),
// Remove_Head, head->reset(), Add_Tail to the free list at +0x14.
// Calls resolve to the DLList<SmudgeSet> Remove_Head pin at 0x002D2665,
// the SmudgeSet::reset row at 0x002D269B and the DLList<SmudgeSet>
// Add_Tail pin at 0x002D2634.

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

	void Add_Head(DLNodeClass<T> *node);
	void Add_Tail(DLNodeClass<T> *node);
	void Remove_Head();

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

protected:
	Int m_hardwareSupportStatus;
	DLListClass<SmudgeSet> m_usedSmudgeSetList;
	DLListClass<SmudgeSet> m_freeSmudgeSetList;
	Int m_smudgeCountLastFrame;
};

// ?reset@SmudgeManager@@UAEXXZ
void SmudgeManager::reset(void)
{
	SmudgeSet *head;

	//Return all smudgeSets back to free pool.
	while ((head = m_usedSmudgeSetList.Head()) != 0) {
		m_usedSmudgeSetList.Remove_Head();
		head->reset();	//free all smudges.
		m_freeSmudgeSetList.Add_Tail(head);
	}
}
