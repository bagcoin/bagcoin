‘⁄ windows√¸¡Ó–– ‰»Î£∫
set INCLUDE=F:\deps\libpng-1.6.10;F:\deps\openssl-1.0.1g\include
set LIB=F:\deps\libpng-1.6.10\.libs;F:\deps\openssl-1.0.1g

cd F:\Qt\5.2.1
configure.bat -release -opensource -confirm-license -static -make libs -no-sql-sqlite -no-opengl -system-zlib -qt-pcre -no-icu -no-gif -system-libpng -no-libjpeg -no-freetype -no-angle -no-vcproj -openssl-linked -no-dbus -no-audio-backend -no-wmf-backend -no-qml-debug

mingw32-make

set PATH=%PATH%;F:\Qt\5.2.1\bin

cd F:\Qt\qttools-opensource-src-5.2.1
qmake qttools.pro
mingw32-make

LIBS="../libpng-1.6.10/.libs/libpng16.a ../../mingw32/i686-w64-mingw32/lib/libz.a" png_CFLAGS="-I../libpng-1.6.10" png_LIBS="-L../libpng-1.6.10/.libs" configure --enable-static --disable-shared --without-tools

./autogen.sh

#share
./configure --with-gui=qt5 --disable-upnp-default --disable-tests --with-qt-incdir=/f/Qt/5.3.2/include --with-qt-libdir=/f/Qt/5.3.2/lib --with-qt-bindir=/f/Qt/5.3.2/bin --with-qt-plugindir=/f/Qt/5.3.2/plugins --with-boost-system=mgw48-mt-s-1_55 --with-boost-filesystem=mgw48-mt-s-1_55 --with-boost-program-options=mgw48-mt-s-1_55 --with-boost-thread=mgw48-mt-s-1_55 --with-boost-chrono=mgw48-mt-s-1_55 --with-protoc-bindir=/f/deps/protobuf-2.5.0/src  CPPFLAGS="-I/f/deps/boost_1_55_0 -I/local/BerkeleyDB.4.8/include/ -I/f/deps/openssl-1.0.1g/include -I/f/deps -I/f/deps/protobuf-2.5.0/src -I/f/deps/libpng-1.6.10 -I/f/deps/qrencode-3.4.3" LDFLAGS="-L/f/deps/boost_1_55_0/stage/lib -L/local/BerkeleyDB.4.8/lib/ -L/f/deps/openssl-1.0.1g -L/f/deps/miniupnpc -L/f/deps/protobuf-2.5.0/src/.libs -L/f/deps/libpng-1.6.10/.libs -L/f/deps/qrencode-3.4.3/.libs" 

#static
./configure --with-gui=qt5 --enable-upnp-default --disable-tests --with-qt-incdir=/f/deps/qtbase-opensource-src-5.2.1/include --with-qt-libdir=/f/deps/qtbase-opensource-src-5.2.1/lib --with-qt-bindir=/f/deps/qtbase-opensource-src-5.2.1/bin --with-qt-plugindir=/f/deps/qtbase-opensource-src-5.2.1/plugins --with-boost-system=mgw48-mt-s-1_55 --with-boost-filesystem=mgw48-mt-s-1_55 --with-boost-program-options=mgw48-mt-s-1_55 --with-boost-thread=mgw48-mt-s-1_55 --with-boost-chrono=mgw48-mt-s-1_55 --with-protoc-bindir=/f/deps/protobuf-2.5.0/src  CPPFLAGS="-I/f/deps/boost_1_55_0 -I/local/BerkeleyDB.4.8/include/ -I/f/deps/openssl-1.0.1g/include -I/f/deps -I/f/deps/protobuf-2.5.0/src -I/f/deps/libpng-1.6.10 -I/f/deps/qrencode-3.4.3" LDFLAGS="-L/f/deps/boost_1_55_0/stage/lib -L/local/BerkeleyDB.4.8/lib/ -L/f/deps/openssl-1.0.1g -L/f/deps/miniupnpc -L/f/deps/protobuf-2.5.0/src/.libs -L/f/deps/libpng-1.6.10/.libs -L/f/deps/qrencode-3.4.3/.libs" 

make



set PATH=%PATH%;F:\deps\qtbase-opensource-src-5.2.1\bin


qmake.exe bagcoin-qt.pro -r -spec win32-g++
