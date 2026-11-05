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

#include "../../../Include/GameLogic/ScriptAction.h"
#include "../../../Include/GameLogic/ScriptParameter.h"

// The canonical in-class accessor is implicitly inline (select-any like
// every other TU's copy); taking its address keeps the body emitted here.
// ?bfmeAnchorScriptActionGetParameter absent-from-retail
Parameter *(ScriptAction::*bfmeAnchorScriptActionGetParameter)(int) = &ScriptAction::getParameter;

