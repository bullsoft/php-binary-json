#include <php.h>
#include <zend_exceptions.h>
#include "php_binaryjson.h"
#include "binaryjson.h"
#include "id.h"

ZEND_EXTERN_MODULE_GLOBALS(binaryjson)

void generate_id(char *data TSRMLS_DC)
{
  int inc;

#ifdef WIN32
  int pid = GetCurrentThreadId();
#else
  int pid = (int)getpid();
#endif

  unsigned t = (unsigned) time(0);
  char *T = (char*)&t,
    *M = (char*)&BINARYJSON_G(machine),
    *P = (char*)&pid,
    *I = (char*)&inc;

  /* inc */
  inc = BINARYJSON_G(inc);
  BINARYJSON_G(inc)++;

  /* actually generate the MongoId */
#if PHP_C_BIGENDIAN
  /* 4 bytes ts */
  memcpy(data, T, 4);

  /* we add 1 or 2 to the pointers so we don't end up with all 0s, as the
   * interesting stuff is at the end for big endian systems */

  /* 3 bytes machine */
  memcpy(data + 4, M + 1, 3);

  /* 2 bytes pid */
  memcpy(data + 7, P + 2, 2);

  /* 3 bytes inc */
  memcpy(data + 9, I + 1, 3);
#else
  /* 4 bytes ts */
  data[0] = T[3];
  data[1] = T[2];
  data[2] = T[1];
  data[3] = T[0];

  /* 3 bytes machine */
  memcpy(data + 4, M, 3);

  /* 2 bytes pid */
  memcpy(data + 7, P, 2);

  /* 3 bytes inc */
  data[9] = I[2];
  data[10] = I[1];
  data[11] = I[0];
#endif
}

char *php_binaryjson_id_to_hex(char *id_str)
{
  int i;
  char *id = (char*)emalloc(25);

  for ( i = 0; i < 12; i++) {
    int x = *id_str;
    char digit1, digit2;

    if (*id_str < 0) {
      x = 256 + *id_str;
    }

    digit1 = x / 16;
    digit2 = x % 16;

    id[2 * i]   = (digit1 < 10) ? '0' + digit1 : digit1 - 10 + 'a';
    id[2 * i + 1] = (digit2 < 10) ? '0' + digit2 : digit2 - 10 + 'a';

    id_str++;
  }

  id[24] = '\0';

  return id;
}

void php_binaryjson_id_populate(zval *newid, zval *id TSRMLS_DC)
{
  char *bid;
  bid = (char*)emalloc(OID_SIZE + 1);
  bid[OID_SIZE] = '\0';

  if (id && Z_TYPE_P(id) == IS_STRING && Z_STRLEN_P(id) == 24) {
    int i;
    if (strspn(Z_STRVAL_P(id), "0123456789abcdefABCDEF") != 24) {
      zend_throw_exception(zend_exception_get_default(TSRMLS_C), "ID must be valid hex characters", 18 TSRMLS_CC);
      return;
    }
    for (i = 0; i < 12;i++) {
      char digit1 = Z_STRVAL_P(id)[i * 2], digit2 = Z_STRVAL_P(id)[i * 2 + 1];

      digit1 = digit1 >= 'a' && digit1 <= 'f' ? digit1 - 87 : digit1;
      digit1 = digit1 >= 'A' && digit1 <= 'F' ? digit1 - 55 : digit1;
      digit1 = digit1 >= '0' && digit1 <= '9' ? digit1 - 48 : digit1;

      digit2 = digit2 >= 'a' && digit2 <= 'f' ? digit2 - 87 : digit2;
      digit2 = digit2 >= 'A' && digit2 <= 'F' ? digit2 - 55 : digit2;
      digit2 = digit2 >= '0' && digit2 <= '9' ? digit2 - 48 : digit2;

      bid[i] = digit1 * 16 + digit2;
    }
    
  } else {
    generate_id(bid TSRMLS_CC);
  }
  char *tmp_id;
  tmp_id = php_binaryjson_id_to_hex(bid);
  ZVAL_STRING(newid, tmp_id, 0);
}

int php_binaryjson_id_serialize(char *id, unsigned char **serialized_data, zend_uint *serialized_length, zend_serialize_data *var_hash TSRMLS_DC)
{
  char *tmp_id;
  tmp_id = php_binaryjson_id_to_hex(id);
  *(serialized_length) = strlen(tmp_id);
  *(serialized_data) = (unsigned char*)tmp_id;
  return SUCCESS;
}

int php_binaryjson_id_unserialize(zval *rval, const unsigned char* p TSRMLS_DC)
{
  zval *str;
  
  MAKE_STD_ZVAL(str);
  ZVAL_STRINGL(str, (const char*)p, 24, 1);
  php_binaryjson_id_populate(rval, str TSRMLS_CC);
  zval_ptr_dtor(&str);

  return SUCCESS;
}
