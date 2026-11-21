#ifndef DEBUG_IO_H
#define DEBUG_IO_H

class Debug;

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface() {}

public:
    explicit DebugIOInterface() {}

    enum StringType
    {
        Assert,
        Log,
        Crash,
        Exception,
        CmdReply,
        StructuredCmdReply,
        Other,
        MAX
    };

    virtual int Read(char *buf, int maxchar) = 0;
    // Debug::GetInput checks this slot before calling Read.
    virtual bool HasInput();
    virtual void Write(StringType type, const char *src, const char *str) = 0;
    virtual void EmergencyFlush() = 0;
    virtual void Execute(Debug &dbg, const char *cmd, bool structuredCmd,
        unsigned argn, const char *const *argv) = 0;
    virtual void Delete() = 0;
};

#endif // DEBUG_IO_H
