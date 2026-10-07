// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native 32B833..32B871 RET4. SidesList's neighbouring rowed clear/addSide
// and their measured +10 notifier / +F7C flag establish the receiver prefix.
// Only this prefix is represented; no full allocation size is claimed.
// The indexed post stores an opaque second word: the other owner pointer
// here. The callback is the existing compiler vcall thunk5CB27E, slot20.
// Callback owner/method identities and the original method name are unknown.
class SidesListNotifier {
public:
    void post(void (*callback)(), void *owner, int argumentWord);
};
class SidesList {
public:
    void exchangeFlag(SidesList *other);
private:
    char unknown00[0x10];
    SidesListNotifier m_notifier;
    char unknown11[0xF7C-0x11];
    bool m_cleared;
};
class Rva0032B833Listener {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20(SidesList *, SidesList *);
};
template <class T> inline void exchangeValue(T &a,T &b) {T t=a; a=b; b=t;}
void SidesList::exchangeFlag(SidesList *other)
{
    exchangeValue(m_cleared,other->m_cleared);
    union CallbackWord {
        void (Rva0032B833Listener::*member)(SidesList *,SidesList *);
        void (*stored)();
    } callback;
    callback.member=&Rva0032B833Listener::slot20;
    m_notifier.post(callback.stored,this,(int)other);
    other->m_notifier.post(callback.stored,other,(int)this);
}
