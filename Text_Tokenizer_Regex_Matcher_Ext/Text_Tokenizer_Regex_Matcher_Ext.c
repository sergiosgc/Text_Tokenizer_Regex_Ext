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

#include "php_Text_Tokenizer_Regex_Matcher_Ext.h"

#if HAVE_TEXT_TOKENIZER_REGEX_MATCHER_EXT

/* {{{ Class definitions */

/* {{{ Class Text_Tokenizer_Regex_Matcher_Ext */

static zend_class_entry * Text_Tokenizer_Regex_Matcher_Ext_ce_ptr = NULL;

/* {{{ Methods */


/* {{{ proto void setInput(string value)
   */
PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, setInput)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * value = NULL;
	int value_len = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, Text_Tokenizer_Regex_Matcher_Ext_ce_ptr, &value, &value_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	do {
		zval* zinput;
		zinput = zend_read_property(_this_ce, _this_zval, "input", strlen("input"), 1);
		if (Z_TYPE_P(zinput) == IS_RESOURCE) { /* Free previous value if existent */
			efree((void*) ((text_tokenizer_regex_matcher_ext_input*) Z_RESVAL_P(zinput))->input );
			efree((void*) Z_RESVAL_P(zinput));
			zval_ptr_dtor(&zinput);
		}
		
		/* Store new value */
		text_tokenizer_regex_matcher_ext_input* newVal;
		newVal = emalloc(sizeof(text_tokenizer_regex_matcher_ext_input));
		newVal->input = newVal->cursor = (char*) emalloc(strlen(value) + 1);
		strncpy(newVal->input, value, strlen(value));
		newVal->input[strlen(value)] = 0;
		ZVAL_RESOURCE(zinput, (long) newVal);
	} while (0);
}
/* }}} setInput */



/* {{{ proto void setSelectionCriteria(int selectionCriteria)
   */
PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, setSelectionCriteria)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long selectionCriteria = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Text_Tokenizer_Regex_Matcher_Ext_ce_ptr, &selectionCriteria) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	do {
		zval* attribute;
		attribute = zend_read_property(_this_ce, _this_zval, "selectionCriteria", strlen("selectionCriteria"), 1);
		ZVAL_LONG(attribute, selectionCriteria);
	} while (0);
}
/* }}} setSelectionCriteria */



/* {{{ proto void addRegex(string regex)
   */
PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, addRegex)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * regex = NULL;
	int regex_len = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, Text_Tokenizer_Regex_Matcher_Ext_ce_ptr, &regex, &regex_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	do {
		if (strlen(regex) < 3) {
			php_error(E_ERROR, "Regular expression has no terminator characters"); RETURN_FALSE;
			RETURN_FALSE;
		}
		
		char* pcreRegex;
		text_tokenizer_regex_matcher_ext_regex_item* newItem;
		int pcreCompileError;
		int pcreCompileErrorOffset;
		
		pcreRegex = (char*) emalloc(sizeof(char) * (2 + strlen(regex)));
		pcreRegex += 1;
		strcpy(pcreRegex, regex);
		pcreRegex[strlen(pcreRegex) - 1] = ')';
		pcreRegex -= 1;
		pcreRegex[0] = '^';
		pcreRegex[1] = '(';
		
		newItem = (text_tokenizer_regex_matcher_ext_regex_item*) emalloc(sizeof(text_tokenizer_regex_matcher_ext_regex_item));
		newItem->next = NULL;
		newItem->regex = pcre_compile(pcreRegex, 0, &pcreCompileError, &pcreCompileErrorOffset, NULL);
		efree(pcreRegex);
		
		if (newItem->regex == NULL) {
			php_error(E_ERROR, "Regular expression compilation failed"); RETURN_FALSE;
			RETURN_FALSE;
		}
		
		zval* attribute;
		attribute = zend_read_property(_this_ce, _this_zval, "regexQueue", strlen("regexQueue"), 1);
		if (Z_TYPE_P(attribute) == IS_NULL) { 
			text_tokenizer_regex_matcher_ext_regex_list* list;
			list = emalloc(sizeof(text_tokenizer_regex_matcher_ext_regex_list));
			list->first = list->last = newItem;
			ZVAL_RESOURCE(attribute, (long) list);
		} else {
			text_tokenizer_regex_matcher_ext_regex_list* list;
			list = (text_tokenizer_regex_matcher_ext_regex_list*) Z_RESVAL_P(attribute);
			list->last->next = newItem;
			list->last = newItem;
		}
	} while (0);
}
/* }}} addRegex */



/* {{{ proto array match()
   */
PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, match)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, Text_Tokenizer_Regex_Matcher_Ext_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	array_init(return_value);

	do {
		zval* regexQueue;
		regexQueue = zend_read_property(_this_ce, _this_zval, "regexQueue", strlen("regexQueue"), 1);
		if (Z_TYPE_P(regexQueue) == IS_NULL) { 
			RETURN_FALSE;
		}
		text_tokenizer_regex_matcher_ext_regex_item* item;
		item = ((text_tokenizer_regex_matcher_ext_regex_list*) Z_RESVAL_P(regexQueue))->first;
		
		zval* inputResource;
		inputResource = zend_read_property(_this_ce, _this_zval, "input", strlen("input"), 1);
		if (Z_TYPE_P(inputResource) != IS_RESOURCE) { 
			RETURN_FALSE;
		}
		char* input = ((text_tokenizer_regex_matcher_ext_input*) Z_RESVAL_P(inputResource))->cursor;
		
		zval* selectionCriteriaResource;
		selectionCriteriaResource = zend_read_property(_this_ce, _this_zval, "selectionCriteria", strlen("selectionCriteria"), 1);
		if (Z_TYPE_P(selectionCriteriaResource) != IS_LONG) { 
			RETURN_FALSE;
		}
		int selectionCriteria = Z_LVAL_P(selectionCriteriaResource);
		
		
		int index = 0;
		int longestMatchIndex = -1;
		int longestMatchLength = -1;
		while ( item 
			   && 
				((selectionCriteria == 2)
				 ||
				 (selectionCriteria == 1 && longestMatchIndex == -1)
				) 
			  ) 
		{
			int ovector[3];
			int rc;
			rc = pcre_exec(item->regex, NULL, input, strlen(input), 0, 0, (int*) &ovector, 3);
			if (rc >= 0 && (ovector[1] - ovector[0] > longestMatchLength)) {
				longestMatchLength = ovector[1] - ovector[0];
				longestMatchIndex = index;
			}
			item = item->next;
			index++;
		}
		if (longestMatchIndex == -1) {
			RETURN_FALSE;
		}
		char* result;
		result = (char*) emalloc(sizeof(char) * (1 + longestMatchLength));
		strncpy(result, input, longestMatchLength);
		result[longestMatchLength] = 0;
		
		array_init(return_value);
		add_assoc_long(return_value, "index", longestMatchIndex);
		add_assoc_string(return_value, "value", result, 0);
	} while (0);
}
/* }}} match */



/* {{{ proto void consume(int howMuch)
   */
PHP_METHOD(Text_Tokenizer_Regex_Matcher_Ext, consume)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long howMuch = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Text_Tokenizer_Regex_Matcher_Ext_ce_ptr, &howMuch) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	do {
		zval* zinput;
		zinput = zend_read_property(_this_ce, _this_zval, "input", strlen("input"), 1);
		if (Z_TYPE_P(zinput) == IS_RESOURCE) { 
			((text_tokenizer_regex_matcher_ext_input*) Z_RESVAL_P(zinput))->cursor += howMuch;
		}
	} while (0);
}
/* }}} consume */


static zend_function_entry Text_Tokenizer_Regex_Matcher_Ext_methods[] = {
	PHP_ME(Text_Tokenizer_Regex_Matcher_Ext, setInput, Text_Tokenizer_Regex_Matcher_Ext__setInput_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Text_Tokenizer_Regex_Matcher_Ext, setSelectionCriteria, Text_Tokenizer_Regex_Matcher_Ext__setSelectionCriteria_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Text_Tokenizer_Regex_Matcher_Ext, addRegex, Text_Tokenizer_Regex_Matcher_Ext__addRegex_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Text_Tokenizer_Regex_Matcher_Ext, match, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Text_Tokenizer_Regex_Matcher_Ext, consume, Text_Tokenizer_Regex_Matcher_Ext__consume_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static void class_init_Text_Tokenizer_Regex_Matcher_Ext(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Text_Tokenizer_Regex_Matcher_Ext", Text_Tokenizer_Regex_Matcher_Ext_methods);
	Text_Tokenizer_Regex_Matcher_Ext_ce_ptr = zend_register_internal_class(&ce);

	/* {{{ Property registration */

	zend_declare_property_long(Text_Tokenizer_Regex_Matcher_Ext_ce_ptr, 
		"selectionCriteria", 17, 1, 
		ZEND_ACC_PROTECTED TSRMLS_DC);

	zend_declare_property_string(Text_Tokenizer_Regex_Matcher_Ext_ce_ptr, 
		"input", 5, "", 
		ZEND_ACC_PROTECTED TSRMLS_DC);

	/* }}} Property registration */

}

/* }}} Class Text_Tokenizer_Regex_Matcher_Ext */

/* }}} Class definitions*/

/* {{{ Text_Tokenizer_Regex_Matcher_Ext_functions[] */
function_entry Text_Tokenizer_Regex_Matcher_Ext_functions[] = {
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ Text_Tokenizer_Regex_Matcher_Ext_module_entry
 */
zend_module_entry Text_Tokenizer_Regex_Matcher_Ext_module_entry = {
	STANDARD_MODULE_HEADER,
	"Text_Tokenizer_Regex_Matcher_Ext",
	Text_Tokenizer_Regex_Matcher_Ext_functions,
	PHP_MINIT(Text_Tokenizer_Regex_Matcher_Ext),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(Text_Tokenizer_Regex_Matcher_Ext), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(Text_Tokenizer_Regex_Matcher_Ext),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(Text_Tokenizer_Regex_Matcher_Ext), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(Text_Tokenizer_Regex_Matcher_Ext),
	"1.0.0", 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TEXT_TOKENIZER_REGEX_MATCHER_EXT
ZEND_GET_MODULE(Text_Tokenizer_Regex_Matcher_Ext)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext)
{
	class_init_Text_Tokenizer_Regex_Matcher_Ext();

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(Text_Tokenizer_Regex_Matcher_Ext)
{
	php_info_print_box_start(0);
	php_printf("<p>Text_Tokenizer_Regex_Matcher_Ext is a regexp matcher to be used wit Text_Tokenizer_Regex</p>\n");
	php_printf("<p>Version 1.0.0stable (2007-12-14)</p>\n");
	php_printf("<p><b>Authors:</b></p>\n");
	php_printf("<p>Sergio Carvalho &lt;sergiosgc@pear.php.net&gt; (lead)</p>\n");
	php_info_print_box_end();
	/* add your stuff here */

}
/* }}} */

#endif /* HAVE_TEXT_TOKENIZER_REGEX_MATCHER_EXT */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
