// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BFME1 GameNetwork/IPEnumeration.cpp donor, verbatim body: the retail leaf
// nulls the address-list head and clears the winsock flag (8-byte object, no
// vtable; the dtor at 0x50C283 reads the same two slots).

class EnumeratedIP;

class IPEnumeration
{
public:
    IPEnumeration();

private:
    EnumeratedIP *m_IPlist;
    bool m_isWinsockInitialized;
};

// ??0IPEnumeration@@QAE@XZ
IPEnumeration::IPEnumeration(void)
{
    m_IPlist = 0;
    m_isWinsockInitialized = false;
}
