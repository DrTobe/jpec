#ifndef JPEC_BUFFER_H
#define JPEC_BUFFER_H

#include <stdint.h>

/** Extensible byte buffer */
typedef struct jpec_buffer_t_ {
  uint8_t *stream;                      /* byte buffer */
  int len;                              /* current length */
  int siz;                              /* maximum size */
} jpec_buffer_t;

jpec_buffer_t *jpec_buffer_new(void);
jpec_buffer_t *jpec_buffer_new2(int siz);
void jpec_buffer_del(jpec_buffer_t *b);
void jpec_buffer_write_byte(jpec_buffer_t *b, int val);
void jpec_buffer_write_2bytes(jpec_buffer_t *b, int val);

#endif
