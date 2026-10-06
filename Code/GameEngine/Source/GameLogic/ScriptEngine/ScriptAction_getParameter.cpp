// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?getParameter@ScriptAction@@QAEPAVParameter@@H@Z at retail 0x00203553 (24B).
// Donor: ZH Scripts.h ScriptAction::getParameter (inline bounds-checked
// indexer). Target evidence: test eax,eax; jl null; cmp eax,[ecx+8];
// jge null; mov eax,[ecx+eax*4+0xC]; xor eax,eax on OOB. Callers pass a
// ScriptAction (ctor 0x003B5413 vtable 0x81F3FC) and use the Parameter*
// result (type at +0, value at +8/+0xC). Layout matches
// ScriptActionGetUiText.cpp: vtable +0, m_actionType +4, m_numParms +8,
// m_parms +0xC. Condition::getParameter is an identical ICF twin (same
// address, ctor 0x003B5AC7 path).

enum { MAX_PARMS = 12 };

class Parameter
{
};

class ScriptAction
{
public:
	Parameter *getParameter(int ndx);

private:
	void *m_vtable; // +0x00
	int m_actionType; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
};

Parameter *ScriptAction::getParameter(int ndx)
{
	if (ndx >= 0 && ndx < m_numParms)
		return m_parms[ndx];

	return 0;
}
