pyinstaller --onefile --name fsat-grs --icon ../img/icon.png -p ../gui ../src/main.py
mv dist/fsat-grs fsat-grs
rmdir dist
rm -rf build
rm fsat-grs.spec