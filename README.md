# FF Profiles

Build

```
gcc $(pkg-config --cflags gtk4) -o build/ff_profiles src/*.c $(pkg-config --libs gtk4)
```

Run

```
./build/ff_profiles https://example.org
```

Setup

```
sudo cp build/ff_profiles /usr/lib/
```

Put profile images to `~/.ff_profiles`
