#ifndef __STRM__
#define __STRM__

#include <stdint.h>
#include <stdbool.h>

typedef enum {STRM_EVENT_NONE, STRM_EVENT_RX_DONE} strm_event_t;

// Callback function signature
typedef void (*strm_callback)(strm_event_t evt);

void strm_init(strm_callback cb);
void strm_send(uint8_t * data, uint32_t len);
void strm_receive_init(uint8_t * data, uint32_t len);
bool strm_send_done();
bool strm_receive_done();
void strm_task(void * params);

#endif