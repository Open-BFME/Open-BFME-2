// cl: /O1 /MD /DNDEBUG
// stlport
//
// ??0RemoveUpgradeUpgradeModuleData@@QAE@XZ, retail 0x004B7FF1, 67 bytes
// (EBP-frame): base call into the rowed OpenContainModuleData 0x253487,
// compiler vtable store at +0 (pinned ??_7 at 0xC58EF0, slot0 is the ??_G
// at 0x4B8034 sitting right after the ctor), two BfmeE16 vectors at
// +0x118/+0x124 via the rowed Vector_base 0x211E58, bytes at +0x130/+0x131.
// The own table holds UpgradeToRemove at +0x118 plus UpgradeGroupsToRemove
// at +0x124 plus SuppressEvaEventForRemoval at +0x130 plus
// RemoveFromAllPlayerObjects at +0x131. The owning factory at 0x0025082A
// (news 0x134) is the sole caller; the pool key at 0x4B7F3D names the
// class. Row supersedes the ctor pin.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class __declspec(novtable) OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	unsigned m_pad04;
	unsigned char m_member08[0x110];
};

class RemoveUpgradeUpgradeModuleData : public OpenContainModuleData
{
public:
	RemoveUpgradeUpgradeModuleData();
	virtual ~RemoveUpgradeUpgradeModuleData();

	_STL::vector<BfmeE16> m_upgradeToRemove;
	_STL::vector<BfmeE16> m_upgradeGroupsToRemove;
	unsigned char m_suppressEvaEventForRemoval;
	unsigned char m_removeFromAllPlayerObjects;
};

RemoveUpgradeUpgradeModuleData::RemoveUpgradeUpgradeModuleData()
	: OpenContainModuleData()
{
	m_suppressEvaEventForRemoval = 0;
	m_removeFromAllPlayerObjects = 0;
}
