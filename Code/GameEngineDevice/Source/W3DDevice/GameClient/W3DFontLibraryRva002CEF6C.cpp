// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva002CEF6C@W3DFontLibrary@@QAE_NPAX@Z, retail 0x002CEF6C..0x002CEF80 (20
// bytes, RET 4): slot 27 of W3DFontLibrary's vtable. It runs the 752-byte
// 0x0050CBA2 (not yet rowed; pinned) on an empty local built from the
// argument -- the compiler gives that local the argument's own stack slot --
// and answers true. WorldBuilder's twin (0x00A96690) is unnamed.

class Rva0050CBA2
{
public:
	Rva0050CBA2(void *arg);
};

class W3DFontLibrary
{
public:
	bool rva002CEF6C(void *arg);
};

bool W3DFontLibrary::rva002CEF6C(void *arg)
{
	Rva0050CBA2 helper(arg);
	return true;
}
