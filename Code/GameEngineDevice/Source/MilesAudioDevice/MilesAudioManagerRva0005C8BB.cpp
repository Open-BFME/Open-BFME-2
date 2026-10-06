// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE2
// Frameless (/Oy via /O1) EH cluster sharing the 0xB5D851 __EH_prolog head:
//  ?rva0005C8BB@Rva0005C8BB@@QAEXMH@Z @0x0005C8BB 118B,
//  ?rva0005CAE2@Rva0005C8BB@@QAEXXZ @0x0005CAE2 87B,
//  ?rva0005CB39@Rva0005C8BB@@QAEXXZ @0x0005CB39 87B,
//  ?rva0005CB90@Rva0005C8BB@@QAEXHM@Z @0x0005CB90 87B.
// Each locks MilesMutexGuard over +0x9D4, then: 5C8BB fans a float out to the
// three 0x1C4-stride owners at +0x12C selected by flag bits before the rowed
// 0x5C892 zero-notify; the 87B members call it after a TheGlobalData +0x9C5
// guard plus a pinned no-arg (0x524D6/0x524E2) or cdecl (int,float) 0x524EE
// global. Layout mirrors MilesAudioManagerRva00053CE1 (+0x12C/0x1C4/0x9D4).
// All names are address-derived; identities unproven.
class Rva00699180Owner
{
public:
	void rva000522DF(float volume);
};

class Rva0005C892
{
public:
	void rva0005C892();
};

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *obj, int flags);
	~MilesMutexGuard();
private:
	void *m_obj;
	int m_flags;
};

struct Rva0005C8BBElem
{
	char m_data[0x1C4];
};

class GlobalData
{
public:
	char m_pad00[0x9C5];
	bool m_flag9C5;
};

extern GlobalData *TheGlobalData;

void rva000524D6();
void rva000524E2();
void rva000524EE(int a, float b);

class Rva0005C8BB
{
public:
	void rva0005C8BB(float volume, int flags);
	void rva0005CAE2();
	void rva0005CB39();
	void rva0005CB90(int a, float b);
private:
	char m_pad00[0x12C];
	Rva0005C8BBElem m_arr[3];
	char m_pad678[0x9D4 - 0x12C - 3 * 0x1C4];
	int m_mutex9D4;
};

void Rva0005C8BB::rva0005C8BB(float volume, int flags)
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	Rva0005C8BBElem *elem = m_arr;
	for (int i = 0; i < 3; i++, elem++)
	{
		if (flags & (1 << i))
			((Rva00699180Owner *)elem)->rva000522DF(volume);
	}
	((Rva0005C892 *)this)->rva0005C892();
}

void Rva0005C8BB::rva0005CAE2()
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	if (TheGlobalData->m_flag9C5)
	{
		rva000524D6();
		((Rva0005C892 *)this)->rva0005C892();
	}
}

void Rva0005C8BB::rva0005CB39()
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	if (TheGlobalData->m_flag9C5)
	{
		rva000524E2();
		((Rva0005C892 *)this)->rva0005C892();
	}
}

void Rva0005C8BB::rva0005CB90(int a, float b)
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	rva000524EE(a, b);
	((Rva0005C892 *)this)->rva0005C892();
}
