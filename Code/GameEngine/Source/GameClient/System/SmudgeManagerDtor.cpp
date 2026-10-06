// cl: /DNDEBUG /MD /EHsc
//
// ??1SmudgeManager@@UAE@XZ, retail 0x002D29F7, 140 bytes.
// Virtual dtor over vtable 0x00C02A60 (slot 0 deleting dtor at 0x002D2A83
// calls this body). Calls the rowed reset at 0x002D27CC, frees the free
// SmudgeSet list at +0x14 via Remove_Head plus deleteInstance slot 0 with 0
// return-fed to the rowed operator delete at 0x0002FD60, frees the static
// SmudgeSet::m_freeSmudgeList Smudge pool via Remove_Head on the +0x14 list
// (donor bug transcribed verbatim) plus DLNode Remove plus operator delete,
// then restores the two DLList vptrs at +0x14/+0x08 to 0x00C02A5C by hand.
// Layout from the rowed reset TU (status at +0x04, used list at +0x08, free
// list at +0x14, count last frame at +0x20; DLNode base at +4 so Head folds
// head-4). Donor BFME1 Smudge.cpp dtor and ZH Smudge.cpp dtor verbatim
// including the second-loop wrong-list Remove_Head. Shape follows
// PlayerListDtor (tracked-pointer virtual release slot 0 with 0).

typedef int Int;

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

struct Smudge : public DLNodeClass<Smudge>
{
};

struct SmudgeSet : public DLNodeClass<SmudgeSet>
{
public:
	virtual void *deleteInstance(int flags);

	static DLListClass<Smudge> m_freeSmudgeList;

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

protected:
	Int m_hardwareSupportStatus;
	DLListClass<SmudgeSet> m_usedSmudgeSetList;
	DLListClass<SmudgeSet> m_freeSmudgeSetList;
	Int m_smudgeCountLastFrame;
};

SmudgeManager::~SmudgeManager()
{
	reset();

	SmudgeSet *head;
	while ((head = m_freeSmudgeSetList.Head()) != 0) {
		m_freeSmudgeSetList.Remove_Head();
		::operator delete(head->deleteInstance(0));
	}

	Smudge *head2;
	while ((head2 = SmudgeSet::m_freeSmudgeList.Head()) != 0) {
		m_freeSmudgeSetList.Remove_Head();
		head2->Remove();
		::operator delete(head2);
	}
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?m_freeSmudgeList@SmudgeSet@@2V?$DLListClass@USmudge@@@@A=?m_freeSmudgeList@SmudgeSet@@0V?$DLListClass@USmudge@@@@A")
