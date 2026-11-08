// cl: /Ireference/shims/bfme2_ascii /Os /DNDEBUG /MD /EHsc
// ?addBuff@BuffLogic@@QAEPAXPAX0@Z retail 0x0030682A 230 bytes. Buff draw helper returning draw object via manager. Evidence: callers 0x00362561 0x00362A3B pass global 0x00DFF190 as this with two pointer args ret 8, callee reuses arg slot for AsciiString, virtual 0x44 on ModuleData then manager virtual 0x60, debug via theDebug SkipNext CrashBegin operator<< CrashDone like Rva0033BA46.
#include "ascii_string.h"

#include "../../../Include/Common/ModuleData.h"

#include "../../../Include/Common/ModuleInfoClass.h"

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

extern class G00DFF080Obj *TheTerrainVisual;
// Retail's own 32-byte literal at RVA 0x00807D80 (file offset 0x008079D0),
// ending exactly where retail's next literal "Buff " begins at 0x00807DA0. The
// rowed body streams it straight after the buff's name, so the missing piece was
// the literal itself rather than a view of it.
// Symbol ?g_00C07D80@@3QBDB, transcribed below.
extern const char g_00C07D80[] = " requires a W3DBuffDrawModule.\n";

#include "../../Common/debug.h"

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
	BuffArg *buffArg = (BuffArg *)a;
	ModuleInfo &mi = buffArg->m_moduleInfo;
	const ModuleData *data = mi.getNthData(0);
	if (data == 0)
	{
		AsciiString msg;
		BuffInner *inner = buffArg->m_inner;
		const char *name = inner != 0 ? inner->m_name : "";
		msg.format("No draw module specified for Buff! In Buff (%s)", name);
		return 0;
	}
	const void *v = data->slot17();
	if (v == 0)
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
		Debug &dbg = theDebug->CrashBegin(0, 0, 0);
		Debug &debug = dbg << "Buff ";
		(debug << (buffArg->m_inner != 0 ? buffArg->m_inner->m_name : "") << g_00C07D80).CrashDone(2);
		}
		return 0;
	}
	return ((G00DFF080Obj *)TheTerrainVisual)->v24(b, (void *)v);
}
