# FormelSamling

Just a silly little project

## OS Status
| OS | State |
| - | - |
| Arch Linux | Working |
| Mac | Working |
| Windows | Working |

## Installing
The only way to try this software is to clone the repo using --recursive

```$ git clone --recursive https://github.com/JJoeDev/FormelSamling```

After cloning you should be ready to run the cmake script that hopefully works on mac and windows aswell

*This is the commands I use on Arch Linux*

```
$ cmake . && make
$ ./bin/FormelSamling
```

### For Windows

Start by making sure cmake is installed and run ```cmake .```

next make sure msbuild is installed in *Developer Command Prompt for VS 2022* (That is where I have tested it on)

next run the following commands to build an executable

```
$ msbuild FormelSamling.sln /p:Configuration=Release /p:Platform=x64
```

Now you should have an executable in ```/bin/Release```


## Source Info

Any errors from spicifically the following includes can be ignored as they are fixed at compile time by sweet cmake

```cpp
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"
```
