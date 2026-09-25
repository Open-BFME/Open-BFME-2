// cl: /O1 /Os /DNDEBUG /MD /EHsc
// DLListClass<Smudge>::Add_Head, from the BFME1 Smudge list model.
struct Smudge;
struct SmudgeSet;

template <class T> class DLNodeClass;

template <class T> class DLListClass
{
    friend class DLNodeClass<T>;
    DLNodeClass<T> *head;
    DLNodeClass<T> *tail;
public:
    virtual ~DLListClass() {}
    void Add_Head(DLNodeClass<T> *node);
    void Add_Tail(DLNodeClass<T> *node);
    void Remove_Head();
    void Remove_Tail();
    T *Head() { return static_cast<T *>(head); }
    T *Tail() { return static_cast<T *>(tail); }
};

template <class T> class DLNodeClass
{
    friend class DLListClass<T>;
    DLNodeClass<T> *succ;
    DLNodeClass<T> *pred;
    DLListClass<T> *list;
public:
    void Insert_Before(DLNodeClass<T> *node);
    void Insert_After(DLNodeClass<T> *node);
    void Remove();
};

template <class T> void DLListClass<T>::Add_Head(DLNodeClass<T> *node)
{
    node->list = this;
    if (head) {
        node->Insert_Before(head);
        head = node;
    } else {
        tail = node;
        head = node;
        node->succ = 0;
        node->pred = 0;
    }
}

template void DLListClass<Smudge>::Add_Head(DLNodeClass<Smudge> *node);

template <class T> void DLListClass<T>::Add_Tail(DLNodeClass<T> *node)
{
    node->list = this;
    if (tail) {
        node->Insert_After(tail);
        tail = node;
    } else {
        tail = node;
        head = node;
        node->succ = 0;
        node->pred = 0;
    }
}

template void DLListClass<SmudgeSet>::Add_Tail(DLNodeClass<SmudgeSet> *node);

template <class T> void DLListClass<T>::Remove_Head()
{
    if (!head)
        return;
    DLNodeClass<T> *oldHead = head;
    head = head->succ;
    if (!head)
        tail = head;
    else
        head->pred = 0;
    oldHead->Remove();
}

template void DLListClass<Smudge>::Remove_Head();

// SmudgeSet has its own vptr before the DLNode base. Converting the
// successor through SmudgeSet preserves the target's null adjustment.
struct SmudgeSet : public DLNodeClass<SmudgeSet>
{
    virtual ~SmudgeSet();
};

template <> void DLListClass<SmudgeSet>::Remove_Head()
{
    if (!head)
        return;
    DLNodeClass<SmudgeSet> *oldHead = head;
    SmudgeSet *next = static_cast<SmudgeSet *>(head->succ);
    head = next;
    if (!head)
        tail = head;
    else
        head->pred = 0;
    oldHead->Remove();
}

struct Smudge : public DLNodeClass<Smudge> {};

template <class T> void DLNodeClass<T>::Remove()
{
    if (!list)
        return;
    if (list->Head() == this) {
        DLListClass<T> *oldList = list;
        list = 0;
        oldList->Remove_Head();
        return;
    }
    if (list->Tail() == this) {
        DLListClass<T> *oldList = list;
        list = 0;
        oldList->Remove_Tail();
        return;
    }
    if (succ)
        succ->pred = pred;
    if (pred)
        pred->succ = succ;
    list = 0;
}

template void DLNodeClass<Smudge>::Remove();
template void DLNodeClass<SmudgeSet>::Remove();

template <class T> void DLListClass<T>::Remove_Tail()
{
    if (!tail)
        return;
    DLNodeClass<T> *oldTail = tail;
    tail = tail->pred;
    if (!tail)
        head = tail;
    else
        tail->succ = 0;
    oldTail->Remove();
}

template void DLListClass<Smudge>::Remove_Tail();

template <> void DLListClass<SmudgeSet>::Remove_Tail()
{
    if (!tail)
        return;
    DLNodeClass<SmudgeSet> *oldTail = tail;
    SmudgeSet *previous = static_cast<SmudgeSet *>(tail->pred);
    tail = previous;
    if (!tail)
        head = tail;
    else
        tail->succ = 0;
    oldTail->Remove();
}
