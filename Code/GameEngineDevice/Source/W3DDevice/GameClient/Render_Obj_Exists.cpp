// ?Render_Obj_Exists@@YA_NPBD@Z, retail 0x0061F0D0 (28B). Ported from
// Open-BFME-1 Code/GameEngineDevice/Source/W3DDevice/GameClient/Render_Obj_Exists.cpp
// (BFME1 0x009E9C40). Trimmed to the placed registry-guard wrapper; the
// hash-map implementation is declared-only here. Callee
// Render_Obj_Exists_Impl resolves via the new ledger pin at 0x00621170
// (sweep's chosen BFME1 name; the global is a DIR32 slot).

class AssetRegistry
{
public:
	bool Render_Obj_Exists_Impl(const char *name);
};

extern class Q1Receiver0134FAAC *TheQ1Receiver;

// ?Render_Obj_Exists@@YA_NPBD@Z
bool Render_Obj_Exists(const char *name)
{
	if (name)
	{
		AssetRegistry *registry = (*(AssetRegistry **)&TheQ1Receiver);
		if (registry)
			return registry->Render_Obj_Exists_Impl(name);
	}
	return false;
}
