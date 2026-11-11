// cl: /MD /DNDEBUG
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

#include "../../../Libraries/Source/Apt/Rva8D0D80Result.h"

class AptFrameStack;
extern "C" AptFrameStack *__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A");

// LINK: the list call is rowed as Rva006FBC90Owner::rva006FBBA0 (0x006FBBA0).
class EAStringC;
class AptValue;
class Rva006FBC90Owner
{
public:
	bool rva006FBBA0(const EAStringC *name, AptValue *value);
};

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
	Rva8D0D80Result *list = __identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A") ? (Rva8D0D80Result *)__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A") : m_list;
	if (list == 0)
		return false;
	return ((Rva006FBC90Owner *)list)->rva006FBBA0((const EAStringC *)name, (AptValue *)value);
}
