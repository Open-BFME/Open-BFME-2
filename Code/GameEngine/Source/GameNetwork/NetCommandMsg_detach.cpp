// cl: /O1 /DNDEBUG /MD /EHsc
// NetCommandMsg::detach at RVA 0x004D55BC, full 26-byte retail body.
// BFME's de-pooled command has its count at +0x18 and frees through the
// slot0 virtual (scalar-deleting-dtor with flags=0 destroys without
// freeing; the explicit operator delete follows). Shape follows the Radar
// deleteInstance precedent: a slot0 virtual taking int and returning the
// instance pointer, fed to ::operator delete. Sibling
// detach@NetCommandNode (rowed 0x58B8AE) tail-calls into this body.
class NetCommandMsg {
public:
    virtual void *deleteInstance(int flags);
    virtual ~NetCommandMsg();
    void detach();
private:
    char m_unrecovered04[0x14];
    int m_referenceCount;
};
void NetCommandMsg::detach()
{
    if (--m_referenceCount == 0 || m_referenceCount < 0)
        ::operator delete(deleteInstance(0));
}
