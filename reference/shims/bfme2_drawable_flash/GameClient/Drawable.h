#pragma once
// GameClient/Drawable.h for units still built on Zero Hour's headers (PreRTS.h, Zero Hour's
// Thing): Zero Hour's Drawable.h with BFME 2's DRAWABLE_FRAMES_PER_FLASH.
//
// Zero Hour defines `const Int DRAWABLE_FRAMES_PER_FLASH = LOGICFRAMES_PER_SECOND / 2;`, a
// compile-time constant, so an includer builds no initializer. BFME 2 divides the frame-rate
// variable instead (GameClient/DrawableFramesPerFlash.h), and every unit that includes
// Drawable.h registers one 16-byte .CRT$XCU copy of it (LINK-236). The canonical Drawable.h
// cannot join these units (a second Thing), so a unit whose retail run proves its copy puts
// this directory first on its include path: Zero Hour's constant is read under another name,
// and the unit takes the BFME 2 definition at the point retail's unit included Drawable.h.
#ifndef BFME2_ZH_DRAWABLE_FLASH_SHIM_H
#define BFME2_ZH_DRAWABLE_FLASH_SHIM_H

#define DRAWABLE_FRAMES_PER_FLASH ZH_DRAWABLE_FRAMES_PER_FLASH_CONSTANT
#include "../../../open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h"
#undef DRAWABLE_FRAMES_PER_FLASH

#include "../../../../Code/GameEngine/Include/GameClient/DrawableFramesPerFlash.h"

#endif // BFME2_ZH_DRAWABLE_FLASH_SHIM_H
