// cl: -Oy- -GR- -EHsc-
// ?rva0059E2DC@@YA_NPAPAVFileClass@@0URva0059E2DCBox@@@Z @0x0059E2DC 33B:
// iterate [first, last), invoking the pinned thiscall callee (0x004FC957,
// matched as W3DFileSystem::Return_File) on a by-value box with each element,
// then return the box's low byte. The lea-ecx + single push with no caller
// cleanup is a thiscall whose callee pops its own explicit arg (ret 4).
class FileClass;

// The callee is the rowed W3DFileSystem::Return_File, called directly.
class W3DFileSystem
{
public:
	virtual void Return_File(FileClass *file);
};

struct Rva0059E2DCBox
{
	bool flag;
	char pad[3];
};

bool __cdecl rva0059E2DC(FileClass **first, FileClass **last, Rva0059E2DCBox box)
{
	for (; first != last; ++first)
		((W3DFileSystem *)&box)->W3DFileSystem::Return_File(*first);
	return box.flag;
}
