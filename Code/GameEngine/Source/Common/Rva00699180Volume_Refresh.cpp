// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Oi
// Combined TU: thiscall refreshPair (0x00699180) + setVolumes (0x006999C0).
// Helper body is the real member; no stand-in.
//
// Retail bodies: refreshPair 296B @0x00051ED6, refreshAll 28B @0x0005202C.
// Transferred from the BFME1 reconstruction (same Rva00699180Volume.cpp TU
// family). Retail adaptations, all measured from the target bytes:
// float-heavy refreshPair needs /arch:SSE2 with intrinsics (/Oi) so the
// slot copy folds to four movsd and the zero-fill to stosd;
// #pragma optimize("y", off) keeps its ebp frame while frameless
// refreshAll keeps the sibling-loop shape (no this reload); the clamp
// section is a rolled 0..3 loop here, and setVolumes is not claimed.
// Both bodies rowed: the m_scale reference local (float &scale) forces the
// scale-first mulss operand order retail shows (plain member reorder is
// commutative-inert); the pointer homes to eax via lea like retail.

class MilesAudioManager
{
public:
	class GlobalVolumeData;
};

class MilesAudioManager::GlobalVolumeData
{
public:
	void refreshPair(int a, int b);
	void refreshAll();
	void rva00051FFE(int b);
	void rva00052015(int b);
	void rva00052048(int idx);
	void rva00052098(int b);
	void rva000520C6();
	void rva000522DF(float volume);
	void setVolumes(float volume, unsigned char flags);

	char m_pad0[4];
	float m_base[12];
	float m_product[6];
	char m_pad4c[0x94 - 0x4c];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_padA0[0xC8 - 0xA0];
	float m_slot[12][4];
	char m_dirty[6][2][4];
	char m_pad1B8[0x1C4 - 0x1B8];
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);
extern "C" void *memset(void *dst, int v, unsigned int n);

// g_00DB3F64: VA 0x00DB3F64 (.data); retail bytes are six float 1.0 values.
float g_00DB3F64[6] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
// g_00DB3F7C: VA 0x00DB3F7C (.data); retail initial byte is 0x01.
unsigned char g_00DB3F7C = 1;

#pragma optimize("y", off)
// ?refreshPair@GlobalVolumeData@MilesAudioManager@@QAEXHH@Z
void MilesAudioManager::GlobalVolumeData::refreshPair(int a, int b)
{
	int idx = b + a * 2;
	float *slot = (float *)((char *)this + 0xC8 + (idx << 4));
	float old[4];
	memcpy(old, slot, sizeof(old));

	if (a == 5)
	{
		slot[0] = 1.0f;
		slot[1] = 1.0f;
		slot[2] = 1.0f;
		slot[3] = 1.0f;
	}
	else if (g_00DB3F7C)
	{
		slot[0] = *((float *)((char *)this + 4 + idx * 4)) * g_00DB3F64[a] * m_vol;
		if (b == 1)
			slot[0] = slot[0] * m_atten;
		float &scale = m_scale;
		slot[1] = scale * slot[0];
		slot[2] = m_product[a] * slot[0];
		slot[3] = scale * slot[2];

		for (int i = 0; i < 4; ++i)
		{
			float x = slot[i];
			if (x < 0.0f)
				x = 0.0f;
			else if (x > 1.0f)
				x = 1.0f;
			slot[i] = x;
		}
	}
	else
	{
		memset(slot, 0, sizeof(float) * 4);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (slot[i] != old[i])
			*((unsigned char *)this + 0x188 + (b + a * 2) * 4 + i) = 2;
	}
}
#pragma optimize("", on)

// ?refreshAll@GlobalVolumeData@MilesAudioManager@@QAEXXZ
void MilesAudioManager::GlobalVolumeData::refreshAll()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}

void MilesAudioManager::GlobalVolumeData::rva00051FFE(int b)
{
	for (int i = 0; i < 2; ++i)
		refreshPair(b, i);
}

void MilesAudioManager::GlobalVolumeData::rva00052015(int b)
{
	for (int i = 0; i < 6; ++i)
		refreshPair(i, b);
}

void MilesAudioManager::GlobalVolumeData::rva00052048(int idx)
{
	struct Factor
	{
		float v;
		float w;
	};
	float *slot = (float *)((char *)this + 0x34 + idx * 4);
	char *base = (char *)this + idx * 12;
	Factor *begin = *(Factor **)(base + 0x4c);
	Factor *end = *(Factor **)(base + 0x50);
	*slot = 1.0f;
	float &r = *slot;
	for (Factor *p = begin; p != end; ++p)
		r = r * p->v;
	float v = r;
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
	r = v;
}

void MilesAudioManager::GlobalVolumeData::rva00052098(int b)
{
	rva00052048(b);
	rva00051FFE(b);
}

