// cl: /O1 /arch:SSE /G7 /MD
// Native 00308A12..00308AA4 RET16. The 00308799..003089CF helper reads a
// type-2, 24-bit TGA, returns its pixel buffer, and writes width and height.
// This caller samples the first row, clamps the index, and writes BGR bytes
// as three integer channels. The owner and original method name are open.
class Rva00308A12
{
public:
 unsigned char *rva00308799(int *width, int *height);
 void rva00308A12(float position, int *red, int *green, int *blue);
};

static inline float clampPosition(float position)
{
 if (position < 0.0f)
  position = 0.0f;
 if (position > 1.0f)
  position = 1.0f;
 return position;
}

void Rva00308A12::rva00308A12(float position, int *red, int *green, int *blue)
{
 int width = 0;
 int height = 0;
 unsigned char *pixels = rva00308799(&width, &height);
 if (pixels && width >= 2 && height >= 1)
 {
  int index = (int)(width * clampPosition(position));
  if (index > width - 1)
   index = width - 1;
  pixels += index * 3;
  *red = pixels[2];
  *green = pixels[1];
  *blue = pixels[0];
 }
 else
 {
  *red = 255;
  *green = 255;
  *blue = 255;
 }
}
