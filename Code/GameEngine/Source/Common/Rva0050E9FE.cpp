// cl: /GX-
// ?Rva0050E9FEAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAPBD@Z @0x0050E9FE 36B: chain via 0x00222B19 thiscall. Evidence: 5 stack args, ECX=arg1 plus 9 pushes (4x0 plus *arg5 plus 1 plus arg4/3/2) to rowed AptCall thiscall.
class Rva00222A8BTarget
{
public:
    int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr)
{
    const char *a0 = *a0ptr;
    return target->rva00222B19(level, prefix, function, 1, a0, 0, 0, 0, 0);
}
