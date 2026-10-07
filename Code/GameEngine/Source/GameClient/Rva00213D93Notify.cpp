// ?rva00213D93@Rva00213D93@@QAEXPAVRva00213D93Target@@@Z
// cl: /O1 /DNDEBUG /MD /EHsc
// Native213D93..213DFD RET4. This is the secondary view12 bytes after
// LivingWorldManager: the primary receiver feeds two target-taking workers
// and rowed SetUpRegionEffectsManager. Its observer pointer is at view2B8.
// Original notification and target identities remain unresolved.
// Only the two flag bytes are consumed. The trailing bytes model the native
// reused four-byte temporary slot without claiming an original type size.
struct Rva00213D93Flags { bool first; bool second; char unused02[2]; };
class Rva00213D93Target
{
public:
    virtual void slot00() = 0;
    virtual bool slot04() = 0;
    virtual void slot08() = 0;
    virtual bool slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28(const Rva00213D93Flags *) = 0;
};
class LivingWorldManager
{
public:
    void rva0021219E(Rva00213D93Target *target);
    void rva00213C6E(Rva00213D93Target *target);
    void SetUpRegionEffectsManager();
};
class Rva00213D93Observer
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C(Rva00213D93Target *) = 0;
};
class Rva00213D93
{
    char unknown00[0x2B8];
    Rva00213D93Observer *observer;
public:
    void rva00213D93(Rva00213D93Target *target);
};
void Rva00213D93::rva00213D93(Rva00213D93Target *target)
{
    if (!target->slot0C())
    {
        Rva00213D93Flags flags;
        flags.first = true;
        flags.second = true;
        target->slot28(&flags);
        LivingWorldManager *manager = reinterpret_cast<LivingWorldManager *>(reinterpret_cast<char *>(this) - 12);
        manager->rva0021219E(target);
        manager->rva00213C6E(target);
        if (observer)
            observer->slot0C(target);
        if (target->slot04())
            manager->SetUpRegionEffectsManager();
    }
}
