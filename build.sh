../firefly-python/wasi-sdk-20.0/bin/clang++ \
    --sysroot=../firefly-python/wasi-sdk-20.0/share/wasi-sysroot \
    --target=wasm32-wasi \
    -fignore-exceptions \
    -o main.wasm \
    examples/triangle/main.cpp
