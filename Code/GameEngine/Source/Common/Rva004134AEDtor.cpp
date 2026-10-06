// cl: /MD /EHs
//
// ??1Rva004134AE@@QAE@XZ, retail 0x004134AE, 53 bytes.
// Non-virtual dtor over GameEngineDeletingBase with tree member at +0xC.
// Evidence: retail calls rowed ??1Rva0041331E at 0x00413396 via lea [esi+0xC]
// then rowed ??1GameEngineDeletingBase at 0x001B4E74 with ecx=esi (base at +0);
// EH prolog with and [ebp-4],0 / or [ebp-4],-1 needs /EHs; caller at 0x00413495
// in 28B body 0x00413492 (likely ??_G) becomes ready; neighbour 0x004134E3 is
// a method of a class with a map at +0xC in the same directory.

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva0041331E
{
public:
	~Rva0041331E();
};

class Rva004134AE
{
public:
	~Rva004134AE();
private:
	GameEngineDeletingBase m_base00;
	Rva0041331E m_tree0C;
};

Rva004134AE::~Rva004134AE()
{
}
