// cl: /Ireference/shims/bfme2_ascii
// ?rva001DBD24@Rva00489360@@QAE_NXZ @0x001DBD24 57B: Rva00489360 element init via NameKeyGenerator and WindowManager then inner v04; evidence caller 0x001DC164 passes Rva00489360 values and NameKeyGenerator row 0x0009FA65
#include "ascii_string.h"

enum NameKeyType
{
  NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
  NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
  virtual void v00();
  virtual void v01();
  virtual void v02();
  virtual void v03();
  virtual void v04();
  virtual void v05();
  virtual void v06();
  virtual void v07();
  virtual void v08();
  virtual void v09();
  virtual void v0a();
  virtual void v0b();
  virtual void v0c();
  virtual void v0d();
  virtual void v0e();
  virtual void v0f();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v1a();
  virtual void v1b();
  virtual void v1c();
  virtual void v1d();
  virtual void v1e();
  virtual void v1f();
  virtual void v20();
  virtual void v21();
  virtual void v22();
  virtual void v23();
  virtual void v24();
  virtual void v25();
  virtual void v26();
  virtual void v27();
  virtual void v28();
  virtual void v29();
  virtual void v2a();
  virtual void v2b();
  virtual void v2c();
  virtual void v2d();
  virtual void v2e();
  virtual void v2f();
  virtual void v30();
  virtual void v31();
  virtual void v32();
  virtual void v33();
  virtual void v34();
  virtual void v35();
  virtual void v36();
  virtual void v37();
  virtual void v38();
  virtual void v39();
  virtual void v3a();
  virtual void v3b();
  virtual void *vF0(int a, int b);
};

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
  void *win = TheWindowManager->vF0(0, key);
  m_14 = m_base;
  m_window = win;
  m_inner->v04(win);
  return true;
}
