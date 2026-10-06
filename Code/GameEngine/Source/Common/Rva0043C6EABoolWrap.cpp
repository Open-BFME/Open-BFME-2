// cl: /GX-
// ?rva0043C6EA@Rva0043C6EA@@QAE_NH@Z @0x0043C6EA 27B.
// Bool wrapper around virtual slot 2: clears a bool out-flag, forwards the
// int arg plus the flag address through slot 2 ([eax+8]), and returns the
// flag. Caller at 0x0043D0E8 passes a sub-object at esi+0x288 as this and an
// int index (checked against -1) as the arg. Class proven by the
// same-object call in 0x0043CD3C only; honest Rva name. Unlock lane.
class Rva0043C6EA
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2(int arg, bool &out);
	bool rva0043C6EA(int arg);
};

bool Rva0043C6EA::rva0043C6EA(int arg)
{
	bool ok = false;
	v2(arg, ok);
	return ok;
}
