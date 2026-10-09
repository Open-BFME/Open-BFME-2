// cl: /O2 /MD
// Native F1570..F15CF: XML-node string conversion callback passed by F1600.
// The checked cast, node+20, slot21 and returned AptString are target facts;
// WB1788240 corroborates the control flow. Original method name unknown.
class XmlNode {
public:
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void s12();
  virtual void s13();
  virtual void s14();
  virtual void s15();
  virtual void s16();
  virtual void s17();
  virtual void s18();
  virtual void s19();
  virtual void s20();
  virtual const char *stringValue();
};
class BfmeAptValue006DCD20 {
public:
  virtual void slot0();
  char pad[28];
  XmlNode *node;
  int isXmlNode() const;
  BfmeAptValue006DCD20 *rva006DD220();
};
class AptValue {
public:
  void SetString(const char *);
};
class AptString : public AptValue {
public:
  static AptString *Create();
};
class EAStringC {
public:
  const char *rva00620090() const;
};
EAStringC *Rva0070B4F0GetString(int);
extern AptValue *gpUndefinedValue;
AptValue *rva006F1570(BfmeAptValue006DCD20 *value) {
  if (!(unsigned char)value->isXmlNode())
    return gpUndefinedValue;
  BfmeAptValue006DCD20 *xml = value->rva006DD220();
  AptString *s = AptString::Create();
  s->SetString(Rva0070B4F0GetString(0x62)->rva00620090());
  if (xml->node) {
    const char *p = xml->node->stringValue();
    if (p)
      s->SetString(p);
  }
  return s;
}
