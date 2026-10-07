// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005D3B26@SelectionUIImpl@StrategicHUD@@QAEXXZ retail 0x005D3B26 116B
// Evidence: unlock twin of rowed 0x005D3B9A portrait; format row 0x00038150 releaseBuffer row 0x00036410; empty VA 0x007BAC1C manager VA 0x009FE4CC; pinned callee 0x002239E2; callers 0x005D3CF0 0x005D3D44
template <typename T> class StringBase;

class AsciiString;

#include "ascii_string.h"

class Image;

// Native image-store calls use the same manager pointer and target 0x2239E2.
// The verified provider takes a string name and an image pointer.
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &key, const Image *image);
};

class Rva00222A8BTarget
{
public:
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

namespace StrategicHUD {
class SelectionUIImpl;
}

// Native calls target RVA 0x5D3A91 with the unadjusted selection pointer.
// Use the existing verified worker view (fields +0x18/+0x1C/+0x24).
class Rva005D3A91
{
public:
	void rva005D3A91();
};

class StrategicHUD::SelectionUIImpl
{
public:
	void rva005D3B26();
	void Show();

	void *m_unused00;
	int m_level;
	Rva005D2FD0Inner *m_inner;
	char m_pad0C[0x14];
	const Image *m_image20;
	char m_pad24[0x0C];
	bool m_shown30;		// +0x30
	bool m_31;
	bool m_32;			// +0x32
};

void StrategicHUD::SelectionUIImpl::rva005D3B26()
{
	if (TheRva00222A8BTarget == 0)
		return;
	if (m_image20 == 0)
		return;
	AsciiString tmp;
	const char *name = m_inner ? m_inner->m_name : "";
	tmp.format("_level%u.%s_Portrait", m_level, name);
	reinterpret_cast<Rva002239B2 *>(TheRva00222A8BTarget)->rva002239E2(tmp, m_image20);
}
// ?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A: the global at VA 0xdfe4cc is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A.
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")

// ?Show@SelectionUIImpl@StrategicHUD@@QAEXXZ retail 0x005D3CFA 81B: show the panel once:
// SetState "_show" through the rowed Rva005FB5E6AptCall (TheRva00222A8BTarget,
// level, name), set the shown flag at +0x30, refresh the verified 0x005D3A91 worker when
// the flag at +0x32 is set, then tail-call the portrait refresh above.
void StrategicHUD::SelectionUIImpl::Show()
{
	if (m_shown30)
		return;
	const char *name = m_inner ? m_inner->m_name : "";
	Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, name, "SetState", "_show");
	m_shown30 = true;
	if (m_32)
		reinterpret_cast<Rva005D3A91 *>(this)->rva005D3A91();
	rva005D3B26();
}
