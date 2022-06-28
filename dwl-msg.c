#include <czmq.h>
#include <czmq_library.h>
#include <czmq_prelude.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <zframe.h>
#include <zloop.h>
#include <zmsg.h>
#include <zpoller.h>
#include <zsock.h>
#include <zstr.h>

int main(int argc, char **argv) {
  printf("syntax: dwl-msg\n");
  zsock_t *req = zsock_new_req("ipc:///tmp/dwl.ipc");
  assert(req);

  if (argc == 3) {
      if (streq(argv[1], "tag")) {

	  zmsg_t *msg = zmsg_new();

	  u_int16_t id = 0;
	  zframe_t *idframe = zframe_new(&id, 2);
	  zmsg_add(msg, idframe);

	  u_int8_t tag = atoi(argv[2]);
	  zframe_t *tagframe = zframe_new(&tag, 1);
	  zmsg_add(msg, tagframe);

	  zmsg_send(&msg, req);
      }
  }


  zpoller_t *poller = zpoller_new(req, NULL);
  zpoller_set_nonstop(poller, true);

  while (true) {
      zsock_t *ready = zpoller_wait(poller, 500);
      if (ready == NULL) break;
      else assert(ready == req);

      zmsg_t *msg = zmsg_recv(req);
      if (msg) {
	  assert(zframe_streq(zmsg_last(msg), "y"));
	  break;
      }
  }

  zpoller_destroy(&poller);
  zsock_destroy(&req);
  return 0;
}
