// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A7974@NAT@@QAEXGPAX@Z @0x005A7974 290B: NAT PORT request builder.
// Target evidence: byte gates m_24=1 plus m_04/m_25 plus Transport setter 0x004D51ED,
// format "PORT%d %d %08X %X" 0x00871C50 plus "NAT/" plus translate 0x00038220,
// empty fallback g_Rva0107301CEmptyString, OwnedRecord ctor 0x001EF661/dtor
// 0x001EF723, queue global g_00A02340 slot 6; layout from Rva005A8666Box.cpp.
#include "ascii_string.h"
#include "unicode_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <string>
#include <vector>
#include "../../Include/GameNetwork/Transport.h"
#include "../GameNetwork/NATView.h"
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}


__forceinline const char *GetStr005A7974(const AsciiString &asciiString)
{
	char *t = *(char * *)(const void *)&asciiString;
	return t ? t + 8 : "";
}

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union
	{
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
	};
};

struct Global003EF728V6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6(PeerRequest *rec);
};

// g_00A02340 is only an alias of the owned global TheGameSpyPeerMessageQueue (ledger names column); this unit reads the owner through its own view type.
extern class GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
#define g_00A02340 (*(Global003EF728V6 * *)&TheGameSpyPeerMessageQueue)

void NAT::rva005A7974(unsigned short port, void *info)
{
	m_24 = 1;
	if (m_04 != 0 && m_25 != 0)
		m_04->setDestAddrToSocket(m_targetSlot, m_addresses[m_targetSlot]);
	PeerRequest req;
	AsciiString portStr;
	portStr.format("PORT%d %d %08X %X", m_localSlot, port, m_localIP, m_cookie);
	req.unknown_00 = 0xd;
	req.payload_flag0.value = true;
	req.unknown_34 = "NAT/";
	AsciiString uniStr;
	uniStr.translate(*(const UnicodeString *)((const char *)info + 0x30));
	req.unknown_04 = GetStr005A7974(uniStr);
	req.unknown_40 = GetStr005A7974(portStr);
	g_00A02340->f6(&req);
}
