#!/bin/sh

src=$(`dirname $0` && pwd -P)
src="$src""/../src"

dest="/usr/include/dot_lib"

if [ $1 ]
then
	dest=$1
fi

echo "Copying: $src -> $dest"
cp -r $src $dest
