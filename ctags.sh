#!/usr/bin/sh

ctags -R --extra=+f * ;
ctags -R -e --extra=+f *
