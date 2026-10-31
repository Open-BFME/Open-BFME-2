// cl: /MD
// ?setID@Drawable@@QAEXPAX@Z @0x00271058 61B: nullable slot at +0x100 via global registry erase 0x00239C38 store 0x00239FA0 at 0x009FE77C. Evidence: callers 0x00238E36 0x00246677; same shape as 0x00239FA0 0x00239C38 family.
#include "../../Include/GameClient/DrawableBFME2.h"
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
void Drawable::setID(void *p)
{
	if ((void *)m_id != p) {
		if (m_id) {
			reinterpret_cast<Rva00239C38 *>(((ClientFrameSubsystem *)TheGameClient))->rva00239C38((const Rva0055A88BDwordField *)this);
		}
		m_id = (DrawableID)(int)p;
		if (p) {
			reinterpret_cast<Rva00239FA0 *>(((ClientFrameSubsystem *)TheGameClient))->rva00239FA0((const Rva0055A88BDwordField *)this);
		}
	}
}
