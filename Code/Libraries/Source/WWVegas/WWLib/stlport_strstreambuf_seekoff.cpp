// cl: /GR- /GX- /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// ?seekoff@strstreambuf@_STL@@MAE?AV?$fpos@H@2@JHH@Z, retail 0x00602C30 (440 B).
// strstreambuf virtual slot 2 (offset 0x8) of vtable 0x0087A878 (class of
// ??0strstreambuf@_STL@@QAE@PADH0@Z). Donor STLport src/strstream.cpp
// strstreambuf::seekoff (same body as libstdc++ strstream.cc and ReactOS
// STLport strstream.cpp: do_get/do_put from mode+dir, seeklow=eback,
// seekhigh=epptr?epptr:egptr, beg/cur/end at 1/2/4, put/get adjust, return
// pos_type(newoff)). Prev 0x00602B50 dtor and next 0x00602DF0 istrstream dtor
// share the class and vtable.

#include <strstream>

_STLP_BEGIN_NAMESPACE

strstreambuf::pos_type
strstreambuf::seekoff(off_type off,
                      ios_base::seekdir dir, ios_base::openmode mode) {
  bool do_get = false;
  bool do_put = false;

  if ((mode & (ios_base::in | ios_base::out)) ==
          (ios_base::in | ios_base::out) &&
      (dir == ios_base::beg || dir == ios_base::end))
    do_get = do_put = true;
  else if (mode & ios_base::in)
    do_get = true;
  else if (mode & ios_base::out)
    do_put = true;

  // !gptr() is here because, according to D.7.1 paragraph 4, the seekable
  // area is undefined if there is no get area.
  if ((!do_get && !do_put) || (do_put && !pptr()) || !gptr())
    return pos_type(off_type(-1));

  char* seeklow  = eback();
  char* seekhigh = epptr() ? epptr() : egptr();

  off_type newoff;
  switch(dir) {
  case ios_base::beg:
    newoff = 0;
    break;
  case ios_base::end:
    newoff = seekhigh - seeklow;
    break;
  case ios_base::cur:
    newoff = do_put ? pptr() - seeklow : gptr() - seeklow;
    break;
  default:
    return pos_type(off_type(-1));
  }

  off += newoff;
  if (off < 0 || off > seekhigh - seeklow)
    return pos_type(off_type(-1));

  if (do_put) {
    if (seeklow + __STATIC_CAST(ptrdiff_t, off) < pbase()) {
      setp(seeklow, epptr());
      pbump((int)off);
    }
    else {
      setp(pbase(), epptr());
      pbump((int)(off - (pbase() - seeklow)));
    }
  }
  if (do_get) {
    if (off <= egptr() - seeklow)
      setg(seeklow, seeklow + __STATIC_CAST(ptrdiff_t, off), egptr());
    else if (off <= pptr() - seeklow)
      setg(seeklow, seeklow + __STATIC_CAST(ptrdiff_t, off), pptr());
    else
      setg(seeklow, seeklow + __STATIC_CAST(ptrdiff_t, off), epptr());
  }

  return pos_type(newoff);
}

_STLP_END_NAMESPACE