// ?rva000520C6@GlobalVolumeData@MilesAudioManager@@QAEXXZ retail 0x000520C6 46B
// Unlock: triple-nested 6x2x4 decrement of positive dirty bytes at this+0x188.
// Evidence: prev 0x00052098 next 0x000523A0 same TU same class; dirty store in refreshPair at +0x188+(b+a*2)*4+i; caller 0x00062881.
void MilesAudioManager::GlobalVolumeData::rva000520C6()
{
	for (int a = 0; a < 6; ++a) {
		for (int b = 0; b < 2; ++b) {
			for (int i = 0; i < 4; ++i) {
				if (m_dirty[a][b][i] > 0)
					--m_dirty[a][b][i];
			}
		}
	}
}


// ?rva000522DF@GlobalVolumeData@MilesAudioManager@@QAEXM@Z retail 0x000522DF 46B
// Unlock: clamp volume 0..1 into m_vol at +0x98 then refreshAll.
// Evidence: prev 0x000520C6 next 0x000523A0 same TU same class; m_vol store +0x98; float 1.0 via g_Va00BBB8D8; caller 0x0005C8FC.
void MilesAudioManager::GlobalVolumeData::rva000522DF(float volume)
{
	float v;
	if (0.0f > volume)
		v = 0.0f;
	else if (volume > 1.0f)
		v = 1.0f;
	else
		v = volume;
	m_vol = v;
	refreshAll();
}

void MilesAudioManager::GlobalVolumeData::setVolumes(float volume, unsigned char flags)
{
	if (flags & 1)
	{
		for (int i = 4; i < 6; ++i)
			m_base[i] = volume;
		rva00051FFE(2);
	}
	if (flags & 2)
	{
		m_base[0] = volume;
		refreshPair(0, 0);
	}
	if (flags & 4)
	{
		m_base[1] = volume;
		refreshPair(0, 1);
	}
	if (flags & 8)
	{
		for (int i = 0; i < 2; ++i)
		{
			m_base[2 + i] = volume;
			m_base[8 + i] = volume;
		}
		rva00051FFE(1);
		rva00051FFE(4);
	}
	if (flags & 16)
	{
		for (int i = 6; i < 8; ++i)
			m_base[i] = volume;
		rva00051FFE(3);
	}
}

// The audio manager holds three GlobalVolumeData blocks at +0x12C, stride
// 0x1C4 (target evidence: the two loops below step 0x1C4 three times from
// TheAudio+0x12C into rowed members of this class). Only that span is
// modelled; indexing the array, not byte arithmetic, gives retail's
// [index+base] address order.
class AudioManager
{
public:
	char m_pad0[0x12C];
	MilesAudioManager::GlobalVolumeData m_volumeData[3];
};
extern AudioManager *TheAudio;

// ?Rva0005244ALoop@@YAXH@Z retail 0x0005244A 48B
// Null-guarded rva00051FFE(v) over the three volume blocks.
// Evidence: rowed callee 0x00051FFE, TheAudio 0x009FE6E8, caller site.
void Rva0005244ALoop(int v)
{
	if (TheAudio == 0)
		return;
	for (int i = 0; i < 3; ++i)
		TheAudio->m_volumeData[i].rva00051FFE(v);
}

// ?Rva000524AALoop@@YAXXZ retail 0x000524AA 44B
// Null-guarded refreshAll over the three volume blocks.
// Evidence: callers 0x000524DD 0x000524E9, rowed refreshAll 0x0005202C.
void Rva000524AALoop()
{
	if (TheAudio == 0)
		return;
	for (int i = 0; i < 3; ++i)
		TheAudio->m_volumeData[i].refreshAll();
}

// ?rva000524D6@@YAXXZ retail 0x000524D6 12B.
// Clears g_00DB3F7C then tail-jumps to Rva000524AALoop. Evidence is pin plus
// caller 0x0005CB14 plus LINK BONUS plus abut to 0x000524AA.
void rva000524D6()
{
	g_00DB3F7C = 0;
	Rva000524AALoop();
}

// ?rva000524E2@@YAXXZ retail 0x000524E2 12B.
// Sets g_00DB3F7C then tail-jumps to Rva000524AALoop. Evidence is pin plus
// caller 0x0005CB6B plus LINK BONUS plus abut to 0x000524D6/0x000524EE.
void rva000524E2()
{
	g_00DB3F7C = 1;
	Rva000524AALoop();
}

// ?rva000524EE@@YAXHM@Z retail 0x000524EE 36B (packet 122B includes next body
// at 0x00052512; landing the ret-terminated 36B per NOTE).
// Bounds-checked store to g_00DB3F64 then Rva0005244ALoop. Evidence is pin
// plus callers 0x0005CBBE plus LINK BONUS plus abut to 0x000524D6.
void rva000524EE(int idx, float value)
{
	if (idx < 0)
		return;
	if (idx >= 6)
		return;
	g_00DB3F64[idx] = value;
	Rva0005244ALoop(idx);
}
