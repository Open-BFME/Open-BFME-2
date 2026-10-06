// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00202058, 492 bytes.
// Rva00202058::rva00202058: reads OptionPreferences enum forwarders
// (0x002E42EE..0x002E432E rowed in OptionPreferences_enumDispatch.cpp)
// into GameLOD-style defs array (5x0x4C at +0) and option fields
// +0x17C..+0x1C4. Imul 0x4C needs /G7; push 2/pop ebp and xor/inc ebx
// are /O1 small-constant idioms.

class OptionPreferences
{
public:
	int Rva002E42EEForward();
	int Rva002E42F6Forward();
	int Rva002E42FEForward();
	int Rva002E4306Forward();
	int Rva002E430EForward();
	int Rva002E4316Forward();
	int Rva002E431EForward();
	int Rva002E4326Forward();
	int Rva002E432EForward();
};

struct LODDef
{
	char _0[8];
	int f8;
	char _c[0x14];
	int f20;
	int f24;
	int f28;
	char _2c[0x18];
	int f44;
	int f48;
};

class Rva00202058
{
public:
	void rva00202058(OptionPreferences *prefs);

private:
	LODDef m_defs[5];
	int m_17c;
	int m_180;
	int m_184;
	bool m_188;
	unsigned char m_189;
	bool m_18a;
	int m_18c;
	bool m_190;
	bool m_191;
	int m_194;
	bool m_198;
	int m_19c;
	int m_1a0;
	int m_1a4;
	int m_1a8;
	bool m_1ac;
	int m_1b0;
	int m_1b4;
	bool m_1b8;
	bool m_1b9;
	int m_1bc;
	int m_1c0;
	int m_1c4;
};

void Rva00202058::rva00202058(OptionPreferences *prefs)
{
	m_17c = prefs->Rva002E42EEForward();
	m_1b0 = prefs->Rva002E42F6Forward();
	m_180 = prefs->Rva002E42FEForward();
	m_1b9 = (prefs->Rva002E42FEForward() >= 2);
	int idx1;
	int v = prefs->Rva002E42FEForward();
	if (v <= 0)
		idx1 = 0;
	else
	{
		int v2 = prefs->Rva002E42FEForward();
		if (v2 == 1)
			idx1 = 1;
		else
		{
			int v3 = prefs->Rva002E42FEForward();
			if (v3 == 2)
				idx1 = 2;
			else
			{
				int v4 = prefs->Rva002E42FEForward();
				idx1 = 3 + (v4 != 3);
			}
		}
	}
	LODDef *d1 = &m_defs[idx1];
	m_184 = d1->f8;
	m_1c0 = d1->f44;
	m_1c4 = d1->f48;
	int widx;
	if (prefs->Rva002E4306Forward() < 1 || prefs->Rva002E4306Forward() > 2)
		widx = 0;
	else
		widx = 1;
	m_189 = (unsigned char)widx;
	m_188 = (prefs->Rva002E4306Forward() == 2);
	m_18a = (prefs->Rva002E4306Forward() >= 3);
	m_18c = prefs->Rva002E4306Forward();
	m_190 = (prefs->Rva002E430EForward() >= 2);
	m_191 = (prefs->Rva002E430EForward() >= 1);
	m_194 = prefs->Rva002E4316Forward();
	m_198 = (prefs->Rva002E4316Forward() >= 1);
	int u = prefs->Rva002E430EForward();
	int idx2;
	if (u <= 0)
		idx2 = 1;
	else
	{
		int u2 = prefs->Rva002E430EForward();
		idx2 = 2 + (u2 > 1);
	}
	LODDef *d2 = &m_defs[idx2];
	m_19c = d2->f20;
	m_1a0 = d2->f24;
	m_1a4 = d2->f28;
	int t = prefs->Rva002E431EForward();
	int idx3;
	if (t <= 0)
		idx3 = 2;
	else
	{
		int t2 = prefs->Rva002E431EForward();
		idx3 = (t2 <= 1);
	}
	m_1a8 = idx3;
	m_1ac = (prefs->Rva002E430EForward() >= 1);
	m_1b4 = prefs->Rva002E4326Forward();
	m_1b8 = (prefs->Rva002E4326Forward() >= 2);
	m_1bc = prefs->Rva002E432EForward();
}
