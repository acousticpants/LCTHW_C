!#/usr/bin/sh

set -e

cd /tmp

sudo chmod +x devpkg.c

./devpkg I:L:c:m:i:d:SF:B:

check(something, "arg %s didn't work out", argv)