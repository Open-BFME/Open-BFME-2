// Ghidra headless pre-script: create a function for every row of a seed list
// (`rva<TAB>size<TAB>name`, from tools/ghidra_seed.py) before auto-analysis.
// A row with a size gets exactly that body. See README: the output is a
// candidate list, not a replacement inventory.
//
// Usage: analyzeHeadless <proj> bfme2 -import game.dat -overwrite \
//          -scriptPath tools/ghidra -preScript seed_ledger.java <seeds.tsv> \
//          -postScript list_functions.java <out.csv>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.io.BufferedReader;
import java.io.FileReader;

public class seed_ledger extends GhidraScript {
    public void run() throws Exception {
        long base = currentProgram.getImageBase().getOffset();
        int made = 0, bodies = 0, failed = 0;
        BufferedReader r = new BufferedReader(new FileReader(getScriptArgs()[0]));
        String line;
        while ((line = r.readLine()) != null) {
            String[] f = line.split("\t");
            if (f.length < 3 || f[0].startsWith("#")) continue;
            long size = Long.parseLong(f[1]);
            Address a = toAddr(base + Long.decode(f[0]));
            try {
                disassemble(a);
                Function fn = getFunctionAt(a);
                if (fn == null) {
                    fn = createFunction(a, null);
                    if (fn != null) made++;
                }
                if (fn == null) { failed++; continue; }
                if (size > 0) {
                    try { fn.setBody(new AddressSet(a, a.add(size - 1))); bodies++; } catch (Exception e) { }
                }
                try { fn.setName(f[2], SourceType.IMPORTED); } catch (Exception e) { }
            } catch (Exception e) {
                failed++;
            }
        }
        r.close();
        println("seeded " + made + " functions, " + bodies + " exact bodies, " + failed + " failed");
    }
}
