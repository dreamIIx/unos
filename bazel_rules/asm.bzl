def _compile_asm(ctx):
    file = ctx.file.srcs
    output_o = ctx.actions.declare_file(file.basename.replace(file.extension, "o"))

    ctx.actions.run(
        outputs = [output_o],
        inputs = [file],
        executable = "nasm",  # place ur path here
                              # and exec bazel build //src/rm/io/...
        arguments = ["-f", "elf", "./" + file.path, "-o", output_o.basename],
    )

    return DefaultInfo(files=depset([output_o]))

asm_library = rule(
    implementation = _compile_asm,
    attrs = {
        "srcs" : attr.label(allow_single_file = True)
    },
)