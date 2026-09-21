// Open-BFME recovery lane: Lua GC sweep (phase 1: mark bodies)
// cl: /MD /Ireference/open-bfme-1/Code/Libraries/Source/Lua
/* Lua 4.0.1 (TeCGraf, PUC-Rio), lua.org lua-4.0.1.tar.gz, flattened from
   src/, src/lib/, src/luac/ and include/.  Statically linked into
   lotrbfme.exe behind GameLogic/ScriptEngine/LuaScriptEngine.cpp.
   ALTERED SOURCE VERSION: upstream plus a reconstruction of EA's own changes
   to the language (a boolean type tag, OP_PUSHBOOL, an extra luaH_new
   argument).  PROVENANCE.txt lists every file that differs from upstream and
   how; a file absent from that list is upstream byte-for-byte apart from this
   header.  Saying so is a condition of the licence at lua.h:215, not a
   courtesy.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect calls --
   /MD is what makes those call sites byte-exact. */
/*
** $Id: lgc.c,v 1.72+ 2000/10/26 12:47:05 roberto Exp $
** Garbage Collector
** See Copyright Notice in lua.h
*/

#include "lua.h"

#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "lmem.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"


typedef struct GCState {
  Hash *tmark;  /* list of marked tables to be visited */
  Closure *cmark;  /* list of marked closures to be visited */
} GCState;



static void markobject (GCState *st, TObject *o);


/* mark a string; marks larger than 1 cannot be changed */
#define strmark(s)    {if ((s)->marked == 0) (s)->marked = 1;}



static void protomark (Proto *f) {
  if (!f->marked) {
    int i;
    f->marked = 1;
    strmark(f->source);
    for (i=0; i<f->nkstr; i++)
      strmark(f->kstr[i]);
    for (i=0; i<f->nkproto; i++)
      protomark(f->kproto[i]);
    for (i=0; i<f->nlocvars; i++)  /* mark local-variable names */
      strmark(f->locvars[i].varname);
  }
}


static void markstack (lua_State *L, GCState *st) {  StkId o;
  for (o=L->stack; o<L->top; o++)
    markobject(st, o);
}


static void marklock (lua_State *L, GCState *st) {
  int i;
  for (i=0; i<L->refSize; i++) {
    if (L->refArray[i].st == LOCK)
      markobject(st, &L->refArray[i].o);
  }
}


static void markclosure (GCState *st, Closure *cl) {
  if (!ismarked(cl)) {
    if (!cl->isC)
      protomark(cl->f.l);
    cl->mark = st->cmark;  /* chain it for later traversal */
    st->cmark = cl;
  }
}


static void marktagmethods (lua_State *L, GCState *st) {
  int e;
  for (e=0; e<TM_N; e++) {
    int t;
    for (t=0; t<=L->last_tag; t++) {
      Closure *cl = luaT_gettm(L, t, e);
      if (cl) markclosure(st, cl);
    }
  }
}


static void markobject (GCState *st, TObject *o) {
  switch (ttype(o)) {
    case LUA_TUSERDATA:  case LUA_TSTRING:
      strmark(tsvalue(o));
      break;
    case LUA_TMARK:
      markclosure(st, infovalue(o)->func);
      break;
    case LUA_TFUNCTION:
      markclosure(st, clvalue(o));
      break;
    case LUA_TTABLE: {
      if (!ismarked(hvalue(o))) {
        hvalue(o)->mark = st->tmark;  /* chain it in list of marked */
        st->tmark = hvalue(o);
      }
      break;
    }
    default: break;  /* numbers, etc */
  }
}


static void markall (lua_State *L) {
  GCState st;
  st.cmark = NULL;
  st.tmark = L->gt;  /* put table of globals in mark list */
  L->gt->mark = NULL;
  marktagmethods(L, &st);  /* mark tag methods */
  markstack(L, &st); /* mark stack objects */
  marklock(L, &st); /* mark locked objects */
  for (;;) {  /* mark tables and closures */
    if (st.cmark) {
      int i;
      Closure *f = st.cmark;  /* get first closure from list */
      st.cmark = f->mark;  /* remove it from list */
      for (i=0; i<f->nupvalues; i++)  /* mark its upvalues */
        markobject(&st, &f->upvalue[i]);
    }
    else if (st.tmark) {
      int i;
      Hash *h = st.tmark;  /* get first table from list */
      st.tmark = h->mark;  /* remove it from list */
      for (i=0; i<h->size; i++) {
        Node *n = node(h, i);
        if (ttype(key(n)) != LUA_TNIL) {
          if (ttype(val(n)) == LUA_TNIL)
            luaH_remove(h, key(n));  /* dead element; try to remove it */
          markobject(&st, &n->key);
          markobject(&st, &n->val);
        }
      }
    }
    else break;  /* nothing else to mark */
  }
}

/* Anchor, absent from retail: keeps the static workers out-of-line so the
   verifier can see them. Only the rowed bodies are claimed. */
void LuaGcAnchor (lua_State *L) {
  GCState st;
  TObject o;
  markall(L);
  markobject(&st, &o);
  marklock(L, &st);
  marktagmethods(L, &st);
  protomark((void *)0);
  markstack(L, &st);
  markclosure(&st, (void *)0);
}
