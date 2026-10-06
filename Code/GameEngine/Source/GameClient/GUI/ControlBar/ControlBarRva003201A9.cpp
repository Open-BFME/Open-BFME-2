// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ?Rva003201A9Parse@@YAXPAVINI@@PAX@Z, retail 0x003201A9, 92 bytes. ControlBar
// factory sibling of 0x00320158 (chain: calls 0x0031F7EB now ready).
// Evidence: news 0x24 via rowed ??2@YAPAXI@Z then rowed ??0Rva0031F7EB@@QAE@XZ;
// rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x0080D788;
// rowed ?rva003200A2@Rva003200A2@@QAEXH@Z with new object then rowed
// ?rva003200BC@Rva003200BC@@QAEXH@Z with [esi+8]; prev 0x00320158 shares flags.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva0031F7EB
{
public:
	Rva0031F7EB();
	char m_pad0[8];
	int m_08; // +0x08 (pushed for second call)
	char m_pad1[0x24 - 0x0C];
};

class Rva003200A2
{
public:
	void rva003200A2(int value);
};

class Rva003200BC
{
public:
	void rva003200BC(int value);
};

extern const FieldParse g_0080D788[];

void Rva003201A9Parse(INI *ini, void *holder)
{
	Rva0031F7EB *obj = new Rva0031F7EB;
	ini->initFromINI(obj, g_0080D788);
	((Rva003200A2 *)holder)->rva003200A2((int)obj);
	((Rva003200BC *)holder)->rva003200BC(obj->m_08);
}
