// ?rva00511ADF@Rva00511ADF@@QAEXHPAD_N@Z
// partial score=0.99 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva00511ADF@Rva00511ADF@@QAEXHPAD_N@Z, retail 0x00511ad4, 11 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// handler switch on code 0..5 with bool flag getter/setter: 0 E046C0, 1 E047C0,
// 2 active-tab index via Rva005118F3Show/snprintf, 3 g_00DD13D8 with 't'/atoi,
// 4 virtual +0x3C bool, 5 m_29d bool. Getters share "1"/"0" tail.
// Evidence: callees Rva005118F3Show 0x005118F3 isInMultiplayerGame 0x00042235
// _mbscpy pin 0x00629176 atoi/_snprintf IAT, globals TheGameLogic g_Va009FE958
// g_Va00E046BC g_00DD13D8 g_00BBFDE0/g_00BBFDDC "%d", members +0x29c/+0x29d.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buf, unsigned int n, const char *fmt, ...);
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);

class GameLogic
{
public:
	bool isInMultiplayerGame();
};
extern GameLogic *TheGameLogic;

struct Global009FE958;
extern Global009FE958 *g_Va009FE958;
extern int g_Va00E046BC;
extern unsigned char g_00DD13D8;
extern char g_00E046C0[];
extern char g_00E047C0[];
extern const char g_00BBFDDC[];
extern const char g_00BBFDE0[];

void __cdecl Rva005118F3Show(int index, bool clear);

class Rva00511ADF
{
public:
	virtual void _v0();
	virtual void _v1();
	virtual void _v2();
	virtual void _v3();
	virtual void _v4();
	virtual void _v5();
	virtual void _v6();
	virtual void _v7();
	virtual void _v8();
	virtual void _v9();
	virtual void _v10();
	virtual void _v11();
	virtual void _v12();
	virtual void _v13();
	virtual void _v14();
	virtual bool _v15();
	void rva00511ADF(int code, char *buf, bool flag);
private:
	char m_pad04[0x29C - 0x04];
	unsigned char m_29c;
	unsigned char m_29d;
};

void Rva00511ADF::rva00511ADF(int code, char *buf, bool flag)
{
	switch (code) {
	case 0:
		if (flag)
			_mbscpy(g_00E046C0, buf);
		else
			_mbscpy(buf, g_00E046C0);
		break;
	case 1:
		if (flag)
			_mbscpy(g_00E047C0, buf);
		else
			_mbscpy(buf, g_00E047C0);
		break;
	case 2:
		if (flag) {
			Rva005118F3Show(atoi(buf), false);
		} else {
			if (TheGameLogic != 0 && TheGameLogic->isInMultiplayerGame() && g_Va009FE958 != 0) {
				buf[0] = 0;
			} else {
				_snprintf(buf, 0xff, "%d", g_Va00E046BC);
			}
		}
		break;
	case 3:
		if (flag) {
			if (buf[0] == 't')
				g_00DD13D8 = 1;
			else {
				int t = atoi(buf);
				g_00DD13D8 = 0;
				if (t == 0) {
				} else {
					g_00DD13D8 = 1;
				}
			}
			m_29c = 1;
		} else {
			const char *v = (g_00DD13D8 != 0) ? g_00BBFDE0 : g_00BBFDDC;
			_mbscpy(buf, v);
		}
		break;
	case 4:
		if (flag)
			break;
		{
			bool b = _v15();
			const char *v = b ? g_00BBFDE0 : g_00BBFDDC;
			_mbscpy(buf, v);
		}
		break;
	case 5:
		if (flag) {
			m_29d = (atoi(buf) != 0);
		} else {
			const char *v = (m_29d != 0) ? g_00BBFDE0 : g_00BBFDDC;
			_mbscpy(buf, v);
		}
		break;
	default:
		break;
	}
}
