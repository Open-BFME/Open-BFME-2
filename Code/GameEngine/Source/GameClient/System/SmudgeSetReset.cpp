// cl: /DNDEBUG /MD /GX- /O1
// SmudgeSet::reset at retail 0x002D269B (35B).
//
// Dedicated TU: the home TU (Smudge.cpp) defines the DLList/DLNode templates
// fully, so an Add_Head call placed there binds (or inlines) to the TU-local
// instantiation instead of the folded retail body at 0x002D25E2. Here
// Remove_Head/Add_Head stay declare-only and resolve to their pins
// (0x002D2613 / 0x002D25E2); only Head is inline (retail reads the head
// member directly, no call). Layout mirrors Smudge.cpp exactly: SmudgeSet
// carries its vptr at +0 with the DLNode base at +4, so the used list object
// sits at +0x10 (head at +0x14) and the count at +0x1C.
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/Smudge.cpp
// (SmudgeSet::reset) verbatim.

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

	void Remove_Head();
	void Add_Head(DLNodeClass<T> *node);

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

private:
	DLListClass<Smudge> m_usedSmudgeList;
	Int m_usedSmudgeCount;
};

// SmudgeSet::m_freeSmudgeList (donor static, defined by the engine binary at
// retail 0x00DBCBF4): borrowed by address so this TU never defines it.
#define SmudgeSetFreeSmudgeList (*(DLListClass<Smudge> *)0x00DBCBF4)

// ?reset@SmudgeSet@@QAEXXZ
void SmudgeSet::reset(void)
{
	Smudge *head;

	while ((head = m_usedSmudgeList.Head()) != 0) {
		m_usedSmudgeList.Remove_Head();
		SmudgeSetFreeSmudgeList.Add_Head(head);	//add to free list
	}
}
