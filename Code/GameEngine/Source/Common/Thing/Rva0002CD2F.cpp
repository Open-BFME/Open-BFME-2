// cl: /Ireference/shims/bfme2_ascii /O1
// stlport
// ?rva0002CD2F@Rva0002CD2F@@QAEPAUOut0002CA72@@PAU2@PBUPair0002CA72@@@Z @0x0002CD2F 36B
// Evidence: unlock lane; hashtable insert wrapper forwarding (Out*, Pair*) to rowed
// insert_noresize 0x0002CA72 after grow 0x0002C7FD with count+1 from +0x10; callers
// 0x0002D1C3 0x0002D4EC; callees all rowed. Row 0x0002C7FD is gen-dump YAXXZ
// (TYPES wrong: retail passes count+1 with this in ECX and callee pops); declared
// as used via cast to stdcall 1-arg so the push survives while the relocation keeps
// the rowed name.
#include "ascii_string.h"

struct Out0002CA72;
struct Pair0002CA72;

void __cdecl d_0002c7fd(void);
struct Out0002CA72;
struct Pair0002CA72;
class Rva0002CA72
{
public:
    struct Out0002CA72 *rva0002CA72(struct Out0002CA72 *out, const struct Pair0002CA72 *obj);
};

class Rva0002CD2F
{
    char m_pad[16];
    unsigned int m_count;
public:
    struct Out0002CA72 *rva0002CD2F(struct Out0002CA72 *out, const struct Pair0002CA72 *obj);
};

struct Out0002CA72 *Rva0002CD2F::rva0002CD2F(struct Out0002CA72 *out, const struct Pair0002CA72 *obj)
{
    ((void (__stdcall *)(unsigned int))&d_0002c7fd)(m_count + 1);
    ((Rva0002CA72 *)this)->rva0002CA72(out, obj);
    return out;
}
