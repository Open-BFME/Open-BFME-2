// ?rva0033B217@Rva0033B217@@QAEXXZ
// partial score=0.8481 date=2026-10-05
// ?rva0033B217@Rva0033B217@@QAEXXZ
// partial score=0.92 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
// ?rva0033B217@Rva0033B217@@QAEXXZ @0x0033B217 315B evidence six GameText fetches into wide members callers 0x002CF1EA rowed set 0x00037150 release 0x00036E70 TheGameText
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
    virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
    virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
    virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
    virtual void pad12(); virtual void pad13();
    virtual UnicodeString *fetch(UnicodeString *out, AsciiString *key, int unk);
};

extern GameTextInterface *TheGameText;

struct RawWide
{
    void *m_data;
    ~RawWide() { ((UnicodeString *)this)->~UnicodeString(); }
};

struct Rva0033B217
{
    char m_pad00[0x2c];
    AsciiString m_key2c;
    UnicodeString m_val30;
    AsciiString m_key34;
    UnicodeString m_val38;
    AsciiString m_key3c;
    UnicodeString m_val40;
    AsciiString m_key44;
    UnicodeString m_val48;
    AsciiString m_key4c;
    UnicodeString m_val50;
    AsciiString m_key54;
    UnicodeString m_val58;
    void rva0033B217();
};

// ?rva0033B217@Rva0033B217@@QAEXXZ present-unmatched
void Rva0033B217::rva0033B217()
{
    {
        RawWide tmp;
        UnicodeString *ret = TheGameText->fetch((UnicodeString *)&tmp, &m_key2c, 0);
        m_val30.set(*ret);
    }
    {
        RawWide tmp;
        UnicodeString *ret = TheGameText->fetch((UnicodeString *)&tmp, &m_key34, 0);
        m_val38.set(*ret);
    }
    {
        RawWide tmp;
        UnicodeString *ret = TheGameText->fetch((UnicodeString *)&tmp, &m_key4c, 0);
        m_val50.set(*ret);
    }
    {
        RawWide tmp;
        UnicodeString *ret = TheGameText->fetch((UnicodeString *)&tmp, &m_key44, 0);
        m_val48.set(*ret);
    }
    {
        RawWide tmp;
        UnicodeString *ret = TheGameText->fetch((UnicodeString *)&tmp, &m_key54, 0);
        m_val58.set(*ret);
    }
    {
        RawWide tmp;
        UnicodeString *ret = TheGameText->fetch((UnicodeString *)&tmp, &m_key3c, 0);
        m_val40.set(*ret);
    }
}
