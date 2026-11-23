To use the API we need OpenSSL, which allows for a secure communication between the server and the client, so it can't be run in the cs100 server :/

Just use the CMakeLists to create the make file and run it `./bin/db`, if you get an error regarding **OpenSSL** you need to install it in your computer:

**Mac using homebrew:**
```
brew install openssl
```

**Windows (i took this from Gemini, im not sure if it works u would need to research):**
```
winget install ShiningLight.OpenSSL.Dev
```
Make sure to install the .Dev package—not OpenSSL.Light—because cpp-httplib needs the C/C++ .h headers and .lib files.

Then tell CMake where it was installed when configuring:

```
cmake -S . -B build -DOPENSSL_ROOT_DIR="C:\Program Files\OpenSSL-Win64"
cmake --build build
```