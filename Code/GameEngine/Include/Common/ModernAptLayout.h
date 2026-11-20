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
// Stage units that move the HUD's edge panels (Palantir.apt's palantir and
// side command bar) from the centred box's edges to the screen's; 0 when the
// stage is stretched or BFME2_MODERN_HUD_EDGES=0.
float modernAptEdgeShift();
// Set while such a panel is drawn; the next Apt pass then is not clipped.
extern bool g_modernAptEdgesDrawn;

#endif
