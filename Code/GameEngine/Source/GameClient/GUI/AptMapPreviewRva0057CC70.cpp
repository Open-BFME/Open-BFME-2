// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
// ?v04@Rva0057C50C@@UAEPAXPAX0@Z @0x0057CC70 246B: slot 1 of the map preview's
// colour callback (vtable 0x0086F31C, ctor 0x0057C50C, deleting dtor 0x0057C66C);
// +0x04 is its owning AptMapPreview.
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
	int GetNextSelectablePlayer(int v);
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
	// 0x0057C525 is the rowed AptMapPreview::AllowsStartInRegion(int) (AptMapPreview.cpp).
	bool AllowsStartInRegion(int region);
};

class Rva0057C50C
{
public:
	virtual void v0();
	virtual void *v04(void *color, void *arg);
private:
	CC70Outer *m_outer;	// +0x04 the owning AptMapPreview
};

void *Rva0057C50C::v04(void *color, void *arg)
{
	Rva0057CC70Color *destination = (Rva0057CC70Color *)color;
	CC70Arg *cC70Arg = (CC70Arg *)arg;
	Rva0057CC70Color def;
	def.r = 0.5f;
	def.g = 0.5f;
	def.b = 0.5f;
	GameInfo *info = (GameInfo *)m_outer->m_ptr18->rva0043DA65();
	if (!info)
	{
		*destination = def;
		return destination;
	}
	Rva0057CC70Color tmp;
	Rva0057CC70Color *src;
	int slot = cC70Arg->m_field140;
	if (slot == -1)
		slot = ((Rva0057CA78 *)m_outer)->GetNextSelectablePlayer(0);
	GameSlot *gs = 0;
	CC70Mid1 *cC70Mid1 = 0;
	CC70Mid2 *cC70Mid2 = 0;
	Sub0052BAC1 *t = 0;
	if ((unsigned int)slot < 8
		&& (gs = info->getSlot(slot)) != 0
		&& (cC70Mid1 = m_outer->m_ptr68) != 0
		&& (cC70Mid2 = cC70Mid1->m_ptr29c) != 0
		&& (t = cC70Mid2->m_ptr1c) != 0)
	{
		Res004FCA0C *r = t->Rva004FCA0C((Rva0020E89C *)cC70Arg);
		if (r != (Res004FCA0C *)cC70Arg)
		{
			v04(destination, r);
			return destination;
		}
		if (!((AptMapPreview *)m_outer)->AllowsStartInRegion((int)cC70Arg))
		{
			CC70LWMInner *cC70LWMInner = ((CC70LWMView *)TheLivingWorldManager)->m_ptr268;
			src = &cC70LWMInner->m_color;
			if (!cC70LWMInner)
				src = &def;
		}
		else
		{
			int color = ((CC70SlotView *)gs)->m_color;
			MultiplayerColorDefinition *multiplayerColorDefinition = TheMultiplayerSettings->getColor(color);
			if (multiplayerColorDefinition)
			{
				tmp = ((CC70ColorDefView *)multiplayerColorDefinition)->m_color;
				src = &tmp;
			}
			else
				src = &def;
		}
	}
	else
		src = &def;
	*destination = *src;
	return destination;
}
