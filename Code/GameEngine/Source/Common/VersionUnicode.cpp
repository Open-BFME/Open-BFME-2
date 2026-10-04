// cl: /O1 /EHsc

// Version's Unicode build-label accessors.  The layout and source follow the
// readable GeneralsMD version.cpp; the BFME2 retail bodies use the same seven
// StringBase<char> metadata members as VersionDestructor.cpp.

typedef unsigned short wchar_t;

class UnicodeString;
class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    void releaseBuffer();
    Header *m_data;

public:
    char getCharAt(int index) const
    {
        return m_data ? m_data->data[index] : 0;
    }
    const T *str() const
    {
        static const T TheNullChr = 0;
        return m_data ? &m_data->data[0] : &TheNullChr;
    }
};

class AsciiString
{
public:
    AsciiString(const AsciiString &that) : m_data(that.m_data) {}
    ~AsciiString() { m_data.releaseBuffer(); }
    // Inline the StringBase logic here instead of calling
    // StringBase<char>::getCharAt: that call forced this TU to emit a
    // select-any copy of it, and this TU's /O1 shape (shared epilogue) loses
    // against WWLib/string_base_inline.cpp's retail /O2 copy. Reading the
    // header through the friendship gives the rows the identical inlined
    // code while emitting no competing copy.
    char getCharAt(int index) const { return m_data.m_data ? m_data.m_data->data[index] : 0; }
private:
    StringBase<char> m_data;
};
class UnicodeString
{
public:
    UnicodeString() {}
    UnicodeString(const UnicodeString &that) : m_data(that.m_data) {}
    ~UnicodeString() { m_data.releaseBuffer(); }
    void translate(const AsciiString &that);
    void __cdecl format(const wchar_t *format, ...);
    // NOTE: this TU also emits ?str@UnicodeString@@QBEPBGXZ, which the link
    // census calls a loser (first copy lives in a ZH-port TU). It cannot be
    // declaration-only or reshaped from here: the Version rows above inline
    // it together with StringBase<wchar_t>::str and reference that static
    // TheNullChr, so any body change breaks their 5/5 match.
    const wchar_t *str() const { return m_data.str(); }
private:
    StringBase<wchar_t> m_data;
};

// Retail fetch call uses vtable offset 0x3c. The fourteen preceding
// non-destructor methods have not yet been reconstructed in this TU.
class GameTextInterface
{
public:
    virtual ~GameTextInterface() {}
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

// The engine initializer at RVA 0x22E6A6 passes this address to the GameText
// factory, and the retail accessor bodies load the singleton from this VA.
extern GameTextInterface *TheGameText;

class Version
{
public:
    UnicodeString getUnicodeVersion();
    UnicodeString getFullUnicodeVersion();
    UnicodeString getUnicodeBuildTime();
    UnicodeString getUnicodeBuildLocation();
    UnicodeString getUnicodeBuildUser();

private:
    int m_major;
    int m_minor;
    int m_buildNum;
    int m_localBuildNum;
    AsciiString m_buildTitle;
    AsciiString m_buildLocation;
    AsciiString m_buildUser;
    AsciiString m_buildGuid;
    AsciiString m_buildTime;
    AsciiString m_buildDate;
    AsciiString m_buildConfiguration;
    bool m_showFullVersion;
};

UnicodeString Version::getUnicodeVersion()
{
    UnicodeString version;
    version.format(TheGameText->fetch("Version:Format2").str(), m_major, m_minor);
    return version;
}

UnicodeString Version::getFullUnicodeVersion()
{
    UnicodeString version;

    if (!m_localBuildNum)
        version.format(TheGameText->fetch("Version:Format3").str(), m_major, m_minor, m_buildNum);
    else
        version.format(TheGameText->fetch("Version:Format4").str(), m_major, m_minor, m_buildNum, m_localBuildNum,
            m_buildUser.getCharAt(0), m_buildUser.getCharAt(1));

    return version;
}

UnicodeString Version::getUnicodeBuildTime()
{
    UnicodeString build;
    UnicodeString dateStr;
    UnicodeString timeStr;

    dateStr.translate(m_buildDate);
    timeStr.translate(m_buildTime);
    build.format(TheGameText->fetch("Version:BuildTime").str(),
        dateStr.str(), timeStr.str());

    return build;
}

UnicodeString Version::getUnicodeBuildLocation()
{
    UnicodeString build;
    UnicodeString machine;

    machine.translate(AsciiString(m_buildLocation));
    build.format(TheGameText->fetch("Version:BuildMachine").str(),
        machine.str());

    return build;
}

UnicodeString Version::getUnicodeBuildUser()
{
    UnicodeString build;
    UnicodeString user;

    user.translate(AsciiString(m_buildUser));
    build.format(TheGameText->fetch("Version:BuildUser").str(),
        user.str());

    return build;
}
