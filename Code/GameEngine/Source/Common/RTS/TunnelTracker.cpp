// cl: /DNDEBUG /MD /EHsc
// WB11031A0 names iterateContained; retail4F553F..4F558C proves the full
// 77-byte visitor, contain-list header +0x10 and node links/payload +0/+4/+8.
// GeneralsMD TunnelTracker.cpp (BFME1 34f59164f6) explains the mutation-safe
// traversal: advance before the callback, which may remove the current item.
class Object;
typedef void (__cdecl *ContainIterateFunc)(Object *object, void *userData);
struct TunnelContainedNode
{
    TunnelContainedNode *m_next;
    TunnelContainedNode *m_prev;
    Object *m_object;
};
class TunnelTracker
{
public:
    void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
    void healObjects(float frames);
    static void healObject(Object *object, void *frames);
private:
    char m_unrecovered00[0x10];
    TunnelContainedNode *m_containHead;
};

void TunnelTracker::iterateContained(ContainIterateFunc func, void *userData, bool reverse)
{
    if (reverse)
    {
        TunnelContainedNode *cur = m_containHead;
        if (cur == cur->m_next)
            return;
        do
        {
            cur = cur->m_prev;
            func(cur->m_object, userData);
        } while (cur != m_containHead->m_next);
        return;
    }
    TunnelContainedNode *cur = m_containHead->m_next;
    if (cur == m_containHead)
        return;
    do
    {
        Object *object = cur->m_object;
        cur = cur->m_next;
        func(object, userData);
    } while (cur != m_containHead);
}

// Donor healObjects name and float argument are supported by the native
// fixed healObject callback (4F53C3), whose user data is read as float.
// WB1103C10 has the same call graph but no independent method-name evidence.
void TunnelTracker::healObjects(float frames)
{
    iterateContained(healObject, &frames, false);
}
