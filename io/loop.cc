#include "loop.h"

void Loop::Loop():epfd_(::epoll_create1(0)),openflag_(true),wakeupfd_(eventfd(0, 0)) {
  if (epfd_ < 0) {
    perror("epoll create failed");
  }
}

void Loop::~Loop() {
  openflag_ = false;
  for (auto& event_pair: events_) {
    SAFE_DELETE(event_pair);
  }
  SAFE_DELETE(epfd_);
}

void Loop::loop() {
  epoll_event events[Constants::EpollMaxEvents];
  while (openflag_) {
    int ev_num = ::epoll_wait(epfd_, &events, Constants::EpollWaitTime);
    for (uint8_t i = 0; i < ev_num; i++) {
      active_event_list_.emplace_back(events[i]);
    }
    procActiveEvents();
    procActiveFunctors();
  } 
}

void Loop::activeFunctor(Callback &callback) {
  active_functor_list_.emplace_back(callback);
}

void Loop::procActiveEvents() {
  if (active_event_list_.size() == 0) {
    return;
  }
  for (auto& active_event : active_event_list_) {
    Event *evt = static_cast<Event *>(active_event.data.ptr);
    if (evt.events | EPOLLIN) {
      evt->readCallback();
    } else if (evt.events | EPOLLOUT) {
      evt->writeCallback();
    } else if (evt.events | EPOLLERR) {
      evt->closeCallback();
    }
  }
}

void Loop::procActiveFunctors() {
  for (auto& active_functor : active_functor_list_) {
    active_functor();
  }
}

void Loop::wakeup() {
  uint64_t intflag;
  write(wakeupfd_, &intflag, sizeof(intflag));
}
