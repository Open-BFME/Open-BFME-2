// ?updateFloatingText@InGameUI@@IAEXXZ
// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?updateFloatingText@InGameUI@@IAEXXZ, retail 0x0029D0E5, 283 bytes.
// Direct port of BFME1 donor
// (reference/open-bfme-1/game/GameEngine/Source/GameClient/InGameUI_updateFloatingText.cpp):
// same static last-frame guard, same TheGameClient->getFrame at slot 0x7c,
// same vanish/rate/divide then diff multiply, same GameGetColorComponents +
// GameMakeColor alpha fade, same list<int>::erase + delete when alpha hits 0.
// BFME2 deltas proven by retail body: list at +0x8A0 (m_node ptr), timeout
// +0x8A4, moveUp +0x8A8, vanish +0x8AC; GameEngine rate at +0x38.
#include <list>

namespace _STL {
// Retail calls the verified list<int> eraser at 0x00438539.
template <> list<int>::iterator list<int>::erase(list<int>::iterator);

template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef int Color;

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

extern void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha);

class ClientFrameSubsystem
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual UnsignedInt getFrame();
};

class GameClient;
extern GameClient *TheGameClient;

class GameEngine
{
public:
	unsigned char m_pad[0x38];
	Int m_frame;
};

extern GameEngine *TheGameEngine;

class FloatingTextData
{
public:
	// Local ABI view of retail vtable slot 0: the target passes delete flags
	// and then sends its returned block pointer to operator delete.
	virtual void *retailDeletingDtorSlot0(Int flags);
	Color m_color;
	unsigned char m_pad2[0x14];
	Int m_frameTimeOut;
	Int m_frameCount;
};

class InGameUI
{
protected:
	void updateFloatingText();

private:
	unsigned char m_pad[0x8A0];
	_STL::list<int> m_floatingTextList;
	UnsignedInt m_floatingTextTimeOut;
	Real m_floatingTextMoveUpSpeed;
	Real m_floatingTextMoveVanishRate;
};

void InGameUI::updateFloatingText()
{
	register InGameUI *self = this;
	FloatingTextData *ftd;
	UnsignedInt currLogicFrame = reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->getFrame();
	UnsignedByte r, g, b, a;
	Int amount;
	static UnsignedInt lastLogicFrameUpdate = currLogicFrame;

	if (lastLogicFrameUpdate == currLogicFrame)
		return;
	lastLogicFrameUpdate = currLogicFrame;

	_STL::list<int> &floatingTextList = self->m_floatingTextList;
	for (_STL::list<int>::iterator it = floatingTextList.begin(); it != floatingTextList.end();)
	{
		ftd = (FloatingTextData *)(*it);
		++ftd->m_frameCount;
		if (currLogicFrame > (UnsignedInt)ftd->m_frameTimeOut)
		{
			GameGetColorComponents(ftd->m_color, &r, &g, &b, &a);
			amount = (Int)((self->m_floatingTextMoveVanishRate / (Real)TheGameEngine->m_frame) * (currLogicFrame - (UnsignedInt)ftd->m_frameTimeOut));
			if ((Int)a - amount < 0)
				a = 0;
			else
				a -= (UnsignedByte)amount;
			ftd->m_color = GameMakeColor(r, g, b, a);
			if (a <= 0)
			{
				it = floatingTextList.erase(it);
				::operator delete(ftd->retailDeletingDtorSlot0(0));
				continue;
			}
		}
		++it;
	}
}
