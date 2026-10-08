// cl: /Ireference/shims/bfme2_ascii /Os /DNDEBUG /MD /EHsc
// ?addBuff@BuffLogic@@QAEPAXPAX0@Z retail 0x0030682A 230 bytes. Buff draw helper returning draw object via manager. Evidence: callers 0x00362561 0x00362A3B pass global 0x00DFF190 as this with two pointer args ret 8, callee reuses arg slot for AsciiString, virtual 0x44 on ModuleData then manager virtual 0x60, debug via theDebug SkipNext CrashBegin operator<< CrashDone like Rva0033BA46.
#include "ascii_string.h"

class ModuleData
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual int s17() const;
};

class ModuleInfo
{
public:
	const ModuleData *getNthData(int i) const;
};

struct BuffInner
{
	char m_pad[8];
	char m_name[1];
};

class BuffArg
{
public:
	char m_pad0[0x64];
	BuffInner *m_inner;
	char m_pad68[0x2F0 - 0x68];
	ModuleInfo m_moduleInfo;
};

class G00DFF080Obj
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void *v24(void *a, void *b);
};

extern class G00DFF080Obj *g_00DFF080;
extern const char g_00C07D80[];

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual void CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class BuffLogic
{
public:
	void *addBuff(void *a, void *b);
};

void *BuffLogic::addBuff(void *a, void *b)
{
	BuffArg *arg = (BuffArg *)a;
	ModuleInfo &mi = arg->m_moduleInfo;
	const ModuleData *data = mi.getNthData(0);
	if (data == 0)
	{
		AsciiString msg;
		BuffInner *inner = arg->m_inner;
		const char *name = inner != 0 ? inner->m_name : "";
		msg.format("No draw module specified for Buff! In Buff (%s)", name);
		return 0;
	}
	int v = data->s17();
	if (v == 0)
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
		Debug &dbg = theDebug->CrashBegin(0, 0, 0);
		Debug &tmp = dbg << "Buff ";
		(tmp << (arg->m_inner != 0 ? arg->m_inner->m_name : "") << g_00C07D80).CrashDone(2);
		}
		return 0;
	}
	return ((G00DFF080Obj *)g_00DFF080)->v24(b, (void *)v);
}
