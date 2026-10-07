// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?allow@FilePathGate@@QAE_NPBD@Z, retail 0x00600AE5, 212 bytes.
// The path gate FileSystem::doesFileExist / openFile consult (thiscall from
// 0x00600D7D): drive-qualified paths and ".big" archives always pass;
// otherwise the path is copied, normalized (0x00605324) and looked up in a
// two-level strcmp-keyed map at +0x00 (directory -> file names, the
// 0x00603A2D _M_find family, as in stlport_cstring_tree_lookup_00603C0F.cpp):
// a listed directory, or a listed name under its parent directory
// (0x006053AD splits it; "" at 0x00BBAC1C for a bare name), answers the
// bool at +0x0C, anything else its negation. ".big" is the literal at
// 0x00C7A678 and _strcmpi is called through its import slot. The method name
// is the existing pin's (unproven); the member names are descriptive.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <string.h>

struct Rva00603A00Mapped
{
	unsigned int m_bits;
};

struct Rva006038D4Less
{
	bool operator()(const char *a, const char *b) const;
};

typedef _STL::map<const char*, Rva00603A00Mapped, Rva006038D4Less> FilePathGateNames;
typedef _STL::map<const char*, FilePathGateNames, Rva006038D4Less> FilePathGateDirs;

void Rva00605324(char *path);
char *Rva006053AD(char *path);

class FilePathGate
{
public:
	bool allow(const char *filename);
private:
	FilePathGateDirs m_dirs;
	bool m_listed;
};

bool FilePathGate::allow(const char *filename)
{
	if (filename)
	{
		if (filename[0] != 0 && filename[1] == ':')
			return true;
		int len = strlen(filename);
		if (len > 4 && _strcmpi(filename + len - 4, ".big") == 0)
			return true;
	}

	char path[260];
	strcpy(path, filename);
	Rva00605324(path);

	filename = path;
	FilePathGateDirs::iterator dir = m_dirs.find(filename);
	if (dir != m_dirs.end())
		return m_listed;

	char *name = Rva006053AD(path);
	filename = path;
	if (name == path)
		filename = "";
	dir = m_dirs.find(filename);
	if (dir != m_dirs.end())
	{
		FilePathGateNames *names = &(*dir).second;
		FilePathGateNames::iterator it = names->find(name);
		if (it != names->end())
			return m_listed;
	}
	return !m_listed;
}
