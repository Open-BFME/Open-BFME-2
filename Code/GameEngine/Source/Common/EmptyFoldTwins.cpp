// cl: /O1 /MD /DNDEBUG /EHsc
// ICF-twin home for pin-aliased empty hooks folded at 0x000B3FD0.
//
// Several small units call empty hooks that retail folds with the rowed 1B
// bodies at 0x000B3FD0 (a bare ret). Each name below is the symbols.csv pin's
// opaque alias (identity unproven; rename when a real identity resolves).
// The bodies MUST live here, not in the caller TUs: cl deletes calls to
// visible-empty bodies even under __declspec(noinline) (proven by revert on
// Rva005D1B01.cpp), which breaks the callers' rowed bodies. This TU makes
// no calls to any of them. Rows are added with add_match --icf-owner
// against the rowed 1B bodies (same sanctioned pattern as the
// StaticNameKey::key and ShellMenuSchemeManager::update twins).
class Rva000B3FD0Empty
{
public:
	void rva000B3FD0Empty();
};

void Rva000B3FD0Empty::rva000B3FD0Empty()
{
}

class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

void Rva000B3FD0::rva000B3FD0()
{
}
