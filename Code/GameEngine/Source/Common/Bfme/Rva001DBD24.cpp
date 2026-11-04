// cl: /Ireference/shims/bfme2_ascii
// ?rva001DBD24@Rva00489360@@QAE_NXZ @0x001DBD24 57B: Rva00489360 element init via NameKeyGenerator and WindowManager then inner v04; evidence caller 0x001DC164 passes Rva00489360 values and NameKeyGenerator row 0x0009FA65
#include "ascii_string.h"

enum NameKeyType
{
  NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

class Inner00489360
{
public:
  virtual void v00();
  virtual void v04(void *win);
  int m_val;
  int m_flag;
};

class Rva00489360
{
public:
  bool rva001DBD24();
  AsciiString m_name;
  int m_base;
  int m_key;
  void *m_window;
  Inner00489360 *m_inner;
  int m_14;
};

bool Rva00489360::rva001DBD24()
{
  int key = TheNameKeyGenerator->nameToKey(m_name);
  m_key = key;
  void *win = TheWindowManager->winGetWindowFromId(0, key);
  m_14 = m_base;
  m_window = win;
  m_inner->v04(win);
  return true;
}
