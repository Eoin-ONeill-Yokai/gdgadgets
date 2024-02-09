#!/usr/bin/env python
import os
import sys
import subprocess
from SCons.Variables import PathVariable

# Allow for specifying argument to godot-cpp for manual override. Defaults to subdirectory...
env = Environment(tools=["default"], PLATFORM="")
customs = ["custom.py"]
opts = Variables(customs, ARGUMENTS)
opts.Add(
        PathVariable(
            key="godot_cpp",
            help="Path to directory containing godot-cpp",
            default="./godot-cpp",
        )
    )

opts.Update(env)

godot_cpp = env["godot_cpp"]
# Make a symlink to godot-cpp or add godot-cpp as a submodule or clone as sub project. Whichever you fancy.
env = SConscript(env["godot_cpp"] + "/SConstruct")

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])

# Note: GDExtension tutorial fails to mention the need to include these folders. Is this simply an oversight?
env.Append(
    CPPPATH=[
        os.path.join(godot_cpp, '/include'),
        os.path.join(godot_cpp, '/gen/include')
    ]
)

sources = Glob("src/*.cpp")


if env["platform"] == "macos":
    library = env.SharedLibrary(
        "project/bin/libgdgadgets{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "project/bin/libgdgadgets{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

# Extensions to the scons build per platform. Useful to keep private code private.
platform_directory = "./platform"
for file in os.listdir(platform_directory):
    f = os.path.join(platform_directory, file)
    if os.path.isfile(f) and env["platform"] in file:
        with open(f) as buff: exec(buff.read())


Default(library)