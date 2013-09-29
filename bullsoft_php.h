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

#endif
