// cl: /DNDEBUG /MD /EHsc
// SmudgeManager::SmudgeManager at retail 0x002D25BA (40B).
//
// Dedicated TU (pin->row upgrade of the ??0SmudgeManager@@QAE@XZ pin).
// Layout mirrors Smudge.cpp exactly: DLList carries a vptr (12B), so the
// used list object sits at +0x08 and the free list object at +0x14;
// vptrs 0xC02A60 (manager) + 0xC02A5C x2 (lists) patch as DIR32.
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/Smudge.cpp
// (SmudgeManager::SmudgeManager) verbatim; the list vptrs/zeros fall out
// of the implicit member inits.

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

struct SmudgeSet;

class SmudgeManager
{
public:
	SmudgeManager(void);
	virtual ~SmudgeManager();

	virtual void init(void);
	virtual void reset(void);

protected:
	enum HardwareSmudgeSupport { SMUDGE_SUPPORT_UNKNOWN, SMUDGE_SUPPORT_NO, SMUDGE_SUPPORT_YES };

	HardwareSmudgeSupport m_hardwareSupportStatus;
	DLListClass<SmudgeSet> m_usedSmudgeSetList;
	DLListClass<SmudgeSet> m_freeSmudgeSetList;
	Int m_smudgeCountLastFrame;
};

// ??0SmudgeManager@@QAE@XZ
SmudgeManager::SmudgeManager(void)
{
	m_smudgeCountLastFrame = 0;
	m_hardwareSupportStatus = SMUDGE_SUPPORT_UNKNOWN;
}
