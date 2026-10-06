// cl: /DNDEBUG /MD /EHsc
// Trimmed from Open-BFME-1
// (Code/GameEngine/Source/GameClient/System/Smudge.cpp): only the placed
// SmudgeManager::removeSmudgeSet and SmudgeSet::SmudgeSet bodies are defined
// here. Sibling bodies stay declared-only so the unmatched-definition gate
// passes. List machinery is the donor's WW3D2/dllist.h with an empty W3DMPO
// (BFME1 trimmed-TU convention); Smudge/SmudgeSet/SmudgeManager mirror
// reference/shims/smudgenopool (no pooling in BFME).

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
	void Remove_Head();
	void Add_Tail(DLNodeClass<T> *node);
	void Remove_Tail();

	T *Head() { return static_cast<T *>(head); }
	T *Tail() { return static_cast<T *>(tail); }
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

	void Insert_Before(DLNodeClass<T> *n)
	{
		list = n->list;
		succ = n;
		pred = n->pred;
		if (n->pred) n->pred->succ = this;
		n->pred = this;

		if (list->head == n) {
			list->head = this;
		}
	}

	void Insert_After(DLNodeClass<T> *n)
	{
		list = n->list;
		pred = n;
		succ = n->succ;
		if (n->succ) n->succ->pred = this;
		n->succ = this;

		if (list->tail == n) {
			list->tail = this;
		}
	}

	void Remove()
	{
		if (!list) return;
		if (list->Head() == this) {
			DLListClass<T> *tmp_list = list;
			list = 0;
			tmp_list->Remove_Head();
			return;
		}
		if (list->Tail() == this) {
			DLListClass<T> *tmp_list = list;
			list = 0;
			tmp_list->Remove_Tail();
			return;
		}
		if (succ) succ->pred = pred;
		if (pred) pred->succ = succ;
		list = 0;
	}
};

template <class T>
inline void DLListClass<T>::Add_Head(DLNodeClass<T> *n)
{
	n->list = this;
	if (head) {
		n->Insert_Before(head);
		head = n;
	}
	else {
		tail = n;
		head = n;
		n->succ = 0;
		n->pred = 0;
	}
}

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

// ??0SmudgeSet@@QAE@XZ
//
// The donor's body is only m_usedSmudgeCount=0; the vptr pair plus the zero
// run are the implicit DLNode base and DLList member init. Identity is
// caller-proven: SmudgeManager::addSmudgeSet news a 0x20-byte SmudgeSet at
// 0x002D2956 (free-list node arithmetic recovers the object at head-4).
SmudgeSet::SmudgeSet(void)
{
	m_usedSmudgeCount = 0;
}

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
	// Retail seats the free list at +0x14: vptr + hardware flag + used list.
	Int m_hardwareSupportStatus;
	DLListClass<SmudgeSet> m_usedSmudgeSetList;
	DLListClass<SmudgeSet> m_freeSmudgeSetList;
	Int m_smudgeCountLastFrame;
};

// ?removeSmudgeSet@SmudgeManager@@QAEXAAUSmudgeSet@@@Z
void SmudgeManager::removeSmudgeSet(SmudgeSet &mySmudge)
{
	mySmudge.Remove();	//remove from used list
	m_freeSmudgeSetList.Add_Head(&mySmudge);	//add to free list.
}
