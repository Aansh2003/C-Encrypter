# C++ Encrypter

C++ Library to implement various symmetric and asymmetric encryption methods. Supports OpenMP based parallelization for speedup.

## Installation

```
cd build
cmake ..
```

Build the library using

```
cmake --build .
```

## Implemented

Current support available for - Alphabets, ASCII, Unicode (UTF-8)

- [x] Caesar cipher
- [x] Monoalphabetic cipher
- [x] Playfair cipher
- [ ] Hill Cipher

More algorithms will be implemented

## Other work

Creating an API that other Languages and Users can use to Encrypt or Decrypt data.

## Metrics

String size - 10000000  characters.

| Algorithm     | Time taken | OpenMP time taken | speedup |
| :------------:| :---------:| :----------------:| :------:|
| Caesar Cipher | 108 ms     | 36 ms             | 3.0     |
| MA Cipher     | 260 ms     | 153 ms            | 1.7     |
| PF Cipher     | 290 ms     | N/A               | N/A     |

