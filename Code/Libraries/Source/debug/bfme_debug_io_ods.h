#ifndef INTERNAL_IO_H
#define INTERNAL_IO_H

#include "bfme_debug_io_interface.h"

class DebugIOOds : public DebugIOInterface
{
public:
    explicit DebugIOOds() {}

    virtual int Read(char *buf, int maxchar) { return 0; }
    virtual void Write(StringType type, const char *src, const char *str);
    virtual void EmergencyFlush() {}
    virtual void Execute(Debug &dbg, const char *cmd, bool structuredCmd,
        unsigned argn, const char *const *argv) {}
    virtual void Delete();

    static DebugIOInterface *Create();
};

#endif // INTERNAL_IO_H
