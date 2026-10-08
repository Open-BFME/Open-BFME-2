// Name and decompile worldbuilder.exe functions (driven by tools/wb_decompile.py).
//
// Usage (as -postScript on -process worldbuilder.exe -noanalysis):
//   wb_decompile.java <names.tsv> <targets.txt> <out_dir> <timeout_s>
//
// names.tsv    kind<TAB>va<TAB>namespace<TAB>name<TAB>thiscall
//              kind F renames the function at va (created if missing) and,
//              when namespace is not empty, moves it into that class
//              namespace ("A::B" nests); thiscall 1 sets __thiscall so the
//              decompiler shows `this`; an empty name only sets the
//              convention. kind D labels a data address.
// targets.txt  one WB function VA per line (hex); each is created if missing
//              and decompiled to <out_dir>/<va>.c, or <out_dir>/<va>.err on
//              failure. A .c file starts with a comment block naming the
//              function and listing its callees (thunks resolved) as
//              `// callee 0x<va> <name>` lines, for tools/wb_draft.py.
//              Untyped callees first get parameters from their stack cleanup
//              (see inferCalleeParameters), so calls show their arguments.
//
// Renames are saved with the project, so a later run skips them cheaply.
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.decompiler.parallel.DecompilerCallback;
import ghidra.app.decompiler.parallel.ParallelDecompiler;
import ghidra.app.script.GhidraScript;
import ghidra.app.util.NamespaceUtils;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.Undefined4DataType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.ParameterImpl;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.util.task.TaskMonitor;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class wb_decompile extends GhidraScript {
    private static final int MAX_ARG_BYTES = 0x100;
    private final Map<String, Namespace> namespaces = new HashMap<>();
    private int renamed, failedRenames;

    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 4) {
            throw new IllegalArgumentException("expected <names.tsv> <targets.txt> <out_dir> <timeout_s>");
        }
        applyNames(Paths.get(args[0]));
        Path out = Paths.get(args[2]);
        Files.createDirectories(out);
        List<Function> functions = targetFunctions(Paths.get(args[1]), out);
        int typed = 0;
        for (Function function : functions) {
            typed += inferCalleeParameters(function);
        }
        println("wb_decompile: gave parameters to " + typed + " callees");
        long start = System.nanoTime();
        int[] counts = decompile(functions, out, Integer.parseInt(args[3]));
        double seconds = (System.nanoTime() - start) / 1e9;
        println(String.format("wb_decompile: renamed %d (%d failed); decompiled %d ok, %d failed in %.1fs",
            renamed, failedRenames, counts[0], counts[1], seconds));
    }

    // ------------------------------------------------------------ naming

    private void applyNames(Path path) throws Exception {
        for (String line : Files.readAllLines(path, StandardCharsets.UTF_8)) {
            String[] f = line.split("\t", -1);
            if (f.length != 5) {
                continue;
            }
            Address address = toAddr(Long.decode(f[1]));
            try {
                if (f[0].equals("D")) {
                    labelData(address, f[3]);
                }
                else {
                    nameFunction(address, f[2], f[3], f[4].equals("1"));
                }
            }
            catch (Exception e) {
                failedRenames++;
            }
        }
    }

    private void labelData(Address address, String name) throws Exception {
        Symbol primary = currentProgram.getSymbolTable().getPrimarySymbol(address);
        if (primary == null || !primary.getName().equals(name)) {
            createLabel(address, name, true, SourceType.USER_DEFINED);
            renamed++;
        }
    }

    private void nameFunction(Address address, String namespace, String name, boolean thiscall)
            throws Exception {
        Function function = functionAt(address);
        if (function == null) {
            failedRenames++;
            return;
        }
        Namespace parent = namespace.isEmpty() ? currentProgram.getGlobalNamespace() : classNamespace(namespace);
        boolean differs = !function.getName().equals(name) || !function.getParentNamespace().equals(parent);
        if (!name.isEmpty() && differs) {
            function.getSymbol().setNameAndNamespace(name, parent, SourceType.USER_DEFINED);
            renamed++;
        }
        if (thiscall && !"__thiscall".equals(function.getCallingConventionName())) {
            function.setCallingConvention("__thiscall");
        }
    }

    private Namespace classNamespace(String path) throws Exception {
        Namespace cached = namespaces.get(path);
        if (cached == null) {
            cached = NamespaceUtils.createNamespaceHierarchy(path, null, currentProgram, SourceType.USER_DEFINED);
            cached = NamespaceUtils.convertNamespaceToClass(cached);
            namespaces.put(path, cached);
        }
        return cached;
    }

    /** The function starting at address, created (with disassembly) if missing. */
    private Function functionAt(Address address) {
        Function function = getFunctionAt(address);
        if (function != null) {
            return function;
        }
        if (getInstructionAt(address) == null) {
            disassemble(address);
        }
        new CreateFunctionCmd(address).applyTo(currentProgram, monitor);
        return getFunctionAt(address);
    }

    // ------------------------------------------------- callee parameters

    /**
     * Gives each untyped callee of function as many undefined4 parameters as
     * it pops (`ret N`), or, for a caller-cleanup callee, as the largest
     * `add esp, N` after a call to it here. Without this the decompiler shows
     * no arguments at all for callees whose signature analysis never ran.
     * Returns how many callees were typed.
     */
    private int inferCalleeParameters(Function function) throws Exception {
        Map<Function, Integer> cleanup = new HashMap<>();
        InstructionIterator it = currentProgram.getListing().getInstructions(function.getBody(), true);
        while (it.hasNext()) {
            Instruction call = it.next();
            if (!call.getFlowType().isCall() || call.getFlows().length != 1) {
                continue;
            }
            Function callee = resolved(getFunctionAt(call.getFlows()[0]));
            if (callee != null && !callee.isExternal()) {
                cleanup.merge(callee, stackCleanup(call.getNext()), Math::max);
            }
        }
        int typed = 0;
        for (Map.Entry<Function, Integer> entry : cleanup.entrySet()) {
            Function callee = entry.getKey();
            if (callee.getParameterCount() > callee.getAutoParameterCount()) {
                continue;
            }
            int purge = callee.getStackPurgeSize();
            int bytes = purge > 0 && purge < MAX_ARG_BYTES ? purge : entry.getValue();
            if (bytes > 0 && bytes % 4 == 0) {
                List<ParameterImpl> params = new ArrayList<>();
                for (int i = 0; i < bytes / 4; i++) {
                    params.add(new ParameterImpl("param_" + (i + 1), Undefined4DataType.dataType, currentProgram));
                }
                callee.replaceParameters(params, Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS,
                    true, SourceType.ANALYSIS);
                typed++;
            }
        }
        return typed;
    }

    private static Function resolved(Function function) {
        return function != null && function.isThunk() ? function.getThunkedFunction(true) : function;
    }

    /** N for an `add esp, N` instruction, else 0. */
    private static int stackCleanup(Instruction next) {
        if (next == null || !next.getMnemonicString().equals("ADD")
                || !"ESP".equals(next.getDefaultOperandRepresentation(0))) {
            return 0;
        }
        Scalar scalar = next.getScalar(1);
        return scalar == null ? 0 : (int) scalar.getUnsignedValue();
    }

    // ------------------------------------------------------- decompiling

    private List<Function> targetFunctions(Path path, Path out) throws Exception {
        List<Function> functions = new ArrayList<>();
        for (String line : Files.readAllLines(path)) {
            line = line.trim();
            if (line.isEmpty()) {
                continue;
            }
            Function function = functionAt(toAddr(Long.decode(line)));
            if (function == null) {
                Files.writeString(out.resolve(line + ".err"), "no function could be created at " + line + "\n");
            }
            else {
                functions.add(function);
            }
        }
        return functions;
    }

    /** Decompiles on Ghidra's shared pool (one worker per core); {ok, failed}. */
    private int[] decompile(List<Function> functions, Path out, int timeout) throws Exception {
        int[] counts = new int[2];
        DecompilerCallback<Boolean> callback = new DecompilerCallback<Boolean>(currentProgram, decompiler -> {
            DecompileOptions options = new DecompileOptions();
            options.grabFromProgram(currentProgram);
            decompiler.setOptions(options);
            decompiler.toggleCCode(true);
            decompiler.setSimplificationStyle("decompile");
        }) {
            @Override
            public Boolean process(DecompileResults results, TaskMonitor m) throws Exception {
                return write(results, out);
            }
        };
        callback.setTimeout(timeout);
        try {
            for (Boolean ok : ParallelDecompiler.decompileFunctions(callback, functions, monitor)) {
                counts[Boolean.TRUE.equals(ok) ? 0 : 1]++;
            }
        }
        finally {
            callback.dispose();
        }
        return counts;
    }

    private boolean write(DecompileResults results, Path out) throws Exception {
        Function function = results.getFunction();
        String va = "0x" + Long.toHexString(function.getEntryPoint().getOffset());
        if (!results.decompileCompleted() || results.getDecompiledFunction() == null) {
            Files.writeString(out.resolve(va + ".err"), String.valueOf(results.getErrorMessage()) + "\n");
            return false;
        }
        StringBuilder text = new StringBuilder();
        text.append("// wb_va ").append(va).append(' ').append(function.getName(true)).append('\n');
        for (Map.Entry<Long, String> callee : callees(function).entrySet()) {
            text.append("// callee 0x").append(Long.toHexString(callee.getKey()))
                .append(' ').append(callee.getValue()).append('\n');
        }
        text.append(results.getDecompiledFunction().getC());
        Files.writeString(out.resolve(va + ".c"), text.toString(), StandardCharsets.UTF_8);
        return true;
    }

    /** {callee entry va: qualified name}, thunks resolved to their targets. */
    private Map<Long, String> callees(Function function) {
        Map<Long, String> callees = new TreeMap<>();
        for (Function callee : function.getCalledFunctions(TaskMonitor.DUMMY)) {
            Function target = resolved(callee);
            if (target != null && !target.isExternal()) {
                callees.put(target.getEntryPoint().getOffset(), target.getName(true));
            }
        }
        return callees;
    }
}
