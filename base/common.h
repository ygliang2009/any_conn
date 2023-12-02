#ifndef ANY_CONN_COMMON_H
#define ANY_CONN_COMMON_H

#define SAFE_DELETE(x) \
          if ((x) != nullptr) \ 
  	    delete(x); \
  	    x=nullptr; \
          }


namespace base {
using FunctorCallback = std::function<int(Context *)>;
using IOCallback = std::function<int(Context *)>;

class Constants
  const static int EpollMaxEvents = 64;
  const static int EpollWaitTime = 10000;
}
#endif
