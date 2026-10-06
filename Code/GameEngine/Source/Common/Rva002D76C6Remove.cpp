// cl: /MD
// ?Rva002D76C6Remove@@YG_NPAURva002D76C6Owner@@PAPAURva002D76C6Node@@@Z @0x002D76C6 78B: unlink node whose +4 is owner then virtual delete.
// Callers 0x002D772A 0x002D773A pass owner in esi slot and list heads at +0x18/+0x14; LINK via 0x002D7714.
struct Rva002D76C6Node
{
    virtual void *v0(int);
    void *m04;
    Rva002D76C6Node *m08;
};
struct Rva002D76C6Owner
{
    char pad[0x260];
    int m260;
};
void __cdecl operator delete(void *);
bool __stdcall Rva002D76C6Remove(Rva002D76C6Owner *owner, Rva002D76C6Node **head)
{
    Rva002D76C6Node *cur = *head;
    Rva002D76C6Node *prev = 0;
    while (cur)
    {
        if (cur->m04 == owner)
            goto found;
        prev = cur;
        cur = cur->m08;
    }
    return false;
found:
    if (!prev)
        *head = cur->m08;
    else
        prev->m08 = cur->m08;
    owner->m260 = 0;
    void *p = cur->v0(0);
    ::operator delete(p);
    return true;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva002D76C6@Rva002D7714@@QAE_NPAURva002D76C6Owner@@PAPAURva002D76C6Node@@@Z=?Rva002D76C6Remove@@YG_NPAURva002D76C6Owner@@PAPAURva002D76C6Node@@@Z")
