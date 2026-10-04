// cl: /O1 /MD /GX-
// ??1BfmeNodeZ@@QAE@XZ @0x003B3F5E (8B): add ecx,4 then tail-jmp the pinned
// ??1Script@@MAE@XZ at 0x003B35B1. Non-virtual public dtor over a Script
// member at +0x04 with the list link at +0x00. Evidence: callers drain node
// chains (clearRva00359330Nodes, ScriptListSubrecordRemove rva003B71B4) and
// delete through ??_GBfmeNodeZ at 0x003B4470 which calls this body.

class Script
{
	friend class BfmeNodeZ;
protected:
	virtual ~Script();
};

class BfmeNodeZ
{
public:
	~BfmeNodeZ();
private:
	BfmeNodeZ *m_next; // +0x00
	Script m_script; // +0x04
};

BfmeNodeZ::~BfmeNodeZ()
{
}
