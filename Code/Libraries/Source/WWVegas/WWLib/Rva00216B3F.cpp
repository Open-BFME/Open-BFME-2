// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Hide@BannerUI@@QAEX_N@Z, retail 0x00216B3F, 65 bytes.
// Guards on TheRva00222A8BTarget null then branches on bool param: true calls
// pinned rva0022277D with +0x24 and erases pod28 range at +0x28 clearing +0x20,
// false calls rowed ShowLevel with +0x24 as int. Evidence: global 0x009FE4CC
// extern name in use; callees rowed 0x005842F7 0x002224FE pinned 0x0022277D;
// callers at 0x00216D32 0x00402A62 0x00402AD3; prev/next STLport pod28 TUs.
#include <vector>

struct BfmePod28 { int a[7]; };

class Rva00222A8BTarget
{
public:

};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class AptPlayer
{
public:
	bool HideLevel(int);
	bool ShowLevel(int index);
};

class BannerUI
{
public:
	void Hide(bool on);
private:
	char m_pad00[0x20];
	unsigned char m_flag20;
	char m_pad21[3];
	void *m_ptr24;
	_STL::vector<BfmePod28> m_vec28;
	bool m_flag34;
};

void BannerUI::Hide(bool on)
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	m_flag34 = on;
	if (on)
	{
		reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->HideLevel((int)m_ptr24);
		_STL::vector<BfmePod28> &vr = m_vec28;
		vr.erase(vr.begin(), vr.end());
		m_flag20 = 0;
	}
	else
	{
		((AptPlayer *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->ShowLevel((int)m_ptr24);
	}
}
