#!/bin/bash
# Build script for static docs used on Cloudflare Pages.
set -e
which doxygen || apt install -y doxygen
doxygen
