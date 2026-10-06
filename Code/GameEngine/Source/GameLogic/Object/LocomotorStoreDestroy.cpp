// cl: /MD
// ?Rva00220AEBDestroy@@YAXPAVLocomotorStore@@0@Z, retail 0x00220AEB 25B.
// Range-destroy for LocomotorStore array stride 0xC: calls rowed
// ??1LocomotorStore@@QAE@XZ at 0x002207C4 per element. Chain from that
// landing; callers 0x00220C17/0x00220C56 pass begin/end then free.
// Identity: stride matches LocomotorStore 12B layout, callee rowed.
class LocomotorStore
{
public:
    ~LocomotorStore();

private:
    void *m_slot00;
    void *m_slot04;
    unsigned m_templates08;
};

void __cdecl Rva00220AEBDestroy(LocomotorStore *first, LocomotorStore *last)
{
    for (; first != last; ++first)
        first->~LocomotorStore();
}
