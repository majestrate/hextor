#!/bin/sh

rm -rf Hextor.app
rm -f *.app.zip

python $HOME/.local/bin/gtk-mac-bundler hextor.bundle

echo "Compressing bundle"
#hdiutil create -format UDBZ -srcdir Hextor.app -quiet Hextor-2.9.6.1-$(git rev-parse --short master).dmg
zip -9rXq ./Hextor-$(git describe --tags).app.zip ./Hextor.app

