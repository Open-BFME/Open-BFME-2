// cl: /MD /O1 /Oy-
//
// ?rva00073950@Rva00073950@@QAEXEPAX@Z @0x00073950 110B via surface fill plus clear
// Byte color input: native render0x745A2 MOV AL then PUSH EAX; WB82DB90
// consumes the low byte. The typed pitch local occupies the same native slot.
// Evidence: calls rowed rva00116680 0x00116680 plus rowed clear 0x00116760; caller 0x000745AC; uses TheWritableGlobalData
// Retail checks GlobalData +0xC6A then locks via rva00116680 then fills DWORDs then clears
class GlobalData {
public:
  unsigned char _00[0xC6A];
  bool bC6A;
};
extern class GlobalData *TheWritableGlobalData;
struct Rva00116680 {
  void *rva00116680(int *pitchOut, bool discard);
};
struct Member0C00739C70 {
  void clear();
};
struct Rva00073950 {
  unsigned char _00[0x20];
  int m20;
  int m24;
  void rva00073950(unsigned char arg08, void *arg0C);
};
void Rva00073950::rva00073950(unsigned char arg08, void *arg0C) {
  if (!TheWritableGlobalData)
    return;
  if (!TheWritableGlobalData->bC6A)
    return;
  unsigned char fill = (unsigned char)arg08;
  unsigned int color = fill;
  color = (color << 8) | fill;
  color = (color << 8) | fill;
  color = (color << 8) | fill;
  int pitch;
  void *bits = ((Rva00116680 *)arg0C)->rva00116680(&pitch, false);
  for (int y = 0; y < m24; y++) {
    for (int x = 0; x < m20; x++)
      ((unsigned int *)bits)[x] = color;
    bits = (unsigned char *)bits + pitch;
  }
  ((Member0C00739C70 *)arg0C)->clear();
}
