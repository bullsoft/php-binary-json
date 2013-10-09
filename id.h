#ifndef __BINARYJSON_ID_H__
#define __BINARYJSON_ID_H__

void generate_id(char *data TSRMLS_DC);
int  php_binaryjson_id_serialize(char*, unsigned char**, zend_uint*, zend_serialize_data* TSRMLS_DC);
int  php_binaryjson_id_unserialize(zval*, const unsigned char* TSRMLS_DC);
void php_binaryjson_id_populate(zval *newid, zval *id TSRMLS_DC);
char *php_binaryjson_id_to_hex(char *id_str);

#endif
