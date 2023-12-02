#ifndef ANY_CONN_NONCOPY_H
#define ANY_CONN_NONCOPY_H
namespace {
class NonCopy {
 public:
  NonCopy() = default;
  virtual ~NonCopy() = default;

  NonCopy(NonCopy &) = delete;
  NonCopy& operator=(NonCopy &) = delete;
};
}
#endif
