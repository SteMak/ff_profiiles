```
gcc $( pkg-config --cflags gtk4 ) -o build/main src/*.c $( pkg-config --libs gtk4 ) && ./build/main https://manjaro.org
```
