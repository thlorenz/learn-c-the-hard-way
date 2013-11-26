#include "ex22.h"
#include "../dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count) {
  log_info("count is %d", count);

  if (count > 10) {
    // shadows count param
    int count = 100;
    log_info("count in inner scope %d", count);
  }

  log_info("count param still is %d", count);
  count = 3000;

  log_info("count param after assign is %d", count);
}

int main(void) {

  log_info("My name: %s, age: %d", MY_NAME, get_age());

  set_age(100);

  log_info("My age i snow: %d", get_age());

  log_info("THE_SIZE is: %d", THE_SIZE);
  print_size();

  THE_SIZE = 9;

  log_info("Ratio at first: %f", update_ratio(2.0));
  log_info("Ratio again: %f", update_ratio(10.0));
  log_info("Ratio once more: %f", update_ratio(300.0));

  // test the scope demo
  int count = 4;
  scope_demo(count);
  scope_demo(count * 20);

  log_info("count after calling scope_demo: %d", count);

  return 0;
}
