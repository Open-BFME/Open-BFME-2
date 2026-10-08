// Pre-analysis setup for worldbuilder.exe (driven by tools/wb_decompile.py).
//
// Usage (as -preScript on -import): wb_prepare.java <seeds.txt>
//   seeds.txt  one function start VA per line (hex), from build/wb/wb_functions.jsonl
//
// 1. Turns off analyzers that cost time on a 33 MB debug build and add nothing
//    to decompilation (Function ID, PE resources, embedded media, scalar
//    operand references, decompiler parameter ID, ...).
// 2. Disassembles and creates a function at every seed, so analysis starts
//    from tools/pe_features.py's proven boundaries instead of rediscovering
//    them (it misses functions only reachable through vtables or the ILT).
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class wb_prepare extends GhidraScript {
    private static final String[] DISABLED = {
        "Function ID", "Library Identification", "WindowsResourceReference",
        "Embedded Media", "Scalar Operand References", "Decompiler Parameter ID",
        "Aggressive Instruction Finder", "PDB Universal", "PDB MSDIA",
        "Create Address Tables", "Condense Filler Bytes",
    };

    public void run() throws Exception {
        disableAnalyzers();
        if (getScriptArgs().length == 1) {
            seedFunctions(readSeeds(getScriptArgs()[0]));
        }
    }

    private void disableAnalyzers() {
        Map<String, String> options = getCurrentAnalysisOptionsAndValues(currentProgram);
        for (String name : DISABLED) {
            if (options.containsKey(name)) {
                setAnalysisOption(currentProgram, name, "false");
                println("wb_prepare: disabled analyzer " + name);
            }
        }
    }

    private List<Address> readSeeds(String path) throws Exception {
        List<Address> seeds = new ArrayList<>();
        for (String line : Files.readAllLines(Paths.get(path))) {
            line = line.trim();
            if (!line.isEmpty()) {
                seeds.add(toAddr(Long.decode(line)));
            }
        }
        return seeds;
    }

    private void seedFunctions(List<Address> seeds) {
        AddressSet starts = new AddressSet();
        for (Address address : seeds) {
            starts.add(address);
        }
        new DisassembleCommand(starts, null, true).applyTo(currentProgram, monitor);
        int created = 0;
        for (Address address : seeds) {
            if (getFunctionAt(address) == null
                    && new CreateFunctionCmd(address).applyTo(currentProgram, monitor)) {
                created++;
            }
        }
        println("wb_prepare: seeded " + seeds.size() + " starts, created " + created + " functions");
    }
}
