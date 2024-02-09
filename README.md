# Godot Gadgets (GDExtension Suite)

A simple collection of miscelaneous nodes. This is a toy project currently. No guarantees, mostly used for personal testing, GDExtension debugging and development.

If you stumble upon this, know that this is mostly for debugging the Godot feature set. Nothing to see here, yada yada.

## Nodes

### MovementSensor[2D|3D]

Tracks all movement in space and reports it via signals OR can be read via methods. This is essentially a reimplementation of Dreams' movement sensor.


## Building

There are two possible build methods.

Option 1: Adding `godot_cpp` build flag to specify directory of `godotengine/godot-cpp` git repository.

```bash
scons godot_cpp=path/to/godot-cpp
```

Option 2: Clone `godotengine/godot-cpp` to `./godot-cpp` and simply run scons. (A symlink is also a valid option, depending on your preference.)

```bash
git clone <repo> ./godot-cpp # Or `ln -s <path> ./godot-cpp` or whatever equivalent on your operating system of choice
scons 
```


## Installing

Copy all binaries and `.gdextension` files found in `project/bin` after compilation. If I find a better use for this project as an addon, I will consider making a distribute build flag for quickly packaging and deploying addon releases. 