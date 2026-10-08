// cl: /MD
// ?rva0029A94F@Rva0029A94F@@QAEXXZ @0x0029A94F 101B. Loop over GlobalData count at +0xA94 clearing ptr slots at this+0x544 via g_00DFF080 slot 0x34 and TheGameClient slot 0x74 then tail to g_00DFF080 slot 0x38. Evidence: retail immediates 0x00DFE758 TheWritableGlobalData 0x00DFE77C TheGameClient 0x00DFF080 plus callers 0x0029BB8B 0x002A242A.
extern class GlobalData *TheWritableGlobalData;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class GlobalData
{
public:
	char m_pad[0xA94];
	int m_count;
};

class GameClientHolder
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(void *p);
};

class G00DFF080Obj
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(void *p); virtual void v14();
};

// g_00DFF080: matched references place it at VA 0xdff080 (retail .data initial value 0).
G00DFF080Obj * g_00DFF080 = 0;

struct Rva0029A94FSlot
{
	void *ptr;
	int unk;
};

class Rva0029A94F
{
public:
	void rva0029A94F();
private:
	char m_pad[0x544];
	Rva0029A94FSlot *m_slots;
};

void Rva0029A94F::rva0029A94F()
{
	for (int i = 0; i < TheWritableGlobalData->m_count; ++i)
	{
		void *p = m_slots[i].ptr;
		if (p != 0)
		{
			g_00DFF080->v13(p);
			(*(GameClientHolder **)&TheGameClient)->s29(m_slots[i].ptr);
		}
		m_slots[i].ptr = 0;
	}
	return g_00DFF080->v14();
}
