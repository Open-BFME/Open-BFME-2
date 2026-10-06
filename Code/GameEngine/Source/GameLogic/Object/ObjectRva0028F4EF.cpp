// cl: /DNDEBUG /MD
// ?rva0028F4EF@Object@@QAEHXZ @ 0x0028F4EF 41B: Object KindOf tri-state
// returning 0 if isKindOf(0x222) else 1 if isKindOf(0x223) else 2. Uses
// rowed ?isKindOf@Object@@QBE_NW4KindOfType@@@Z. Callers include 0x0028F518
// plus 8 others. Prev ObjectRva0028F4BC same flags.
enum KindOfType
{
	K_222 = 0x222,
	K_223 = 0x223
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;
	int rva0028F4EF();
};

int Object::rva0028F4EF()
{
	if (isKindOf(K_222))
		return 0;
	return isKindOf(K_223) ? 1 : 2;
}
