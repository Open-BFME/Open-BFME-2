// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
// ?rva0057CC70@AptMapPreview@@QAEPAURva0057CC70Color@@PAU2@PAUCC70Arg@@@Z @0x0057CC70 246B
// Evidence: chain from 0x0057C525 landing; neighbours AptMapPreviewSetMapDescription
// (prev 0x0057CC43) and RvaTreeEraseClearFamily (next 0x0057CD78); callees rowed
// 0x0043DA65 0x0057CA78 0x003FF29F 0x004FCA0C 0x0057C525 0x00381373.

class Rva0043DA65
{
public:
	int rva0043DA65();
};

class Rva0057CA78
{
public:
	int rva0057CA78(int v);
};

class GameSlot
{
public:
	virtual void reset();
};

class GameInfo
{
public:
	GameSlot *getSlot(int v);
};

struct Res004FCA0C;
class Rva0020E89C;
class Sub0052BAC1
{
public:
	Res004FCA0C *Rva004FCA0C(Rva0020E89C *v);
};

class Rva004FD6F9;
class Rva0057C525
{
public:
	bool rva0057C525(const Rva004FD6F9 &o);
};

class MultiplayerColorDefinition;
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int v);
};

class LivingWorldManager;

extern LivingWorldManager *TheLivingWorldManager;
extern MultiplayerSettings *TheMultiplayerSettings;

struct Rva0057CC70Color
{
	float r;
	float g;
	float b;
};

struct CC70Arg
{
	char m_pad[0x140];
	int m_field140;
};

struct CC70SlotView
{
	char m_pad[0x0c];
	int m_color;
};

struct CC70Mid2
{
	char m_pad[0x1c];
	Sub0052BAC1 *m_ptr1c;
};

struct CC70Mid1
{
	char m_pad[0x29c];
	CC70Mid2 *m_ptr29c;
};

struct CC70Outer
{
	char m_pad00[0x18];
	Rva0043DA65 *m_ptr18;
	char m_pad1c[0x4c];
	CC70Mid1 *m_ptr68;
};

struct CC70ColorDefView
{
	char m_pad[0x24];
	Rva0057CC70Color m_color;
};

struct CC70LWMInner
{
	char m_pad[0x20];
	Rva0057CC70Color m_color;
};

struct CC70LWMView
{
	char m_pad[0x268];
	CC70LWMInner *m_ptr268;
};

class AptMapPreview
{
public:
	virtual void v0();
	virtual void virt04(Rva0057CC70Color *o, Res004FCA0C *r);
	Rva0057CC70Color *rva0057CC70(Rva0057CC70Color *o, CC70Arg *a);
private:
	CC70Outer *m_outer;
};

Rva0057CC70Color *AptMapPreview::rva0057CC70(Rva0057CC70Color *o, CC70Arg *a)
{
	Rva0057CC70Color def;
	def.r = 0.5f;
	def.g = 0.5f;
	def.b = 0.5f;
	GameInfo *info = (GameInfo *)m_outer->m_ptr18->rva0043DA65();
	if (!info)
	{
		*o = def;
		return o;
	}
	Rva0057CC70Color tmp;
	Rva0057CC70Color *src;
	int slot = a->m_field140;
	if (slot == -1)
		slot = ((Rva0057CA78 *)m_outer)->rva0057CA78(0);
	GameSlot *gs = 0;
	CC70Mid1 *m1 = 0;
	CC70Mid2 *m2 = 0;
	Sub0052BAC1 *t = 0;
	if ((unsigned int)slot < 8
		&& (gs = info->getSlot(slot)) != 0
		&& (m1 = m_outer->m_ptr68) != 0
		&& (m2 = m1->m_ptr29c) != 0
		&& (t = m2->m_ptr1c) != 0)
	{
		Res004FCA0C *r = t->Rva004FCA0C((Rva0020E89C *)a);
		if (r != (Res004FCA0C *)a)
		{
			virt04(o, r);
			return o;
		}
		if (!((Rva0057C525 *)m_outer)->rva0057C525(*(const Rva004FD6F9 *)(const void *)a))
		{
			CC70LWMInner *q = ((CC70LWMView *)TheLivingWorldManager)->m_ptr268;
			src = &q->m_color;
			if (!q)
				src = &def;
		}
		else
		{
			int color = ((CC70SlotView *)gs)->m_color;
			MultiplayerColorDefinition *c = TheMultiplayerSettings->getColor(color);
			if (c)
			{
				tmp = ((CC70ColorDefView *)c)->m_color;
				src = &tmp;
			}
			else
				src = &def;
		}
	}
	else
		src = &def;
	*o = *src;
	return o;
}
