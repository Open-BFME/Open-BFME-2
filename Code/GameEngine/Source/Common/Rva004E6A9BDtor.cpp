// cl: /MD /EHsc
// ??1InGameNotificationBoxMovieClip@@QAE@XZ @0x004E6A9B 157B
// Native vtable 0x862440 is the named movie-clip constructor's five-slot table;
// its destructor restores the five-purecall base at 0x8078DC.
// The holder offsets and cleanup sequence agree with the named 84-byte class.
class Rva00222A8BTarget;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../../Libraries/Source/Apt/AptPlayerClass.h"
class DisplayStringManager
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(int v);
};
extern DisplayStringManager *TheDisplayStringManager;
class Rva004E6A1D
{
public:
    ~Rva004E6A1D();
    void clear();
    void *m_ptr;
};
#include "../../Include/Common/Rva0052413E.h"
class Rva005241B0
{
public:
    ~Rva005241B0();
    char m_pad[12];
};
class Rva00524265
{
public:
    ~Rva00524265();
    char m_pad[12];
};
class Rva005242D7
{
public:
    ~Rva005242D7();
    char m_pad[16];
};
class UnicodeString;
class Rva002217EA;
class Rva004E6A9BBase
{
public:
    virtual unsigned char rva00578522() const = 0;
    virtual void rva004E6B7D(bool) = 0;
    virtual void rva004E725F(const UnicodeString &, const Rva002217EA &, int) = 0;
    virtual void DoClose() = 0;
    virtual int rva004E6882() = 0;
    ~Rva004E6A9BBase() {}
};
class InGameNotificationBoxMovieClip : public Rva004E6A9BBase
{
public:
    ~InGameNotificationBoxMovieClip();
    virtual unsigned char rva00578522() const;
    virtual void rva004E6B7D(bool);
    virtual void rva004E725F(const UnicodeString &, const Rva002217EA &, int);
    virtual void DoClose();
    virtual int rva004E6882();
    int m04;
    char m_pad08[4];
    Rva0052413E m0C;
    Rva005241B0 m18;
    Rva00524265 m24;
    Rva005242D7 m30;
    Rva004E6A1D m40;
    Rva004E6A1D m44;
    int m48;
    int m4C;
};
InGameNotificationBoxMovieClip::~InGameNotificationBoxMovieClip()
{
    if (((Rva00222A8BTarget *)g_bfmeAptWindowManager))
        ((AptPlayer *)g_bfmeAptWindowManager)->RemoveLevel(m04);
    if (TheDisplayStringManager)
        TheDisplayStringManager->v15(m4C);
}
