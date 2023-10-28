#!/bin/bash

echo "[Compiling...]"
make
echo
echo "[Copying data files for app...]"
rsync -r datafiles/ bin/
echo
echo "[Attempting to open program...]"
cd bin
./nokuplayer
cd ..