// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00523F8C@Rva00524021@@QAEXXZ @0x00523F8C 96B
// Two-vector clear via rowed erase 0x0022453E plus StringBase::clear plus indexed erase 0x002245FF plus CameraMarker dtor 0x0029D7C2 with global TheRva00222A8BTarget guard at 0x009FE4CC. Evidence: chain via 0x002245FF; callers 0x0052444E 0x00524955; precedent Rva00524021Loop single-vector shape.
template <typename T> class StringBase
{
public:
	void clear();
private:
	void *m_data;
};

class AsciiString;

class AptPlayer
{
public:
	void RemoveOverButtonHandler(const AsciiString &key);
	void RemoveOverButtonHandler(int idx, const AsciiString &key);
};


#include "../../Include/GameClient/Rva002246B1.h"

class Rva002244CA
{
public:
	int RemoveExternHandler(const AsciiString *key);
};

#include "../../Include/Common/Rva00224455.h"

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct CameraMarker
{
	~CameraMarker();
	char m_pad[8];
};

class Rva00524021
{
public:
	void rva00523F8C();
	void rva00523FEC();
	void rva00523F57();
	void rva00523F22();
private:
	StringBase<char> *m_begin1;
	StringBase<char> *m_end1;
	char m_pad0[0xC - 0x8];
	CameraMarker *m_begin2;
	CameraMarker *m_end2;
};

void Rva00524021::rva00523F8C()
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	while (m_begin1 != m_end1) {
		((AptPlayer *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->RemoveOverButtonHandler(*(const AsciiString *)(m_end1 - 1));
		--m_end1;
		m_end1->clear();
	}
	while (m_begin2 != m_end2) {
		((AptPlayer *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->RemoveOverButtonHandler(*(int *)((char *)m_end2 - 8), *(const AsciiString *)((char *)m_end2 - 4));
		--m_end2;
		m_end2->~CameraMarker();
	}
}

void Rva00524021::rva00523FEC()
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	while (m_begin1 != m_end1) {
		((Rva002246B1 *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->RemoveCustomRender((const AsciiString *)(m_end1 - 1));
		--m_end1;
		m_end1->clear();
	}
}

void Rva00524021::rva00523F57()
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	while (m_begin1 != m_end1) {
		((Rva002244CA *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->RemoveExternHandler((const AsciiString *)(m_end1 - 1));
		--m_end1;
		m_end1->clear();
	}
}

void Rva00524021::rva00523F22()
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) == 0)
		return;
	while (m_begin1 != m_end1) {
		((Rva00224455 *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->RemoveCommandMap((const AsciiString *)(m_end1 - 1));
		--m_end1;
		m_end1->clear();
	}
}
