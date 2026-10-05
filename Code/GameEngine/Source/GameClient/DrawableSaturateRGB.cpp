// cl: /G7 /arch:SSE /DNDEBUG /MD
//
// ?saturateRGB@Drawable@@QAEXAAURGBColor@@M@Z retail 0x002701A8, 76 bytes: the
// Zero Hour Drawable.cpp body, which a /G7 /arch:SSE build places uniquely.
// Its caller at 0x0044FDE9 loads the drawable into ecx, so it is the member
// function rather than a static scaler.

typedef float Real;

struct RGBColor
{
	Real red, green, blue;
};

class Drawable
{
public:
	void saturateRGB(RGBColor& color, Real factor);
};

void Drawable::saturateRGB(RGBColor& color, Real factor)
{
	color.red *= factor;
	color.green *= factor;
	color.blue *= factor;

	Real halfFactor = factor * 0.5f;

	color.red -= halfFactor;
	color.green -= halfFactor;
	color.blue -= halfFactor;

}
