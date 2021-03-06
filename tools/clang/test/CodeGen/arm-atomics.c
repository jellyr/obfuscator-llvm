// RUN: %clang_cc1 %s -emit-llvm -o - -triple=thumbv7-none--eabi | FileCheck %s
// RUN: %clang_cc1 %s -emit-llvm -o - -triple=armv6-none--eabi | FileCheck %s
// RUN: %clang_cc1 %s -emit-llvm -o - -triple=armv7-unknown-openbsd | FileCheck %s

int i;
long long l;

typedef enum memory_order {
  memory_order_relaxed, memory_order_consume, memory_order_acquire,
  memory_order_release, memory_order_acq_rel, memory_order_seq_cst
} memory_order;

void test_presence(void)
{
  // CHECK-LABEL: @test_presence
  // CHECK: atomicrmw add i32* {{.*}} seq_cst
  __atomic_fetch_add(&i, 1, memory_order_seq_cst);
  // CHECK: atomicrmw sub i32* {{.*}} seq_cst
  __atomic_fetch_sub(&i, 1, memory_order_seq_cst);
  // CHECK: load atomic i32* {{.*}} seq_cst
  int r;
  __atomic_load(&i, &r, memory_order_seq_cst);
  // CHECK: store atomic i32 {{.*}} seq_cst
  r = 0;
  __atomic_store(&i, &r, memory_order_seq_cst);

  // CHECK: atomicrmw add i64* {{.*}} seq_cst
  __atomic_fetch_add(&l, 1, memory_order_seq_cst);
  // CHECK: atomicrmw sub i64* {{.*}} seq_cst
  __atomic_fetch_sub(&l, 1, memory_order_seq_cst);
  // CHECK: load atomic i64* {{.*}} seq_cst
  long long rl;
  __atomic_load(&l, &rl, memory_order_seq_cst);
  // CHECK: store atomic i64 {{.*}} seq_cst
  rl = 0;
  __atomic_store(&l, &rl, memory_order_seq_cst);
}
