#ifndef BFME2_MODERN_APT_LAYOUT_H
#define BFME2_MODERN_APT_LAYOUT_H

#if !defined(BFME2_MODERN)
#error ModernAptLayout belongs only to the explicit modern variant
#endif

// The reference build scales the Apt stage (HUD, menus) to the device with
// independent X and Y factors, which stretches it on wide screens. The modern
// variant keeps the stage's aspect ratio: one uniform scale and a centring
// offset in device pixels. BFME2_MODERN_HUD=stretch restores the reference
// behaviour. The offset is zero whenever the stage is stretched.
extern float g_modernAptOffsetX;
extern float g_modernAptOffsetY;
bool modernAptKeepAspect();

#endif
