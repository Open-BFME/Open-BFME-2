// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 DockUpdate crippled-flag setter v2, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp).
// Retail BFME2 keeps the flag at the same offset (+0x65): crippling means
// approach requests are accepted but enter clearance is never granted.

class DockUpdate
{
public:
	virtual void setDockCrippled(bool setting);

private:
	unsigned char m_pre[0x61];	// implicit vptr at +0x0
	bool m_dockCrippled;	// +0x65
};

// ?setDockCrippled@DockUpdate@@UAEX_N@Z
void DockUpdate::setDockCrippled(bool setting)
{
	m_dockCrippled = setting;
}
