// cl: /O1 /MD
// Target 0x0006577F: pool lock with an atomic test-and-set and a yield on contention.
class BFMEPoolCriticalSection
{
public:
    void Lock();
private:
    unsigned int m_locked;
};

void BFMEPoolYield();

void BFMEPoolCriticalSection::Lock()
{
    unsigned int *lockWord = &m_locked;
    __asm mov ebx, lockWord
    __asm lock bts dword ptr [ebx], 0
    __asm jc retry
    __asm jmp acquired
retry:
    BFMEPoolYield();
    __asm mov ebx, lockWord
    __asm lock bts dword ptr [ebx], 0
    __asm jc retry
acquired:
    ;
}
