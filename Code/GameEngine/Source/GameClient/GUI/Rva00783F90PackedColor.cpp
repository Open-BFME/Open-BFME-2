// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// Store the three low color channels as normalized floating-point values.
// The address-derived name retains the unproven calling owner.
extern float Rva00783F90Red;
extern float Rva00783F90Green;
extern float Rva00783F90Blue;

void Rva00783F90StorePackedColor(unsigned int color)
{
    unsigned int red = (color >> 16) & 255;
    Rva00783F90Red = (float)red * 0.003921569f;
    unsigned int green = (color >> 8) & 255;
    Rva00783F90Green = (float)green * 0.003921569f;
    unsigned int blue = color & 255;
    Rva00783F90Blue = (float)blue * 0.003921569f;
}
