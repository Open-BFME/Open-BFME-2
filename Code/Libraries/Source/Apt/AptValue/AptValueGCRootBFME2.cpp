// cl: /MD
// PC-derived AptValue.inl GCRoot family. Same assertion mechanism as the
// already matched AptValueSetTypeBFME2.cpp; no cross-game layout imported.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
    struct {
        unsigned int unknown : 18;
        unsigned int gcRootCount : 7;
        unsigned int type : 7;
    } flags;
public:
    void setGCRootCount(unsigned int nRoot);
    void incrementGCRootCount();
    void decrementGCRootCount();
    unsigned int getGCRootCount() const;
};
// Descriptive method names: PC assertions independently name mnGCRootCount;
// positions18..24 at this+4 are measured from PC code. Existing BFME1 type
// predicates informed bitfield C++ shaping, but their low-bit type layout
// does not transfer. Godfather PDB research is reference only, not proof.

void BfmeAptValue006DCD20::setGCRootCount(unsigned int nRoot)
{
    if (!(nRoot <= 127)) {
        g_bfmeAptAssertAtE17734("(nRoot >= 0) && (nRoot <= MAX_GCROOT)","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",400);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    flags.gcRootCount = nRoot;
}

void BfmeAptValue006DCD20::incrementGCRootCount()
{
    if (!(flags.gcRootCount < 127)) {
        g_bfmeAptAssertAtE17734("mValueBitfield.mnGCRootCount < MAX_GCROOT","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",425);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.gcRootCount < 127) ++flags.gcRootCount;
}

void BfmeAptValue006DCD20::decrementGCRootCount()
{
    if (!(flags.gcRootCount > 0)) {
        g_bfmeAptAssertAtE17734("mValueBitfield.mnGCRootCount > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl",453);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (flags.gcRootCount > 0) --flags.gcRootCount;
}

unsigned int BfmeAptValue006DCD20::getGCRootCount() const { return flags.gcRootCount; }
