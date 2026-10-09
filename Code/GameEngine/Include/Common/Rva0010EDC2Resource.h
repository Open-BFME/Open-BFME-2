#pragma once
#include "ascii_string.h"
#include "Rva00041004Lock.h"

// Only the destructor ABI of this event view is consumed here. Its empty
// derived destructor reproduces the rowed 0x000411BC tail call to 0x00040EDB.
class __declspec(novtable) Rva000411BC : public Rva0040EDB
{
public:
    virtual ~Rva000411BC() {}
    virtual bool unlock();
};

// Address-derived owner: constructor 10ED4C copies the name at zero and
// initializes events at 44/4C. Destructor 10EDC2 observes the fields below;
// its FuncInfo 9089D4 owns exactly name00 and event44 in states zero and one.
// The second event is explicitly released on the normal path, so model its
// storage without adding an automatic cleanup absent from the retail graph.
// Original class identity and unobserved fields remain unknown.
class Rva0010EDC2
{
public:
    ~Rva0010EDC2();
    void *destroy(unsigned int flags);
private:
    AsciiString name00;
    int id04;
    char unmodelled08[0x24];
    void *payload2C;
    int unmodelled30;
    volatile int count34;
    int unmodelled38;
    int unmodelled3C;
    unsigned char miles40;
    Rva000411BC event44;
    char event4C[8];
};
