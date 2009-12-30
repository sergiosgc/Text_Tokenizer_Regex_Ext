/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Sergio Carvalho <sergiosgc@pear.php.net>                    |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#ifndef PHP_TEXT_TOKENIZER_REGEX_MATCHER_EXT_H
#define PHP_TEXT_TOKENIZER_REGEX_MATCHER_EXT_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_TEXT_TOKENIZER_REGEX_MATCHER_EXT

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef  __cplusplus
} // extern "C" 
#endif
#include <pcre.h>
typedef struct {
	char* input;
	char* cursor;
} text_tokenizer_regex_matcher_ext_input;
struct text_tokenizer_regex_matcher_ext_regex_item_struct {
	pcre* regex;
	struct text_tokenizer_regex_matcher_ext_regex_item_struct* next;
};
typedef struct text_tokenizer_regex_matcher_ext_regex_item_struct text_tokenizer_regex_matcher_ext_regex_item;
typedef struct {
	text_tokenizer_regex_matcher_ext_regex_item* first;
	text_tokenizer_regex_matcher_ext_regex_item* last;
} text_tokenizer_regex_matcher_ext_regex_list;
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry Text_Tokenizer_Regex_Matcher_Ext_module_entry;
#define phpext_Text_Tokenizer_Regex_Matcher_Ext_ptr &Text_Tokenizer_Regex_Matcher_Ext_module_entry

#ifdef PHP_WIN32
#define PHP_TEXT_TOKENIZER_REGEX_MATCHER_EXT_API __declspec(dllexport)
#else
#define PHP_TEXT_TOKENIZER_REGEX_MATCHER_EXT_API
#endif

PHP_MINIT_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext);
PHP_MSHUTDOWN_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext);
PHP_RINIT_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext);
PHP_RSHUTDOWN_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext);
PHP_MINFO_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)    Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)    Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)    Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, setInput);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Text_Tokenizer_Regex_Matcher_Ext__setInput_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Text_Tokenizer_Regex_Matcher_Ext__setInput_args NULL
#endif

PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, setSelectionCriteria);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Text_Tokenizer_Regex_Matcher_Ext__setSelectionCriteria_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, selectionCriteria)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Text_Tokenizer_Regex_Matcher_Ext__setSelectionCriteria_args NULL
#endif

PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, addRegex);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Text_Tokenizer_Regex_Matcher_Ext__addRegex_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, regex)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Text_Tokenizer_Regex_Matcher_Ext__addRegex_args NULL
#endif

PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, match);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Text_Tokenizer_Regex_Matcher_Ext__match_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Text_Tokenizer_Regex_Matcher_Ext__match_args NULL
#endif

PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, consume);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Text_Tokenizer_Regex_Matcher_Ext__consume_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, howMuch)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Text_Tokenizer_Regex_Matcher_Ext__consume_args NULL
#endif

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_HAVE_TEXT_TOKENIZER_REGEX_MATCHER_EXT */

#endif /* PHP_TEXT_TOKENIZER_REGEX_MATCHER_EXT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
