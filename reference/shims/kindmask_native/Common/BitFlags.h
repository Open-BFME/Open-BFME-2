#pragma once
// TU-scoped binding for Player.cpp and ScoreKeeper.cpp. Their reference
// header's BitFlags<116> test emits a four-word body. Retail's independently
// rowed 0x0030A146 provider walks seven words; retain that out-of-line body.
// Declare the specialization before PreRTS includes Thing's inline queries.
#include "../../../open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h"

template <> Bool BitFlags<116>::testSetAndClear(
 const BitFlags<116> &, const BitFlags<116> &) const;
