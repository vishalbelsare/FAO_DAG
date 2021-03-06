#ifndef GSL_VECTOR_H_
#define GSL_VECTOR_H_

#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstring>

// Gnu Scientific Library
namespace gsl {

// Vector Class
template <typename T>
struct vector {
  size_t size, stride;
  T* data;
};

template <typename T>
vector<T> vector_alloc(size_t n) {
  vector<T> vec;
  vec.size = n;
  vec.stride = 1;
  vec.data = new T[n];
  assert(vec.data != 0);
  return vec;
}

template <typename T>
vector<T> vector_calloc(size_t n) {
  vector<T> vec = vector_alloc<T>(n);
  memset(vec.data, 0, n * sizeof(T));
  return vec;
}

template<typename T>
void vector_free(vector<T> *x) {
  if (x->data)
    delete [] x->data;
}

template<typename T>
inline void vector_set(vector<T> *v, size_t i, T x) {
  v->data[i * v->stride] = x;
}

template<typename T>
inline T vector_get(const vector<T> *v, size_t i) {
  return v->data[i * v->stride];
}

template<typename T>
void vector_set_all(vector<T> *v, T x) {
  for (unsigned int i = 0; i < v->size; ++i)
    vector_set(v, i, x);
}

template <typename T>
bool vector_any_isnan(vector<T> *v) {
  for (unsigned int i = 0; i < v->size; ++i) {
    if (isnan(vector_get(v, i))) {
      return true;
    }
  }
  return false;
}

template <typename T>
vector<T> vector_subvector(vector<T> *vec, size_t offset, size_t n) {
  vector<T> subvec;
  subvec.size = n;
  subvec.data = vec->data + offset * vec->stride;
  subvec.stride = vec->stride;
  return subvec;
}

template <typename T>
vector<T> vector_view_array(T *base, size_t n) {
  vector<T> vec;
  vec.size = n;
  vec.data = base;
  vec.stride = 1;
  return vec;
}

// TODO: Find a better way to deal with the const issue.
template <typename T>
const vector<T> vector_view_array(const T *base, size_t n) {
  vector<T> vec;
  vec.size = n;
  vec.data = const_cast<T*>(base);
  vec.stride = 1;
  return vec;
}

/* Copy len elements from the dst_vec to src_vec at the given offsets. */
template <typename T>
void vector_subvec_memcpy(vector<T>* dest_vec, size_t dest_offset,
                          const vector<T>* src_vec, size_t src_offset,
                          size_t len) {
    if (dest_vec->stride == 1 && src_vec->stride == 1) {
      memcpy(dest_vec->data + dest_offset,
             src_vec->data + src_offset, len * sizeof(T));
    } else {
      for (unsigned int i = 0; i < len; ++i)
        vector_set(dest_vec, i + dest_offset,
          vector_get(src_vec, src_offset));
    }
}

template <typename T>
void vector_memcpy(vector<T> *x, const vector<T> *y) {
  if (x->stride == 1 && y->stride == 1) {
    memcpy(x->data, y->data, x->size * sizeof(T));
  } else {
    for (unsigned int i = 0; i < x->size; ++i)
      vector_set(x, i, vector_get(y, i));
  }
}

template <typename T>
void vector_memcpy(vector<T> *x, const T *y) {
  if (x->stride == 1) {
    memcpy(x->data, y, x->size * sizeof(T));
  } else {
    for (unsigned int i = 0; i < x->size; ++i)
      vector_set(x, i, y[i]);
  }
}

template <typename T>
void vector_memcpy(T *x, const vector<T> *y) {
  if (y->stride == 1) {
    memcpy(x, y->data, y->size * sizeof(T));
  } else {
    for (unsigned int i = 0; i < y->size; ++i)
      x[i] = vector_get(y, i);
  }
}

template <typename T>
void vector_print(const vector<T> *x) {
  for (unsigned int i = 0; i < x->size; ++i)
    printf("%e ", vector_get(x, i));
  printf("\n");
}

template <typename T>
void vector_scale(vector<T> *a, T x) {
  for (unsigned int i = 0; i < a->size; ++i)
    a->data[i * a->stride] *= x;
}

template <typename T>
void vector_add(vector<T> *a, const vector<T> *b) {
  for (unsigned int i = 0; i < a->size; i++)
    a->data[i * a->stride] += b->data[i * b->stride];
}

template <typename T>
void vector_sub(vector<T> *a, const vector<T> *b) {
  for (unsigned int i = 0; i < a->size; i++)
    a->data[i * a->stride] -= b->data[i * b->stride];
}

template <typename T>
void vector_mul(vector<T> *a, const vector<T> *b) {
  for (unsigned int i = 0; i < a->size; i++)
    a->data[i * a->stride] *= b->data[i * b->stride];
}

template <typename T>
void vector_div(vector<T> *a, const vector<T> *b) {
  for (unsigned int i = 0; i < a->size; i++)
    a->data[i * a->stride] /= b->data[i * b->stride];
}

template <typename T>
void vector_add_constant(vector<T> *a, const T x) {
  for (unsigned int i = 0; i < a->size; i++)
    a->data[i * a->stride] += x;
}

}  // namespace gsl

#endif  // GSL_VECTOR_H_

