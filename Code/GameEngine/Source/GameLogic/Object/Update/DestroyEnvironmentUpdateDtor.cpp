// cl: /DNDEBUG /MD /EHsc
//
// ??1DestroyEnvironmentUpdate@@UAE@XZ, retail 0x004AC767, 70 bytes (pinned;
// deleting wrapper 0x004AC7AD). Stores the three vtables, calls the helper
// 0x004AC722 on this in EH state 0, then the opaque MI base dtor 0x0024A797
// (retail's unwind map destroys only that base). The helper is BFME1's
// destructor body moved out of line: it resolves the object ID at +0x24,
// releases the attached module and destroys the object, then clears the ID
// (BFME1 donor DestroyEnvironmentUpdateDestructorThunk.cpp). It passes the
// object to 0x004AC5F5 in eax, so it stays unrecovered; it is pinned here
// under an address name from this call. Base layout follows
// Rva0024A797Derived.cpp; the +0x20/+0x24 members follow the rowed ctor.
class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class DestroyEnvironmentUpdate_B2
{
public:
	virtual void f2();
};

class DestroyEnvironmentUpdate : public UpdateModule, public MiBase1, public DestroyEnvironmentUpdate_B2
{
public:
	virtual ~DestroyEnvironmentUpdate();
	void rva004AC722();
private:
	char m_pad14[0x0C];
	unsigned int m_nextCallFrame;
	unsigned int m_objectID;
};

DestroyEnvironmentUpdate::~DestroyEnvironmentUpdate()
{
	rva004AC722();
}
