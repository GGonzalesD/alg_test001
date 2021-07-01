#include <iostream>
#include "mvector.hpp"
#include "mmatrix.hpp"
//#include "mmreader.hpp"



int main(){

	//Matrix* matrix = Matrix::from_string("-2 0 3,-3 5 -8,-5 -3 -3");
	//Matrix* matrix = Matrix::from_string("1 1 0,0 1 -1,1 0 1"); // 2 ec
	//Matrix* matrix = Matrix::from_string("1 -2 1,1 1 1,2 2 2"); // 1 ec
	//Matrix* matrix = Matrix::from_string("1 1 2, 0 1 2, -1 1 -1"); // No Kernel

	//Matrix* matrix = Matrix::from_string("1 -1 0,0 0 1,0 1 -1");
	//Matrix* matrix = Matrix::from_string("1 1 0,0 1 -1,1 0 1");
	//Matrix* matrix = Matrix::from_string("1 2 3,3 2 2");
	//Matrix* matrix = Matrix::from_string("1 -2 -1,-1 2 1,2 -3 -1");
	//Matrix* matrix = Matrix::from_string("1 1 0 0,0 1 -1 0,1 0 1 0");
	Matrix* matrix = Matrix::from_string("1 2 1 -1,0 -1 0 1,1 3 2 2");

	matrix->show("ORIGINAL: ");

	Matrix* imagen = matrix->transposed();
	Matrix* triang = matrix->kernel();

	triang->show("KERNEL: ");
	imagen->show("IMAGEN: ");


	
	/*
	xd_execute(XD_NEW_VECTOR, "vector_a", "2 4 1 3");
	xd_execute(XD_NEW_MATRIX, "lol", "3 1 2/2 1 2");

	xd_execute(XD_NEW_VECTOR, "a", "2 3 1");
	xd_execute(XD_NEW_VECTOR, "b", "4 1 2");

	xd_execute(XD_ADD_VECTOR, "a", "b");
	xd_execute(XD_SAVE_LAST, "c", XD_NOTHING);
	
	xd_execute(XD_ADD_VECTOR, "a", "c");
	xd_execute(XD_SAVE_LAST, "d", XD_NOTHING);

	xd_execute(XD_ADD_VECTOR, "b", "d");
	xd_execute(XD_SAVE_LAST, "gg", XD_NOTHING);

	xd_execute(XD_SHOW_VECTOR, "gg", XD_NOTHING);
	*/

}