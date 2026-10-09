// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::LogBegin.  The BFME Debug object keeps the log mutex and
// current-thread owner at +0x9F50/+0x9F54, while the frame state remains at
// the Zero Hour Debug offsets.

#include <string.h>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *, unsigned long);
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(
    void);

struct DebugIOInterface
{
    // Minimal StringType for StartOutput's mangled name (values unused in
    // this TU; retail keeps 7 types with Log==1).
    enum StringType { Assert, Check, Log, Crash, Exception, CmdReply, StructuredCmdReply, Other, MAX };
};

class Debug
{
public:
    virtual ~Debug(void);
    virtual void pad01(void);
    virtual void pad02(void);
    virtual void pad03(void);
    virtual void pad04(void);
    virtual void pad05(void);
    virtual void pad06(void);
    virtual void pad07(void);
    virtual void pad08(void);
    virtual void pad09(void);
    virtual void pad10(void);
    virtual void pad11(void);
    virtual void pad12(void);
    virtual void pad13(void);
    virtual Debug &operator<<(const char *);
    virtual void pad15(void);
    virtual void pad16(void);
    virtual void pad17(void);
    virtual void pad18(void);
    // (No pad19: with the two retail FlushOutput/StartOutput declarations
    // below present, the compiler numbers StartOutput above at retail slot
    // 0x50; keeping pad19 puts it at 0x54. Verified by build.)
    virtual void StartOutput(const char *, unsigned);

    struct FrameHashEntry
    {
        FrameHashEntry *next;
        unsigned frameAddr;
        unsigned frameType;
        const char *fileOrGroup;
        int line;
        int hits;
        int status;
    };

private:
    unsigned char m_pad04[8];
    void *firstIOFactory;
    unsigned char m_pad10[4];
    unsigned curStackFrame;
    unsigned char m_pad18[0x9CDC];
    int curType;
    char curSource[256];
    int disableAssertsEtc;
    FrameHashEntry *curFrameEntry;
    unsigned char m_pad9E00[0x15C];
    void *m_mutex;
    unsigned m_threadId;

    FrameHashEntry *GetFrameEntry(unsigned, unsigned, const char *, int);

    // Retail Debug::FlushOutput / Debug::StartOutput (0x39300 / 0x39B30).
    // Virtual so the declarations reproduce their exact mangled names;
    // every call below qualifies them explicitly to keep the direct calls
    // retail emits. Appended after the established vtable slots.
    virtual void FlushOutput(bool);
    virtual void StartOutput(DebugIOInterface::StringType, const char *, ...);

public:
    virtual Debug &LogBegin(const char *);	// slot 26 of 0x00BBE810
};

// ?LogBegin@Debug@@UAEAAV1@PBD@Z
Debug &Debug::LogBegin(const char *fileOrGroup)
{
    WaitForSingleObject(m_mutex,100);

    if (curType!=7)
    {
        if (curType!=1 || m_threadId!=GetCurrentThreadId())
            Debug::FlushOutput(true);
    }

    curFrameEntry=GetFrameEntry(curStackFrame,4,fileOrGroup,0);
    if (curFrameEntry->status==2 || curFrameEntry->status==3 ||
        curFrameEntry->status==0)
    {
        StartOutput("",10);
        ++curFrameEntry->hits;

        if (curType==1 &&
            strcmp(curSource,curFrameEntry->fileOrGroup))
            Debug::FlushOutput(true);

        if (curType!=1)
            Debug::StartOutput((DebugIOInterface::StringType)1,"%s",
                      curFrameEntry->fileOrGroup);
    }
    else if (curType!=7)
        Debug::FlushOutput(true);

    return *this;
}
