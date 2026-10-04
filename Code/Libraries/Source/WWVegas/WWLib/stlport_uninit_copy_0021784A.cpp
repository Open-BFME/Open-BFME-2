// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?dup_0021781D@@YAXXZ @0x0021781D callee (rowed dup _Construct)
class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		unsigned char m_data[0x10];
	};
};

void __cdecl dup_0021781D();

typedef void (__cdecl *CtorFn)(MixFileCreator::FileInfoStruct *, const MixFileCreator::FileInfoStruct &);

// ?Rva0021784ACopy@@YAPAUFileInfoStruct@MixFileCreator@@PAU12@00@Z @0x0021784A 38B
// Unlock uninitialized_copy loop stride 0x10 calling rowed dup _Construct at
// 0x0021781D. Evidence: pushes plus call plus pop ecx interleaved adds; same
// family as rowed __uninitialized_copy 0x000C2438 38B; callers at 0x00218B5E.
// True __uninitialized_copy name spent at 0x000642AF so land honest free name;
// dup callee reached by its ledger name via cast.
MixFileCreator::FileInfoStruct *Rva0021784ACopy(MixFileCreator::FileInfoStruct *first,
	MixFileCreator::FileInfoStruct *last, MixFileCreator::FileInfoStruct *result)
{
	MixFileCreator::FileInfoStruct *cur = result;
	for (; first != last; ++first, ++cur)
		((CtorFn)dup_0021781D)(cur, *first);
	return cur;
}
