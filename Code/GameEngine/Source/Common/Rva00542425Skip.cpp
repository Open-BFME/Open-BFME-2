// cl: /O1 /MD /Oi-
// ?skipIdentifier@@YAPADPAD@Z @0x00542425 36B
// Identifier-char skip: advances past [A-Za-z0-9_] via isalnum IAT and '_' check
// returning first non-ident pointer. Evidence: retail bytes unlock lane plus two
// callers in 0x005424C4 and isalnum import and underscore literal.
// Static with internal caller in same TU restores compiler-private EAX-to-ESI
// handoff (mov esi eax). Precedent static intToHexDigit rowed in
// quoted_printable.cpp and shape-lever EAX-to-ESI handoff. Caller stub keeps the
// static emitted with EAX ABI for findChar.
#include <ctype.h>
#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static char *skipIdentifier(char *text)
{
	char *cursor = text;
	for (;;) {
		char ch = *cursor;
		if (ch == 0)
			break;
		if (isalnum(ch)) {
			cursor++;
			continue;
		}
		if (*cursor == '_') {
			cursor++;
			continue;
		}
		break;
	}
	return cursor;
}

// ?findChar@@YAPADPADD@Z @0x00542449 16B
// Character find: advances until NUL or the stack-passed character, returning
// the stop pointer. Same EAX-pointer private convention as skipIdentifier
// directly before it (retail bytes: live-in eax, char at [esp+4], plain ret).
static char *findChar(char *text, char c)
{
	char *cursor = text;
	for (;;) {
		char ch = *cursor;
		if (ch == 0)
			break;
		if (ch == c)
			break;
		cursor++;
	}
	return cursor;
}

// ?Rva00542425Caller@@YAPADPAD@Z present-unmatched
char *Rva00542425Caller(char *text)
{
	char *cursor = skipIdentifier(text);
	cursor = findChar(cursor, ',');
	return skipIdentifier(cursor);
}

// ?scanElement@XmlNameSlotList@@QAEHXZ @0x005424C4 535B
// Element scanner: tail-jumped from XmlNameSlotList::finish 0x00542890 at '<'.
// Skips whitespace after '<', reads an optional '/' (closing tag, kind 2),
// the tag name (skipIdentifier), then for an opening tag up to 4
// name="value" / name='value' attributes into 33+64 byte slots at +0x2C
// (stride 0x61, retail imul 0x61). '/' leaves the element open for finish's
// "/>" arm, '>' is consumed; the tag name is NUL-terminated in place with the
// clobbered byte saved at +0x20/+0x24, and the depth at +0x04 moves by one.
// Any malformed input returns bfmeFailEAN(-1). Retail bytes and call sites.
class BfmeLexEAN {public:int bfmeFailEAN(int);int bfmeScanEAN();};
#include "../../Include/Common/Rva005423F0.h"
struct Rva005424C4Attribute {char name[33];char value[64];};
class XmlNameSlotList {
public:
 int scanElement();
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
int XmlNameSlotList::scanElement()
{
 int kind=1;
 m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos)+1;
 m_inTag=false;
 if(*m_pos==0)
  return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 if(*m_pos=='/') {
  ++m_pos;
  kind=2;
  if(*m_pos==0)
   return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 }
 m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
 if(*m_pos==0)
  return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 m_tail=m_pos;
 char *tagEnd=skipIdentifier(m_pos);
 m_pos=tagEnd;
 if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
 if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
 m_mark=0;
 if(kind==1) {
  while(isalnum(*m_pos)) {
   char *name=m_pos;
   char *nameEnd=skipIdentifier(m_pos);
   m_pos=nameEnd;
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   if(*m_pos!='=')return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   ++m_pos;
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   m_pos=((Rva005423F0 *)this)->rva005423F0(m_pos);
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   char quote=*m_pos;
   if(quote!='"' && quote!='\'')return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   ++m_pos;
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   char *value=m_pos;
   char *valueEnd=value;
   if(*valueEnd) do { if(*valueEnd==quote)break; ++valueEnd; } while(*valueEnd);
   m_pos=valueEnd;
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   ++m_pos;
   if(*m_pos==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
   char *after=((Rva005423F0 *)this)->rva005423F0(m_pos);
   m_pos=after;
   _ReadWriteBarrier();
   if(*after==0)return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
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
 else {
  if(*m_pos!='>')return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
  ++m_pos;
 }
 m_savedDelimiter=tagEnd;
 m_savedByte=*tagEnd;
 *tagEnd=0;
 if(kind==1)++m_counter04;
 else --m_counter04;
 return kind;
}
