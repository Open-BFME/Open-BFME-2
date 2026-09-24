// cl: /O2
// CopyProtect installation-verdict flag, retail 0x002FB00 (set-once 26B) and
// 0x002FB20 (getter 15B). The flag lives at 0x009A7574 (VA 0x00DA7574) with a
// -1 sentinel for unset. Two writers agree on the verdict role: WinMain's
// launcher path stores CopyProtect::validate() at 0x000030EC and the edition
// probe stores FileSystem::doesFileExist("mithriledition.txt") at 0x001B53B8.
// The sole reader at 0x003779C9 gates its action on the flag reading 1.
// /O2 (not the family /O1) reproduces the load-first scheduling; the getter
// is flag-neutral. Kept in its own TU so WinMain cannot inline either body.

class CopyProtect
{
public:
	static void setVerified(bool verified);
	static bool isVerified(void);
private:
	static int s_verified;
};

int CopyProtect::s_verified = -1;

void CopyProtect::setVerified(bool verified)
{
	if (s_verified == -1)
	{
		s_verified = (verified != 0);
	}
}

bool CopyProtect::isVerified(void)
{
	return s_verified == 1;
}
