#!/bin/bash
# Build script for static docs used on Cloudflare Pages.
set -e
wget --header='Content-Type: application/json' https://www.doxygen.nl/files/doxygen-1.17.0.linux.bin.tar.gz
tar xf doxygen-*.tar.gz
rm doxygen-*.tar.gz
./doxygen-*/bin/doxygen

