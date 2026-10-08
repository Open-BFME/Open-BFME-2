// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?LocationFromString@BuddyInviteGameInfo@@QAEXABVAsciiString@@@Z, retail 0x00416143, 174 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// sscanf "%d %d %d" into +4/+8/+0x14 then split " PW:"/" #HOST:" substrings into +0x10/+0x0C.
// Evidence: sscanf IAT strstr IAT x2 strlen thunk x3 via 0x00629170 StringBase set 0x00036780/0x000055F5
// releaseBuffer 0x00036410 empty string 0x00BBAC1C via g_Rva0107301CEmptyString caller 0x0041775D
// neighbours 0x00416088/0x004161F1. Best probe V6 two ternaries gives 172B vs 174B 69 vs 70 insns.
#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *s, const char *sub);
extern "C" unsigned int __cdecl strlen(const char *s);


struct BuddyInviteGameInfo
{
	int m_00;
	int m_04;
	int m_08;
	AsciiString m_0C;
	AsciiString m_10;
	int m_14;
	void LocationFromString(const AsciiString &a);
};

void BuddyInviteGameInfo::LocationFromString(const AsciiString &a)
{
	void *h = *(void *const *)&a;
	const char *t = h != 0 ? (const char *)h + 8 : "";
	const char *s = h != 0 ? (const char *)h + 8 : "";
	sscanf(s, "%d %d %d", &m_04, &m_08, &m_14);
	const char *pw = strstr(t, " PW:");
	const char *host = strstr(pw, " #HOST:");
	if (pw == 0 || host == 0) {
		m_10.clear();
		m_0C.clear();
	} else {
		((StringBase<char> *)&m_10)->set(pw + strlen(" PW:"), (int)(host - pw) - (int)strlen(" PW:"));
		m_0C.set(host + strlen(" #HOST:"));
	}
}
