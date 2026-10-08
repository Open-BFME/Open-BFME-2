// cl: /O2 /G6 /DNDEBUG /MD /EHsc
// Native 00622670..00622679 is the complete nine-byte cdecl start routine.
// The recovered AssetManagerImpl constructor passes its address and this to
// _beginthread. Its sole tail call reaches the separately verified registry
// worker at 00622480. The original leaf name remains unknown.
class AssetRegistry
{
public:
    void Worker_Thread_00622480();
};

void __cdecl Rva00622670ThreadProc(void *instance)
{
    ((AssetRegistry *)instance)->Worker_Thread_00622480();
}
