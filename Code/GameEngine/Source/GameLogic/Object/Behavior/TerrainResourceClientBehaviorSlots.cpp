// cl: /O1 /DNDEBUG /MD
//
// TerrainResourceClientBehavior primary slots 17 and 18 (vtable 0x00BEFF20),
// a raise/lower pair around the byte at +0x0C: slot 17 (retail 0x004CC5FA,
// 32 bytes) runs 0x004E7B0C on the holder at TheInGameUI +0x58C once and sets
// the byte, slot 18 (retail 0x004CC61A, 32 bytes) runs 0x004E7D1D there and
// clears it. Both holder members forward through the pointer the holder
// keeps; they are pinned by address on these call sites. Names by address.
class Rva004E7B0CHolder
{
public:
	void rva004E7B0C();
	void rva004E7D1D();
};

// TheInGameUI's holder at +0x58C. Retail adds the offset to the global loaded
// straight into ecx (add ecx, 0x58C); cl 7.1 emits that for byte-pointer
// arithmetic written in the body.
class InGameUI;
extern InGameUI *TheInGameUI;

class ModuleData;
class Object;
class TerrainResourceClientBehavior
{
public:
	virtual ~TerrainResourceClientBehavior();
	virtual void rva004CC5FA();
	virtual void rva004CC61A();
private:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	bool m_0C;			// +0x0C
};

void TerrainResourceClientBehavior::rva004CC5FA()
{
	if (!m_0C)
	{
		Rva004E7B0CHolder *holder = (Rva004E7B0CHolder *)((char *)TheInGameUI + 0x58C);
		holder->rva004E7B0C();
		m_0C = true;
	}
}

void TerrainResourceClientBehavior::rva004CC61A()
{
	if (m_0C)
	{
		Rva004E7B0CHolder *holder = (Rva004E7B0CHolder *)((char *)TheInGameUI + 0x58C);
		holder->rva004E7D1D();
		m_0C = false;
	}
}
