@0x86178a99b0959d77;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("capnproto_benchmark");

struct DoubleArray {
  elems @0 :List(Float64);
}

struct SparseMatrix {
  rows @0 :List(SparseMatrixRow);

  struct SparseMatrixRow {
    cols @0 :List(UInt64);
    values @1 :List(Float64);
  }
}
