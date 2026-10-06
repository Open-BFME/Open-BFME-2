// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00151288@Rva00151288@@QAEXPBD@Z, retail 0x00151288, 105 bytes.
// Path-surgery method on a StringBase<char> member at +8: release it, and
// when the input path is non-null split off fname+ext with _splitpath
// (drive/dir NULL), rebuild with _makepath, and set the member to the
// result. Callees are all rowed or IAT-pinned: private
// ?releaseBuffer@?$StringBase@D@@AAEXXZ (0x00036410), ?set@?$StringBase@D@@
// QAEXPBD@Z (0x000055F5), plus msvcr71 _splitpath/_makepath through IAT
// (FF15), hence __declspec(dllimport). The TU-local StringBase mirror keeps
// the real private access and befriends the enclosing class (a TU-scoped
// access shim; friendship is mangling-neutral). StringBase declaration
// follows string_base.h; frame sizes (buffer 0x204, ext/fname 0x100 each)
// from the retail sub esp and lea immediates. Unlocks four callers.

extern "C" {
__declspec(dllimport) void __cdecl _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
__declspec(dllimport) void __cdecl _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
}

template <typename T>
class StringBase
{
	friend class Rva00151288;

public:
	void set(const T *str);

private:
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class Rva00151288
{
public:
	void rva00151288(const char *path);

private:
	char m_pad00[8];
	StringBase<char> m_str08;
};

void Rva00151288::rva00151288(const char *path)
{
	m_str08.releaseBuffer();
	if (path != 0) {
		char buffer[0x204];
		char ext[0x100];
		char fname[0x100];
		_splitpath(path, 0, 0, fname, ext);
		_makepath(buffer, 0, 0, fname, ext);
		m_str08.set(buffer);
	}
}
