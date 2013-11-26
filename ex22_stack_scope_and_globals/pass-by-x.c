#include "../dbg.h"

void pass(int val, int *ref, int *dref) {
  int deref = *dref;
  log_info("val is %d, ref is %d, deref is %d", val, *ref, deref);
  val++;
  (*ref)++;
  deref++;
  log_info("val is %d, ref is %d, deref is %d", val, *ref, deref);
}

int main(void) {

  int byval = 1;
  int byref = 1;
  int byrefderef = 1;

  log_info("byval %d, byref %d, byref-deref %d", byval, byref, byrefderef);
  pass(byval, &byref, &byrefderef);

  log_info("byval %d, byref %d, byref-deref %d", byval, byref, byrefderef);

  return 0;
}
