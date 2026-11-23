// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// LatchRestore<bool> constructor 0x000519FC, destructor 0x00051A1B and
// deleting destructor 0x00051A46. The latch shape comes from BFME1 GameState.cpp.

template <class T>
class LatchRestore
{
public:
    LatchRestore(T &dest, const T &src) : m_whereToRestore(dest)
    {
        m_valueToRestore = dest;
        dest = src;
    }
    virtual ~LatchRestore(void) { m_whereToRestore = m_valueToRestore; }

protected:
    T m_valueToRestore;
    T &m_whereToRestore;
};

template class LatchRestore<bool>;
