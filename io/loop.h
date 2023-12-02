#ifndef ANY_CONN_LOOP_H
#define AYN_CONN_LOOP_H

#include <iostream>
#include <unordered_map>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include "common.h"

namespace net {

class Loop : public NonCopy {
 public:
  Loop();
  ~Loop();

 public:
  void loop();
  void activeFunctor(FunctorCallback &callback);

 private:
  void procActiveEvents();
  void procActiveFunctors();  

 private:
  bool openflag_;
  int epfd_;
  eventfd wakeupfd_;
  std::unordered_map<int, Event*> events_;
  std::vector<epoll_event> active_event_list_;
  std::vector<Callback> active_functor_list_;
};

}
#endif
