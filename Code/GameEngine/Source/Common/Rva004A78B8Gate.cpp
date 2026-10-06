// cl: /O1 /DNDEBUG /MD
//
// ?rva004A78B8@Rva004A78B8@@QAE_NH@Z @0x004A78B8 41B ret 4.
// Virtual slot 1 gates the thiscall at 0x0045CD6E. On that path the owner
// pointer at this-0x18 gets status 4 set. The function always returns true.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
};

class Rva004A78B8
{
public:
	virtual void slot0();
	virtual bool slot1();
	bool rva0045CD6E(int arg);
	bool rva004A78B8(int arg);
};

bool Rva004A78B8::rva004A78B8(int arg)
{
	if (slot1())
	{
		rva0045CD6E(arg);
		(*(Object **)((char *)this - 0x18))->setStatus((ObjectStatusTypes)4, true);
	}
	return true;
}
