dnl $Id$
dnl config.m4 for extension binaryjson

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(binaryjson, for binaryjson support,
dnl Make sure that the comment is aligned:
[  --with-binaryjson             Include binaryjson support])

if test "$PHP_BINARYJSON" != "no"; then
   PHP_NEW_EXTENSION(binaryjson, binaryjson.c, $ext_shared)
fi
