// cl: /O1 /MD /DNDEBUG /EHsc
#include <new>
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


void Rva000B3FD0AptAssertFail(const char *, const char *, int)
{
}

void Rva000B3FD0AptDebugPrint(const char *, const char *)
{
}

void Rva000B3FD0AptDebugAddSavedInput()
{
}

void Rva000B3FD0AptDebugSetScreenGrabPending()
{
}

void Rva000B3FD0AptFreeSound()
{
}

void Rva000B3FD0AptStartSound(void *, int)
{
}

void Rva000B3FD0AptStartSoundStream()
{
}

void Rva000B3FD0AptFreeTexture()
{
}

void Rva000B3FD0AptFreeRenderingUnit()
{
}

void Rva000A91D8AptFreeConstantTable(void *table)
{
	operator delete[](table);
}

int Rva000910FBAptPointHitTest()
{
	return 1;
}

int Rva000D43D0AptLoadSound()
{
	return 0;
}
