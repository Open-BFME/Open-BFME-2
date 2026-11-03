exec(open('build/wwmath-profile-20261103/probe.py').read().split('variants={')[0])
for tag,flags in [
 ('Oy','-O1 -G7 -arch:SSE -MD -Oy'),
 ('Og','-O1 -G7 -arch:SSE -MD -Og'),
 ('G6','-O1 -G6 -arch:SSE -MD'),
 ('Op','-O1 -G7 -arch:SSE -MD -Op'),
 ('O2-Og-off','-O2 -G7 -arch:SSE -MD -Og-'),
 ('O2-Op','-O2 -G7 -arch:SSE -MD -Op'),
 ('O2-Oa','-O2 -G7 -arch:SSE -MD -Oa'),
]:
 w=T.Verifier(names[0],flags=flags)
 got=w.matched(source,rows)
 print(tag,flags,sorted(got or []),flush=True)
 if len(got or [])==len(rows):Path('build/wwmath-profile-20261103/winner.cpp').write_text(w.effective(source,rows))
 if tag=='O2-Op':
  r=next(r for r in rows if 'areApprox' in r['name'])
  p=w.B.compile_function(r,w.sm,w.obj)
  for title,data in [('retail-equal',p['target']),('O2-equal',p['bytes'])]:
   print(title,flush=True)
   for i in md.disasm(data,0):print(i.mnemonic,i.op_str)
