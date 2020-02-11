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

void jpec_buffer_init(jpec_buffer_t *b, uint8_t *stack_memory, int siz) {
  if (stack_memory) {
      b->stream = stack_memory;
      b->siz = siz;
      b->dynamic_on_heap = false;
  }
  else {
      b->stream = siz > 0 ? malloc(siz) : NULL;
      b->siz = b->stream ? siz : 0;
      b->dynamic_on_heap = true;
  }
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
    if (b->dynamic_on_heap && b->stream)
        free (b->stream);
}

int8_t jpec_buffer_write_byte(jpec_buffer_t *b, int val) {
  assert(b);
  if (b->siz == b->len) { // current buffer is full
    if (!b->dynamic_on_heap) {
        return -1;
    }
    else {
        int nsiz = (b->siz > 0) ? 2 * b->siz : JPEC_BUFFER_INIT_SIZ; // new buffer size
        void *tmp = realloc(b->stream, nsiz); // try to allocate bigger memory region
        if (tmp == NULL) {
            return -2;
        }
        b->stream = (uint8_t *) tmp;
        b->siz = nsiz;
    }
  }
  b->stream[b->len++] = (uint8_t) val;
  return 0;
}

int8_t jpec_buffer_write_2bytes(jpec_buffer_t *b, int val) {
  assert(b); // For Keil uVision projects: Add NDEBUG define to avoid "Undefined symbol __aeabi_assert"
  int8_t err = jpec_buffer_write_byte(b, (val >> 8) & 0xFF);
  err |= jpec_buffer_write_byte(b, val & 0xFF);
  return err;
}
