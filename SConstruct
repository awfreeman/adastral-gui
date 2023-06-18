#!/usr/bin/env python
import os
import sys
env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["extension_modules/murse/"])
rdir = os.curdir
os.chdir("extension_modules/murse/murse_c_export")
proc = os.popen("go build -buildmode=c-archive")
print(proc.read())
code = proc.close()
if code is not None:
    exit(-1)
os.rename("murse_c_export.h", "../murse_c_export.h")
os.rename("murse_c_export.a", "../murse_c_export.a")
os.chdir(rdir)
sources = Glob("extension_modules/murse/*.cpp", "extension_modules/murse/*.a")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "bin/libmurse.{}.{}.framework/libmurse.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "bin/libmurse{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
