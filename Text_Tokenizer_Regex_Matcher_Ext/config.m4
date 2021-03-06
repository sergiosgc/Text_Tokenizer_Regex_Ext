dnl
dnl $ Id: $
dnl

PHP_ARG_ENABLE(Text_Tokenizer_Regex_Matcher_Ext, whether to enable Text_Tokenizer_Regex_Matcher_Ext functions,
[  --enable-Text_Tokenizer_Regex_Matcher_Ext         Enable Text_Tokenizer_Regex_Matcher_Ext support])

if test "$PHP_TEXT_TOKENIZER_REGEX_MATCHER_EXT" != "no"; then

PHP_ARG_WITH(pcre, whether pcre is available,[  --with-pcre[=DIR]    With pcre support])



  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_PCRE"
  PHP_SUBST(TEXT_TOKENIZER_REGEX_MATCHER_EXT_SHARED_LIBADD)

  PHP_ADD_LIBRARY_WITH_PATH(pcre, $PHP_PCRE_DIR/lib, TEXT_TOKENIZER_REGEX_MATCHER_EXT_SHARED_LIBADD)
  export CPPFLAGS="$OLD_CPPFLAGS"

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_TEXT_TOKENIZER_REGEX_MATCHER_EXT"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 50000
#error  this extension requires at least PHP version 5.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 5.0.0])])

  export CPPFLAGS="$OLD_CPPFLAGS"


  PHP_SUBST(TEXT_TOKENIZER_REGEX_MATCHER_EXT_SHARED_LIBADD)
  AC_DEFINE(HAVE_TEXT_TOKENIZER_REGEX_MATCHER_EXT, 1, [ ])

  PHP_NEW_EXTENSION(Text_Tokenizer_Regex_Matcher_Ext, Text_Tokenizer_Regex_Matcher_Ext.c , $ext_shared)

fi

