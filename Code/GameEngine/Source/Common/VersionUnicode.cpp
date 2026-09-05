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
