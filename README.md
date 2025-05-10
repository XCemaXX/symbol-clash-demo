## Symbol Clash Demo

A minimal CMake-based example illustrating how static vs. shared libraries can clash over identical symbols (including templates), and how to resolve it.

### Why This Matters
As projects grow, symbol collisions across static and shared builds (especially with templates) can introduce subtle bugs. This demo shows:
- How the dynamic loader picks the first matching global symbol.
- Three fixes: compile-time visibility hiding, link-time exclusion or version scripts.
- That C++ template functions can collide because each instantiation happens in the compilation unit where it’s first used - so the static library’s instantiation may override the one in the shared library.

### Overview
- **`lib1_v1_shared`** (shared): implements `printVersion()` → “1” and a template `multiply<T>(T a, T b)` .
- **`lib1_v2_static`** (static): implements `printVersion()` → “2” and the same template `multiply<T>(T a, T b)` (additionally adds 200000).
- **`lib2_shared`**: wraps calls into `lib1_v1_shared`.
- **`main_app`**: links both; demonstrates that without hiding symbols, the static version “wins” even inside the shared library.

### Build & Run

```bash
cmake -S . -B build \
      -DWITH_VISIBILITY_HIDDEN=ON/OFF \
      -DWITH_EXCLUDE_LIB2=ON/OFF \
      -DWITH_VERSION_SCRIPT=ON/OFF \
      -DCOMMENT_TEMPLATE_STATIC_CALL=0/1
cmake --build build
./build/bin/main_app
```
- `WITH_VISIBILITY_HIDDEN`  
Compile static lib with `-fvisibility=hidden`.

- `WITH_EXCLUDE_LIB2`  
Link `main_app` with `-Wl,--exclude-libs,libstatic_v2.a`.

- `WITH_VERSION_SCRIPT`  
Apply a linker version script to export only main.

- `COMMENT_TEMPLATE_STATIC_CALL`  
Toggle (`#ifdef`) to comment the direct call to `multiply<int>` in `main_app`.

### What You’ll See
1. Default (no hiding):
```
Static lib_v2 prints: 2
Dynamic libdyn->lib_v1 prints: Call to v1: 2 ← static override!
multiply<int>() direct from v2: 200012
call_multiply_from_v1: Call to v1: 200012 ← static override!
```
2. With hiding/exclude-libs:
```
Static lib_v2 prints: 2
Dynamic libdyn->lib_v1 prints: Call to v1: 1
multiply<int>() direct from v2: 200012
call_multiply_from_v1: Call to v1: 200012 ← static override!
```
3. With commented a direct call to `multiply<int>` in `main_app`
```
Static lib_v2 prints: 2
Dynamic libdyn->lib_v1 prints: Call to v1: 2
call_multiply_from_v1: Call to v1: 12
```
4. With version-script:
```
Static lib_v2 prints: 2
Dynamic libdyn->lib_v1 prints: Call to v1: 1
multiply<int>() direct from v2: 200012
call_multiply_from_v1: Call to v1: 12
```
