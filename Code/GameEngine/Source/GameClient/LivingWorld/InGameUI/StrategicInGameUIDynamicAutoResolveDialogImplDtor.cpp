// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// StrategicInGameUI::DynamicAutoResolveDialog::Impl::~Impl, retail
// 0x005EB2E7..0x005EB35D (118 bytes, EH). The destructor of the dialog
// implementation whose constructor is 0x005EB481 (vtable 0x00C78210): it
// detaches itself from the living-world logic's auto-resolve observers
// (+0x2C list, rowed 0x002B7250), unloads its movie through the +0x08 owner
// (rowed 0x0057C2CC), then destroys the +0x34 and +0x14 owned holders (rowed
// clear 0x000AD6F4) around the two player-data vectors at +0x1C, and finally
// restores the observer base vtable 0x00C62A14.
#include <vector>

class CreateAHeroData;

// The observer list's rowed remover (its spelling carries an unrelated
// parameter type; the receiver is TheLivingWorldLogic + 0x2C).
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *observer);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct LivingWorldLogicObserverView
{
	unsigned char m_pad00[0x2C];
	Rva002B7250 m_autoResolveObservers;	// +0x2C
};

class Rva0057C2CC
{
public:
	void rva0057C2CC();
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4() { clear(); }
	void clear();

	void *m_pointer;
	unsigned int m_04;
};

struct DynamicAutoResolvePlayerData
{
	~DynamicAutoResolvePlayerData();

	unsigned char m_pad00[0x24];
};

class LivingWorldAutoResolveEventObserver
{
public:
	virtual ~LivingWorldAutoResolveEventObserver() {}
};

namespace StrategicInGameUI
{
	class DynamicAutoResolveDialog
	{
	public:
		class Impl : public LivingWorldAutoResolveEventObserver
		{
		public:
			virtual ~Impl();

		private:
			void *m_dialog;				// +0x04
			Rva0057C2CC *m_movieOwner;		// +0x08
			void *m_battle;				// +0x0C
			void *m_battlePlayers;			// +0x10
			Rva000AD6F4 m_state;			// +0x14
			_STL::vector<DynamicAutoResolvePlayerData> m_playerData[2];	// +0x1C
			Rva000AD6F4 m_34;			// +0x34
			int m_3c;
			int m_40;
			bool m_44;
		};
	};
}

StrategicInGameUI::DynamicAutoResolveDialog::Impl::~Impl()
{
	reinterpret_cast<LivingWorldLogicObserverView *>(TheLivingWorldLogic)->m_autoResolveObservers.rva002B7250(reinterpret_cast<CreateAHeroData *>(this));
	m_movieOwner->rva0057C2CC();
}
