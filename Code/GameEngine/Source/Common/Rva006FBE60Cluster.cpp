// cl: /O2 /MD /DNDEBUG
// Rva006FBE60::rva006FBE60, retail 0x006FBE60 (29 B).
// Result-table forwarder: pick the live Rva8D0D80Result list (the global at
// 0x00E1835C, else the +0x28 member) and tail-jump to the row-blocked
// Rva8D0D80Result::rva006FBBA0 0x006FBBA0 find-or-add; a null list answers
// false.  Evidence: the sole call site 0x006FEE0D passes a String* and a
// Value* and the body is exactly the Rva8D0D80Result family shape (Table at
// +8, next at +0x1C in the callee).  The ternary spelling is what makes MSVC
// coalesce the chosen list into ecx, target evidence for this shape.
class Rva8D0D80String;
class Rva8D0D80Value;

class Rva8D0D80Result
{
public:
	bool rva006FBBA0(Rva8D0D80String *name, Rva8D0D80Value *value);
};

extern Rva8D0D80Result *g_rva00A1835C;

class Rva006FBE60
{
public:
	bool rva006FBE60(Rva8D0D80String *name, Rva8D0D80Value *value);

private:
	char m_pad[0x28];
	Rva8D0D80Result *m_list;	// +0x28
};

bool Rva006FBE60::rva006FBE60(Rva8D0D80String *name, Rva8D0D80Value *value)
{
	Rva8D0D80Result *list = g_rva00A1835C ? g_rva00A1835C : m_list;
	if (list == 0)
		return false;
	return list->rva006FBBA0(name, value);
}

// Native E1835C is the script-function current frame root. Bind its shared provider.
#pragma comment(linker, "/alternatename:?g_rva00A1835C@@3PAVRva8D0D80Result@@A=?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A")
