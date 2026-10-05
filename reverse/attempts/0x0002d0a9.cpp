// ?preprocessMacro@INI@@SAPBDPBD@Z
// partial score=0.9 date=2026-10-05
// ?preprocessMacro@INI@@SAPBDPBD@Z
// partial score=0.9 date=2026-10-05
// ?preprocessMacro@INI@@SAPBDPBD@Z
// partial score=0.9 date=2026-10-05 r10
// STASH for ?preprocessMacro@INI@@SAPBDPBD@Z @0x002D0A9 (156B).
// r10: scope FIXED (mov esi,0xDDF5B4 exact via shared extern, no add-peephole).
// Tail STILL OPEN: retail mov edi,[edi+8]/test edi/lea eax,[edi+8]-hoist/jne
// vs ours mov eax,[edi+8]/test eax/je/add. Two r10 spellings both FAIL with
// identical tail (add_match diffs in seat-4-r10.json): (1) node=node->m_text
// same-var reuse (MacroNode*); (2) separate char *text=node->m_text.
// Shared providers (no duplicate pin, no Root/custom-Anim strings):
// - scope DDF5B4 reuses extern AsciiString g_00DDF5B4 from
//   Code/GameEngine/Source/Common/System/Rva0002BF4AClear.cpp (matched
//   0x0002BF4A clear sets it from TheEmptyString; dtor thunk 0x007B6A5A).
//   Link-time extern kills the add-esi-28 peephole; mov esi,OFFSET masked.
//   r9 g_iniMacroScopeName duplicate pin REMOVED; r8 0x2CBCC pin preserved.
// - other DE0878 reuses AsciiString::TheEmptyString (real definition in
//   Code/GameEngine/Source/Common/Rva00380200Getter.cpp at 0x00DE0878).
// - table DDF58C absolute (exact); map DDF5A0 absolute (sole xref, exact).
// Next: try double member access (return node->m_text ? node->m_text+8 : "")
// or re-derive from r10 compiled hex (exact through map call, tail-only diff).

// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc

#include "ascii_string.h"

struct MacroNode
{
	char m_pad[8];
	char *m_text;
};

class Rva002C9E7Table;

struct MacroScopeSlot
{
	int m_out;
	Rva002C9E7Table *m_table;
};

class Rva002C9E7Table
{
public:
	MacroNode *find(const AsciiString &key);
};

class Rva002CA26Map
{
public:
	void opaqueCall(MacroScopeSlot *slot, const StringBase<char> &key);
};

class INI
{
public:
	static const char *preprocessMacro(const char *token);
};

// Shared real scope provider (see header note). No new pin.
extern AsciiString g_00DDF5B4;

// ?preprocessMacro@INI@@SAPBDPBD@Z
const char *INI::preprocessMacro(const char *token)
{
	const char *tok = token;
	char c = tok[0];
	if (c > '9' || c < '0' || c == '-')
	{
		MacroNode *node;
		MacroScopeSlot slot;
		{
			AsciiString tmp(tok);
			Rva002C9E7Table *table = (Rva002C9E7Table *)0xDDF58C;
			node = table->find(tmp);
			slot.m_table = table;
		}
		if (node != 0)
		{
			AsciiString *scope = &g_00DDF5B4;
			const AsciiString *other = &AsciiString::TheEmptyString;
			if (scope->compare(*other) != 0)
			{
				((Rva002CA26Map *)0xDDF5A0)->opaqueCall(&slot, (const StringBase<char> &)*scope);
			}
			char *text = node->m_text;
			return text != 0 ? text + 8 : "";
		}
		return tok;
	}
	return tok;
}
