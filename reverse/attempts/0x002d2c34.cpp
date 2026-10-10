// ?rva002D2C34@Rva002D2C34@@QAEXXZ
// partial score=0.65 date=2026-10-10
// cl: /DNDEBUG /MD
//
// ?rva002D2C34@Rva002D2C34@@QAEXXZ @0x002D2C34 (~106B). BANKED ATTEMPT.
// Direct-ctor shape probe for the Apt record body: five ObjectCreationList
// members plus a 24B member via rowed ctors. Retail stores the 0x00C02A80
// vtable AFTER the six member calls; a direct ctor stores it first. Retail
// is called as a plain method by 13 Apt units, but no clean C++ method
// formulation reproduces the single-scope EH states plus late vtable:
// method+inline-ctor splits shift the states and add a null guard or tail
// jump, per-member placement news cannot store the vtable, and a thunk
// breaks the callers REL32s. See the re_log partial for the full analysis.
class ObjectCreationList
{
public:
	ObjectCreationList();
	~ObjectCreationList();
private:
	char m_pad[12];
};

class Rva00524415
{
public:
	Rva00524415();
	~Rva00524415();
private:
	char m_pad[24];
};

class Rva002D2C34
{
public:
	virtual ~Rva002D2C34();
	Rva002D2C34();
private:
	ObjectCreationList m_04;
	ObjectCreationList m_10;
	Rva00524415 m_1C;
	ObjectCreationList m_34;
	ObjectCreationList m_40;
	ObjectCreationList m_4C;
};

Rva002D2C34::Rva002D2C34()
{
}
