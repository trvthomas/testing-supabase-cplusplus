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



## In the CS100 server

We need to run the following commands when logged in to the class server, don't ask:

```
cd ~
curl -LO https://github.com/openssl/openssl/releases/download/openssl-3.0.15/openssl-3.0.15.tar.gz
tar -xzf openssl-3.0.15.tar.gz
cd openssl-3.0.15
./config no-shared --prefix=$HOME/local --openssldir=$HOME/local/ssl
make -j4
make install

cd ~
rm -rf openssl-3.0.15 openssl-3.0.15.tar.gz

ls $HOME/local/lib64/*.a

export OPENSSL_ROOT_DIR=$HOME/local
ln -sf /etc/pki/tls/certs/ca-bundle.crt $HOME/local/ssl/cert.pem
```