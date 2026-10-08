// cl: /MD
// Retail RVA 0x00216670, 75 bytes.
// ?SetBannerSlotXOffset@BannerUI@@QAEXIM@Z chain from just-landed 0x00216517: banner offset guard.
// __thiscall Banner setter with (index float): if new float equals slot at +0x3c return; if flag at +0x20 fire SetBannerXOffset via 0x00216517 then store.
// Evidence: callee 0x00216517 rowed int-return firer; callers 0x0052A2F4 0x0052A52B 0x0052AB56; literal SetBannerXOffset; global TheRva00222A8BTarget 0x009FE4CC.
class Rva00222A8BTarget;

struct BfmePod28 { int a[7]; };

BfmePod28 *Rva0021618AFind(BfmePod28 *first,BfmePod28 *last,int key);

namespace _STL {

template <class T> class allocator {};
template <class T, class A> class vector {
public:
	typedef T *iterator;
	iterator erase(iterator position);
private:
	iterator _M_start;
	iterator _M_finish;
	iterator _M_end;
};
}

int __cdecl Rva00216517Fire(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int *pInt, const float *pFloat);
int __cdecl Rva002162CFInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &arg);

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class BannerUI
{
	char m_pad00[0x20];
	unsigned char m_flag20;
	char m_pad21[3];
	void *m_owner24;
	BfmePod28 *m_itemsBegin;
	BfmePod28 *m_itemsEnd;
	char m_pad30[0x0C];
	float m_values3C[2]; // native21725B..21726F initializes3C..44 only
public:
	void SetBannerSlotXOffset(unsigned int index, float value);
	void RemoveBanner(int value);
};

void BannerUI::SetBannerSlotXOffset(unsigned int index, float value)
{
	float *slot = &m_values3C[index];
	if (value == *slot)
		return;
	if (m_flag20)
		Rva00216517Fire((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_owner24, "SetBannerXOffset", &index, &value);
	*slot = value;
}

// The target's literal at 0x00BE58A0 is "DeleteBanner". It uses the same
// owner field at +0x24 and adjacent container view at +0x28 as SetBannerSlotXOffset.
// WB B6E700 calls this RemoveBanner and asserts that the handle exists.
// Native216621..216670 searches28-byte records by the by-value integer
// handle, fires DeleteBanner, and erases the matching iterator. The former
// fill/count/reference ABI was refuted by the same WB/native search chain.
void BannerUI::RemoveBanner(int value)
{
	BfmePod28 *end = m_itemsEnd;
	BfmePod28 *newEnd = Rva0021618AFind(m_itemsBegin,end,value);
	bool alreadyAtEnd = newEnd == end;
	BfmePod28 * volatile savedEnd = newEnd;
	if (!alreadyAtEnd) {
		Rva002162CFInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,
			m_owner24, "DeleteBanner", *(const unsigned int *)&value);
		((_STL::vector<BfmePod28, _STL::allocator<BfmePod28> > *)&m_itemsBegin)->erase((BfmePod28 *)savedEnd);
	}
}
