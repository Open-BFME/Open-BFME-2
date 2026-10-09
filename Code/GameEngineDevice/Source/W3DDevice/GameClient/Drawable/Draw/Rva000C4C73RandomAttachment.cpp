// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva000C4C73@Rva000C4C73@@QAEXVAsciiString@@_NI@Z retail 0x000C4C73..0x000C4D34 (193 bytes).
// Evidence: slot 35 of the +0x0C interface vtables 0x00BCBB78 0x00BCBEF8
// and 0x00BCC588 (W3DModelDraw family) next to slot 34 0x000C445D; WB twin
// 0x00947D70 in W3DScriptedModelDraw.cpp. Takes the AsciiString by value
// (callee-destroyed through releaseBuffer 0x00036410) plus a bool and a
// word; with a non-empty 12-byte string vector at +0x164 (this view) and a
// non-null name it builds the render object (Create_Render_Obj 0x00136175)
// picks a random entry (GetGameClientRandomValue 0x0023404A on line 10029)
// hands object and entry text to the owner's rowed attachment method
// 0x000C433A on this-0x0C erases the entry (rowed erase 0x000C4657) and
// releases its reference (RefCountClass::Release_Ref inline: Delete_This
// slot 0). The original method name is unknown.
#include "ascii_string.h"

class RenderObjClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

RenderObjClass *Create_Render_Obj(const char *name);
int GetGameClientRandomValue(int lo, int hi, char *file, int line);

class Rva000C433A
{
public:
	void rva000C433A(RenderObjClass *robj, const char *name, bool flag, unsigned word);
};

struct Rva000C4657Elem
{
	const char *c_str() const { return text; }
	const char *text;
	char m_pad[8];
};

class Rva000C4657
{
public:
	Rva000C4657Elem *erase(Rva000C4657Elem *position);
	bool empty() const { return m_start == m_finish; }
	unsigned size() const { return m_finish - m_start; }
	Rva000C4657Elem *begin() { return m_start; }
	Rva000C4657Elem &operator[](unsigned i) { return *(begin() + i); }
	Rva000C4657Elem *m_start;
	Rva000C4657Elem *m_finish;
	Rva000C4657Elem *m_endOfStorage;
};

class Rva000C4C73
{
public:
	void rva000C4C73(AsciiString name, bool flag, unsigned word);

private:
	char m_pad00[0x164];
	Rva000C4657 m_names;
};

void Rva000C4C73::rva000C4C73(AsciiString name, bool flag, unsigned word)
{
	if (m_names.empty())
		return;
	const char *text = name.str();
	if (text == 0)
		return;
	RenderObjClass *robj = Create_Render_Obj(text);
	if (robj)
	{
		int index = GetGameClientRandomValue(0, m_names.size() - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp", 10029);
		Rva000C4657Elem *entry = &m_names[index];
		reinterpret_cast<Rva000C433A *>(reinterpret_cast<char *>(this) - 0xC)->rva000C433A(robj, entry->c_str(), flag, word);
		m_names.erase(entry);
		robj->Release_Ref();
	}
}
