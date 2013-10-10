#ifndef __BINARYJSON_ID_H__
#define __BINARYJSON_ID_H__

void generate_id(char *data TSRMLS_DC);
void php_binaryjson_id_populate(zval *newid, zval *id TSRMLS_DC);
char *php_binaryjson_id_to_hex(char *id_str);

#endif
