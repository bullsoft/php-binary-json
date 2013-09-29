#ifndef BULLSOFT_PHP_H
#define BULLSOFT_PHP_H

#ifndef PHP_FE_END
#define PHP_FE_END { NULL, NULL, NULL, 0, 0 }
#endif

#ifndef ZEND_MOD_END
#define ZEND_MOD_END { NULL, NULL, NULL, 0 }
#endif

#if PHP_VERSION_ID >= 50400
#define BULLSOFT_INIT_FUNCS(class_functions) static const zend_function_entry class_functions[] =
#else
#define BULLSOFT_INIT_FUNCS(class_functions) static const function_entry class_functions[] =
#endif

#define BULLSOFT_INIT_CLASS(extname, name)                   \
    int extname## _ ##name## _init(INIT_FUNC_ARGS)

#define BULLSOFT_INIT(extname, name)                                        \
    if (extname## _ ##name## _init(INIT_FUNC_ARGS_PASSTHRU) == FAILURE) { \
        return FAILURE; \
    }

#define BULLSOFT_REGISTER_CLASS(extname, class_name, name, methods, flags)   \
  { \
    zend_class_entry ce; \
    memset(&ce, 0, sizeof(zend_class_entry)); \
    INIT_CLASS_ENTRY(ce, #class_name, methods); \
    extname## _ ##name## _ce = zend_register_internal_class(&ce TSRMLS_CC); \
    extname## _ ##name## _ce->ce_flags |= flags;  \
  }

#define HASH_P(a) (Z_TYPE_P(a) == IS_ARRAY ? Z_ARRVAL_P(a) : Z_OBJPROP_P(a))
#define HASH_PP(a) (Z_TYPE_PP(a) == IS_ARRAY ? Z_ARRVAL_PP(a) : Z_OBJPROP_PP(a))

#define IS_SCALAR_P(a) (Z_TYPE_P(a) == IS_NULL || Z_TYPE_P(a) == IS_LONG || Z_TYPE_P(a) == IS_DOUBLE || Z_TYPE_P(a) == IS_BOOL || Z_TYPE_P(a) == IS_STRING)
#define IS_SCALAR_PP(a) IS_SCALAR_P(*a)
#define IS_ARRAY_OR_OBJECT_P(a) (Z_TYPE_P(a) == IS_ARRAY || Z_TYPE_P(a) == IS_OBJECT)

/* TODO: this should be expanded to handle long_as_object being set */
#define Z_NUMVAL_P(variable, value)                                     \
  ((Z_TYPE_P(variable) == IS_LONG && Z_LVAL_P(variable) == value) ||    \
   (Z_TYPE_P(variable) == IS_DOUBLE && Z_DVAL_P(variable) == value))
#define Z_NUMVAL_PP(variable, value)                                    \
  ((Z_TYPE_PP(variable) == IS_LONG && Z_LVAL_PP(variable) == value) ||  \
   (Z_TYPE_PP(variable) == IS_DOUBLE && Z_DVAL_PP(variable) == value))

#define BULLSOFT_EXCEPTION(msg) zend_throw_exception(zend_exception_get_default(TSRMLS_C), #msg, 0 TSRMLS_CC);

#endif
