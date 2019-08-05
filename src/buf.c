#include "buf.h"
#include "conf.h"

#define JPEC_BUFFER_INIT_SIZ (0x8000-1000)

/*
jpec_buffer_t *jpec_buffer_new(void) {
  return jpec_buffer_new2(-1);
}

jpec_buffer_t *jpec_buffer_new2(int siz) {
  if (siz < 0) siz = 0;
  jpec_buffer_t *b = malloc(sizeof(*b));
  jpec_buffer_init(b, siz);
  return b;
}
*/

void jpec_buffer_init(jpec_buffer_t *b, int siz) {
  b->stream = siz > 0 ? malloc(siz) : NULL;
  b->siz = siz;
  b->len = 0;
}

/*
void jpec_buffer_del(jpec_buffer_t *b) {
  assert(b);
  if (b->stream) free(b->stream);
  free(b);
}
*/
void jpec_buffer_finish(jpec_buffer_t *b) {
    if (b->stream)
        free (b->stream);
}

void jpec_buffer_write_byte(jpec_buffer_t *b, int val) {
  assert(b);
  if (b->siz == b->len) {
    int nsiz = (b->siz > 0) ? 2 * b->siz : JPEC_BUFFER_INIT_SIZ;
    void* tmp = realloc(b->stream, nsiz);
    if (tmp == NULL) {
        int foo = 1;
    }
    b->stream = (uint8_t *) tmp;
    b->siz = nsiz;
  }
  b->stream[b->len++] = (uint8_t) val;
}

void jpec_buffer_write_2bytes(jpec_buffer_t *b, int val) {
  assert(b);
  jpec_buffer_write_byte(b, (val >> 8) & 0xFF);
  jpec_buffer_write_byte(b, val & 0xFF);
}
