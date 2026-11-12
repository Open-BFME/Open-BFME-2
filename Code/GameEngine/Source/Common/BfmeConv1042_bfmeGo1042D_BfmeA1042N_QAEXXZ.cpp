// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
//
// ?bfmeGo1042D@BfmeA1042N@@QAEXXZ, retail 0x0044BD79, 41 bytes. With no
// target it throws FunctorNotSet: the rowed ctor ??0FunctorNotSet@@QAE@XZ at
// 0x002035E2, then _CxxThrowException with the shared 0x00D0B644 throw info.

#include "../../Include/Common/FunctorNotSet.h"

class BfmeB1042N
{
public:
	virtual void bfmeV01042N();
	virtual void bfmeDoN1042();
};

class BfmeA1042N
{
public:
	void bfmeGo1042D(void);

	BfmeB1042N *m_bfmeP;
};

void BfmeA1042N::bfmeGo1042D(void)
{
	BfmeB1042N *p = m_bfmeP;

	if (p == 0)
		throw FunctorNotSet();

	p->bfmeDoN1042();
}

