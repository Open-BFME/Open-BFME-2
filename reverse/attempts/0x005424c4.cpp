// ?rva005424C4@XmlNameSlotList@@QAEHXZ
// partial score=0.12 date=2026-10-10
// cl: /O1 /MD /Oi-
// ?Rva00542425Skip@@YAPADPAD@Z @0x00542425 36B
// Identifier-char skip: advances past [A-Za-z0-9_] via isalnum IAT and '_' check
// returning first non-ident pointer. Evidence: retail bytes unlock lane plus two
// callers in 0x005424C4 and isalnum import and underscore literal.
// Static with internal caller in same TU restores compiler-private EAX-to-ESI
// handoff (mov esi eax). Precedent static intToHexDigit rowed in
// quoted_printable.cpp and shape-lever EAX-to-ESI handoff. Caller stub keeps the
// static emitted with EAX ABI until real 0x005424C4 lands here.
extern "C" __declspec(dllimport) int __cdecl isalnum(int c);

static char *Rva00542425Skip(char *p)
{
	char *s = p;
	for (;;) {
		char c = *s;
		if (c == 0)
			break;
		if (isalnum(c)) {
			s++;
			continue;
		}
		if (*s == '_') {
			s++;
			continue;
		}
		break;
	}
	return s;
}


extern "C" __declspec(dllimport) char *__cdecl strncpy(char *,const char *,unsigned int);
class BfmeLexEAN {public:int bfmeFailEAN(int);int bfmeScanEAN();};
class Rva005423F0 {public:char *rva005423F0(char *);};
class Rva005427F1 {public:void rva005427F1();};
class Rva0054273B {public:bool rva0054273B();};
struct Rva005424C4Attribute {char name[33];char value[64];};
class XmlNameSlotList {
public:
 int rva005424C4();
 int finish();
private:
 char *m_pos;
 int m_counter04;
 char *m_source08;
 int m_line0C;
 bool m_inTag;
 unsigned char m_pad11[3];
 char *m_buffer14;
 int m_limit18;
 char *m_tail;
 char *m_savedDelimiter;
 char m_savedByte;
 char m_pad25[3];
 int m_mark;
 Rva005424C4Attribute m_attributes[4];
};
int XmlNameSlotList::rva005424C4()
{
 int kind=1;
 m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos)+1;
 m_inTag=false;
 if(*m_pos==0)goto failed;
 if(*m_pos=='/') {
  ++m_pos;
  kind=2;
  if(*m_pos==0)goto failed;
 }
 m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
 if(*m_pos==0)goto failed;
 m_tail=m_pos;
 char *tagEnd=Rva00542425Skip(m_pos);
 m_pos=tagEnd;
 if(*m_pos==0)goto failed;
 m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
 if(*m_pos==0)goto failed;
 m_mark=0;
 if(kind==1) {
  while(isalnum(*m_pos)) {
   char *name=m_pos;
   char *nameEnd=Rva00542425Skip(m_pos);
   m_pos=nameEnd;
   if(*m_pos==0)goto failed;
   m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
   if(*m_pos==0 || *m_pos!='=')goto failed;
   ++m_pos;
   if(*m_pos==0)goto failed;
   m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
   if(*m_pos==0)goto failed;
   char quote=*m_pos;
   if(quote!='"' && quote!='\'')goto failed;
   ++m_pos;
   if(*m_pos==0)goto failed;
   char *value=m_pos;
   char *valueEnd=value;
   while(*valueEnd && *valueEnd!=quote)++valueEnd;
   m_pos=valueEnd;
   if(*m_pos==0)goto failed;
   ++m_pos;
   if(*m_pos==0)goto failed;
   m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
   if(*m_pos==0)goto failed;
   if(m_mark<4) {
    char saved=*nameEnd;
    *nameEnd=0;
    strncpy(m_attributes[m_mark].name,name,32);
    m_attributes[m_mark].name[32]=0;
    *nameEnd=saved;
    saved=*valueEnd;
    *valueEnd=0;
    strncpy(m_attributes[m_mark].value,value,63);
    m_attributes[m_mark].value[63]=0;
    *valueEnd=saved;
    ++m_mark;
   }
  }
 }
 if(*m_pos=='/')m_inTag=true;
 else if(*m_pos=='>')++m_pos;
 else goto failed;
 m_savedDelimiter=tagEnd;
 m_savedByte=*tagEnd;
 *tagEnd=0;
 if(kind==1)++m_counter04;
 else --m_counter04;
 return kind;
failed:
 return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
}
int XmlNameSlotList::finish()
{
 if(m_inTag && *m_pos=='/') {
  ++m_pos;
  if(*m_pos!='>')return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
  ++m_pos;
  return 2;
 }
 ((Rva005427F1 *)this)->rva005427F1();
 if(m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 for(m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);*m_pos!=0;
     m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos)) {
  if(*m_pos!='<')return ((BfmeLexEAN *)this)->bfmeScanEAN();
  if(m_pos[1]!='!')return rva005424C4();
  if(!((Rva0054273B *)this)->rva0054273B())return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 }
 m_tail=0;m_mark=0;return 0;
}
