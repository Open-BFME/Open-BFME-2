// ?clear@ScriptList@@QAEXXZ
// partial score=0.97 date=2026-09-26
// Banked near-miss for ?clear@ScriptList@@QAEXXZ at 0x003B7812 (36B):
// temp ScriptList, temp.swap(this), temp dtor. Best shape is 36/36B
// with identical frame, calls and registers; sole diff is the swap
// target: retail reuses the constructor return (push esi / mov ecx,eax)
// while every named-temp spelling recomputes lea ecx,[ebp-0x4C].
// The temporary spelling gives mov ecx,eax but drops the esi save
// (push ecx instead); retail has both. Refuted: named temp, temporary,
// (&tmp)->, qualified ScriptList::, reference alias, pointer alias,
// placement new (<new>), explicit ctor call on raw storage, /O2, /Os.
// The ctor (0x003B7720), swap (0x003B58DF) and dtor (pinned 0x003B774B)
// callees are all named. TU needs /GX- (no EH frame on the temp).
// Next ideas: a spelling that keeps this in a callee-saved reg while
// taking the swap target from eax, or the true TU flags.

// cl: /O1 /MD /GX-
class Rva003B761E
{
public:
	Rva003B761E();

private:
	char m_data[0x20];
};

class ScriptListBase
{
public:
	ScriptListBase()
	{
		m_firstGroup = 0;
		m_firstScript = 0;
		m_vtable = (void *)0x00C1FAAC;
	}

private:
	void *m_vtable;
	void *m_firstGroup;
	void *m_firstScript;
};

class ScriptList : public ScriptListBase
{
public:
	ScriptList();
	~ScriptList();
	void clear();
	void swap(ScriptList *other);

private:
	Rva003B761E m_first;
	Rva003B761E m_second;
};

void ScriptList::clear()
{
	ScriptList tmp;
	tmp.swap(this);
}
