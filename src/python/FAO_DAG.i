//    This file is part of CVXcanon.
//
//    CVXcanon is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    CVXcanon is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with CVXcanon.  If not, see <http://www.gnu.org/licenses/>.

%module FAO_DAG
%{
	#define SWIG_FILE_WITH_INIT
	#include "FAO_DAG.hpp"
%}

%include "numpy.i"
%include "std_vector.i"
%include "std_map.i"

/* Must call this before using NUMPY-C API */
%init %{
	import_array();
%}

/* Typemap for the addDenseData C++ routine in LinOp.hpp */
%apply (double* IN_ARRAY2, int DIM1, int DIM2) {(double* data, int rows, int cols)};


/* Typemap for the addSparseData C++ routine in LinOp.hpp */
%apply (double* INPLACE_ARRAY1, int DIM1) {(double *data, int data_len)}

%apply (int* INPLACE_ARRAY1, int DIM1) {(int *indices, int idx_len), (int *ptrs, int ptr_len)};
%include "FAO.hpp"

/* Useful wrappers for the FAO class */
namespace std {
   %template(IntVector) vector<int>;
   %template(SizetVector) vector<size_t>;
   %template(SizetVector2D) vector< vector<size_t> >;
   %template(DoubleVector) vector<double>;
   %template(IntVector2D) vector< vector<int> >;
   %template(DoubleVector2D) vector< vector<double> >;
   %template(FaoVector) vector<FAO*>;
   %template(IntIntMap) map<int, int>;
   %template(ConeConstraint) pair<int, vector<int> >;
   %template(ConeConstraintVector) vector< pair<int, vector<int> > >;
}

/* For FAO_DAG.hpp. */
%apply (double* INPLACE_ARRAY1, int DIM1) {(double* input, int input_len)}

%apply (double* INPLACE_ARRAY1, int DIM1) {(double* output, int output_len)}
%include "FAO_DAG.hpp"
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 