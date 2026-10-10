// cl: /MD
// Native73EEBB..73EECA RET0. Previous body ends RET4; the next is the
// separately verified22B clear73EECA. Reads one pointer at receiver+0,
// null checks it and passes pointee+8 to the owned fastcall release7DEEF.
// Does not clear the receiver pointer. Original class, method name and
// lifetime role remain unresolved; this is only a target ABI view.
// Kept separate from the adjacent list unit's pre-existing COMDAT debt.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva0073EEBBHandleRelease {
    char *handle;
    void release();
};
void Rva0073EEBBHandleRelease::release() {
    if (handle)
        ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(handle + 8));
}
