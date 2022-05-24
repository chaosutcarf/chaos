#pragma once

#include "common/type.h"
#include "io/io_basic.h"

namespace chaos::io {
// https://stackoverflow.com/a/25389481/11927397
// template <class Matrix>
template <typename Derived>
inline bool dump_matrix_binary(const std::string& filename,
                               const Eigen::PlainObjectBase<Derived>& matrix) {
  return with_write_binary(filename, [&matrix](std::ostream& out) {
    using Index = typename Derived::Index;
    using Scalar = typename Derived::Scalar;
    constexpr auto sizeIndex = sizeof(Index);
    constexpr auto sizeScalar = sizeof(Scalar);

    Index rows = matrix.rows(), cols = matrix.cols();
    out.write(reinterpret_cast<char*>(&rows), sizeIndex);
    out.write(reinterpret_cast<char*>(&cols), sizeIndex);
    out.write(reinterpret_cast<const char*>(matrix.data()),
              rows * cols * sizeScalar);
  });
}

template <typename Derived>
inline bool read_matrix_binary(const std::string& filename,
                               Eigen::PlainObjectBase<Derived>& matrix) {
  return with_read_binary(filename, [&matrix](std::istream& in) {
    using Index = typename Derived::Index;
    using Scalar = typename Derived::Scalar;
    constexpr auto sizeIndex = sizeof(Index);
    constexpr auto sizeScalar = sizeof(Scalar);

    Index rows = 0, cols = 0;
    in.read(reinterpret_cast<char*>(&rows), sizeIndex);
    in.read(reinterpret_cast<char*>(&cols), sizeIndex);
    matrix.resize(rows, cols);
    in.read(reinterpret_cast<char*>(matrix.data()), rows * cols * sizeScalar);
  });
}

// https://scicomp.stackexchange.com/a/21438
template <class SparseMatrix>
inline bool dump_sparse_matrix_binary(const std::string& filename,
                                      const SparseMatrix& matrix) {
  CHAOS_ASSERT(matrix.isCompressed());
  return with_write_binary(filename, [&matrix](std::ostream& out) {
    using Index = typename SparseMatrix::Index;
    using StorageIndex = typename SparseMatrix::StorageIndex;
    using Scalar = typename SparseMatrix::Scalar;
    constexpr auto sizeIndex = sizeof(Index);
    constexpr auto sizeIndexS = sizeof(StorageIndex);
    constexpr auto sizeScalar = sizeof(Scalar);

    Index rows, cols, nnzs, outS, innS;
    rows = matrix.rows();
    cols = matrix.cols();
    nnzs = matrix.nonZeros();
    outS = matrix.outerSize();
    innS = matrix.innerSize();

    out.write(reinterpret_cast<char*>(&rows), sizeIndex);
    out.write(reinterpret_cast<char*>(&cols), sizeIndex);
    out.write(reinterpret_cast<char*>(&nnzs), sizeIndex);
    out.write(reinterpret_cast<char*>(&outS), sizeIndex);
    out.write(reinterpret_cast<char*>(&innS), sizeIndex);

    out.write(reinterpret_cast<const char*>(matrix.valuePtr()),
              sizeScalar * nnzs);
    out.write(reinterpret_cast<const char*>(matrix.outerIndexPtr()),
              sizeIndexS * outS);
    out.write(reinterpret_cast<const char*>(matrix.innerIndexPtr()),
              sizeIndexS * nnzs);
  });
}

template <class SparseMatrix>
inline bool read_sparse_matrix_binary(const std::string& filename,
                                      SparseMatrix& matrix) {
  return with_read_binary(filename, [&matrix](std::istream& in) {
    using Index = typename SparseMatrix::Index;
    using StorageIndex = typename SparseMatrix::StorageIndex;
    using Scalar = typename SparseMatrix::Scalar;
    constexpr auto sizeIndex = sizeof(Index);
    constexpr auto sizeIndexS = sizeof(StorageIndex);
    constexpr auto sizeScalar = sizeof(Scalar);

    Index rows, cols, nnz, inSz, outSz;
    in.read(reinterpret_cast<char*>(&rows), sizeIndex);
    in.read(reinterpret_cast<char*>(&cols), sizeIndex);
    in.read(reinterpret_cast<char*>(&nnz), sizeIndex);
    in.read(reinterpret_cast<char*>(&outSz), sizeIndex);
    in.read(reinterpret_cast<char*>(&inSz), sizeIndex);

    matrix.resize(rows, cols);
    matrix.makeCompressed();
    matrix.resizeNonZeros(nnz);

    in.read(reinterpret_cast<char*>(matrix.valuePtr()), sizeScalar * nnz);
    in.read(reinterpret_cast<char*>(matrix.outerIndexPtr()),
            sizeIndexS * outSz);
    in.read(reinterpret_cast<char*>(matrix.innerIndexPtr()), sizeIndexS * nnz);

    matrix.finalize();
  });
}

}  // namespace chaos::io
