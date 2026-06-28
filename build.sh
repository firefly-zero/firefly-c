#!/bin/bash
# Build script for static docs used on Cloudflare Pages.
set -e
wget https://www.doxygen.nl/files/doxygen-1.17.0.linux.bin.tar.gz
tar xf doxygen-*.tar.xz
rm doxygen-*.tar.xz
./doxygen-*/bin/doxygen

