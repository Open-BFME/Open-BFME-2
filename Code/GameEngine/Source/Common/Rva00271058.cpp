// cl: /MD
// ?rva00271058@Rva00271058@@QAEXPAX@Z @0x00271058 61B: nullable slot at +0x100 via global registry erase 0x00239C38 store 0x00239FA0 at 0x009FE77C. Evidence: callers 0x00238E36 0x00246677; same shape as 0x00239FA0 0x00239C38 family.
class Rva0055A88BDwordField;
class Rva00239C38
{
public:
	void rva00239C38(const Rva0055A88BDwordField *arg);
};
class Rva00239FA0
{
public:
	void rva00239FA0(const Rva0055A88BDwordField *arg);
};
class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;
class Rva00271058
{
	char m_pad[0x100];
	void *m_ptr;
public:
	void rva00271058(void *p);
};
void Rva00271058::rva00271058(void *p)
{
	if (m_ptr != p) {
		if (m_ptr) {
			reinterpret_cast<Rva00239C38 *>(((ClientFrameSubsystem *)TheGameClient))->rva00239C38((const Rva0055A88BDwordField *)this);
		}
		m_ptr = p;
		if (p) {
			reinterpret_cast<Rva00239FA0 *>(((ClientFrameSubsystem *)TheGameClient))->rva00239FA0((const Rva0055A88BDwordField *)this);
		}
	}
}
