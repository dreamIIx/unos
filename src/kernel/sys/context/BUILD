cc_library(
    name = "interruption",
    srcs = ["interruption.c"],
    hdrs = ["idt.h", "interruption.h", "tramplins.hpp"],
    deps = [
        "//src/sys/memory:memory",
        "//src/sys/io:io",
        "//src/sys/context:context",
    ],
)