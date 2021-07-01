#ifndef __MMATRIX_HPP__
#define __MMATRIX_HPP__

#include "mvector.hpp"

class Matrix{
public:

	Matrix(size_t f_, size_t c_){
		// Crear la matriz 
		// f_: filas
		// c_: columnas
		f = f_;
		c = c_;

		if(f != 0){
			rmatrix = new Vector*[f_];
			for(int i=0; i<f; i++)
				rmatrix[i] = new Vector(c);
		}else{
			f = 0;
			rmatrix = nullptr;
		}
	}

	~Matrix(){
		// Liberar la memoria
		if(rmatrix)
		for(int i=0; i<f; i++)
			delete rmatrix[i];
		delete []rmatrix;
	}

	Matrix* copy(){
		// Copia la matriz
		
		// |2 1 2|    |2 1 2|
		// |4 2 1| => |4 2 1|
		// |1 0 4|    |1 0 4|

		Matrix* matrix = Matrix::from_scratch();
		for(int i=0; i<f; i++)
			matrix->add_vector( rmatrix[i] );
		return matrix;
	}

	Matrix* no(size_t t){
		// Copia la matriz sin un vector

		// matrix.no(1) ...

		// |2 1 2|    |2 1 2|
		// |4 2 1| => |1 0 4|
		// |1 0 4|    

		Matrix* matrix = Matrix::from_scratch();
		for(int i=0; i<f; i++)
			if(i!=t)
				matrix->add_vector(get(i));
		return matrix;
	}

	void load(Matrix* matrix){
		// Copia exactamente a otra matriz

		if(rmatrix)
			delete rmatrix;
		rmatrix = nullptr;
		c = f = 0;
		for(int i=0; i<matrix->get_f(); i++){
			add_vector(matrix->get(i));
		}
	}

	// ----- MSG ERROR - ETC ------
	void show(const char * text_before = "", const char * text_end = "\n"){
		// Muestra la matriz

		printf("%s(%ld, %ld)\n", text_before, f, c);
		for(int i=0; i<f; i++){
			rmatrix[i]->show("..");
		}
	}

	// ----- OPERATORS -----------

	Vector* transform(Vector* vect){
		// Evalua un Vector en la matriz

		if(c == vect->get_size()){
			Vector* res = new Vector(f);

			for(int i=0; i<f; i++){
				Vector* r = rmatrix[i]->copy();
				r->mul(vect);
				res->at(i) = r->plus();
				delete r;
			}

			return res;
		}else{
			printf(" :: ERROR :: ");
			show("\"", "\"");
			printf(" no aplica para una matriz de [%d %d]\n", f, c);
			return nullptr;
		}
	}

	Matrix* transposed(){
		// Obtener la transpuesta

		Matrix* matrix = Matrix::from_scratch();
		for(int i=0; i<c; i++){
			Vector* vect = new Vector(f);
			for(int j=0; j<f; j++){
				vect->at(j) = rmatrix[j]->at(i);
			}
			matrix->add_vector(vect, false);
		}
		return matrix;
	}

	void set_transposed(){
		// Fijar la matriz a la transpuesta
		Matrix* x = transposed();
		load(x);
		delete x;
	}

	void add_vector(Vector* vector, bool copy=true){
		if(copy)
			vector = vector->copy();
		if(rmatrix){
			Vector** matrix_ = new Vector*[f+1];
			for(int i=0; i<f; i++)
				matrix_[i] = rmatrix[i];
			matrix_[f] = vector;
			delete rmatrix;
			rmatrix = matrix_;
			f++;
		}else{
			rmatrix = new Vector*[1];
			rmatrix[0] = vector;
			c = vector->get_size();
			f = 1;
		}
	}
	// Agrega un vector a la matriz
	// vector: Vector a agregar
	// copy: si se copia el vector, o se agrega directamente
	
	// matrix.add_vector(Vector::from_xyz(1, 0, 4))

	// |2 1 2|              |2 1 2|
	// |4 2 1| + |1 0 4| => |4 2 1|
	//                      |1 0 4|


	Vector* resolvex(){
		// [AUN NO SE TERMINA]
		Matrix* x =transposed();

		Vector* values = new Vector(x->get_f()-1);
		Matrix* Ms = x->no(x->get_f()-1);


		x->show("x: ");
		for(size_t i=0; i<x->get_f()-1; i++){

			Matrix* Mi = x->no(i);

			Mi->show("MX: ");

			delete Mi;

		}

		return nullptr;
	}

	Matrix* resolve(){
		// [AUN NO SE TERMINA]
		Matrix* c =copy();
		int rps = 1;

		while(rps){
			rps = 0;
			for(int i=c->get_f()-1; i>=0; i--){
				Vector* xvect = c->get(i);
				int id = xvect->unique();
				if(id != -1){
					rps += 1;
					for(int j=0; j<c->get_f(); j++)
						c->get(j)->at(id) = 0;
				}
					
			}
		}


		// Filtrar
		Matrix* matrix_out = Matrix::from_scratch();
		for(int i=0; i<c->get_f(); i++){
			Vector* tmp_vect = c->get(i);
			if(!tmp_vect->is_null())
				matrix_out->add_vector(tmp_vect);
		}
		delete c;
		return matrix_out;
	}

	Matrix* _kernel(){
		// Despejar Variables #1
		Matrix* ker = copy();
		bool repet = true;
		while(repet){
			repet = false;
			for(int i=0; i<ker->get_f(); i++){
				int index = ker->get(i)->unique();
				if(index != -1){
					repet = true;
					for(int j=0; j<ker->get_f(); j++)
						ker->get(j)->at(index) = 0;
				}
			}
		}
		Matrix* kernel_ = Matrix::from_scratch();
		for(int i=0; i<ker->get_f(); i++)
			if(!ker->get(i)->is_null())
				kernel_->add_vector(ker->get(i));
		delete ker;
		if(kernel_->get_f() <= 1)
			return kernel_;

		// Despejar Variables #2
		//Matrix* t = kernel_->transposed();
		//Vector* vect = new Vector(t->get_f());
		
		// ------ ------- --------- ------------ -------
		//for(int i=0; i<t->get_f(); i++){ // Select Mayor
		//	for(int j=0; j<t->get_c(); j++){
		//		if(t->get(i)->at(j) != 0)
		//			vect->at(i) += 1;
		//	}
		//}

		return kernel_;
	}

	Matrix* kernel(){
		// Obtiene las ecuaciones del kernel
		Matrix* ker_ = _kernel();
		Matrix* ker = ker_->triangul();
		ker->show("Ttriang");

		return ker->_kernel();
	}

	Matrix* triangul(){
		// Trianguliza la matriz por el metodo de GAUSS
		Matrix* matrix = copy();
		for(int i=0; i<int(f)-1; i++){
			int mi = i>c-1?c-1:i;
			for(int j=i+1; j<f; j++){

				Vector* vi = matrix->get(i)->copy();
				Vector* vj = matrix->get(j);

				if(vj->at(mi) != 0){
					double vvi = vi->at(mi);
					double vvj = vj->at(mi);

					vj->scale(vvi);
					vi->scale(-vvj);
					vj->add(vi);
				}
				delete vi;
			}
		}
		return matrix;
	}

	// ------- GETTERS ---------

	Vector* get(size_t index){
		// Obtiene un vector de un indice
		return rmatrix[index];
	}

	size_t get_f(){
		// Obtine las filas
		return f;
	}
	size_t get_c(){
		// Obtiene las columnas
		return c;
	}
	
	//  --- - - -STATICS - - -- - - -
	static Matrix* from_scratch(){
		// Matriz vacia
		// | - |
		return new Matrix(0, 0);
	}

	static Matrix* from_vector(Vector* vector, bool copy=true){
		// Matriz a partir de un vector
		// [2 1 2] = |2 1 2|
		Matrix* matrix = new Matrix(0, 0);
		matrix->add_vector(vector, copy);
		return matrix;
	}

	static Matrix* from_string(const char* string){
		// Matriz a partir de un texto(string)
		
		// Matrix::from_string("2 1 3,3 2 9,1 1 0")

		// |2 1 3|
		// |3 2 9|
		// |1 1 0|


		char tmp[100];
		size_t start = 0;
		size_t end = 0;
		bool tr = true;

		Matrix* matrix = Matrix::from_scratch();

		while(true){
			if(string[end] == '\n' || string[end] == ',' || string[end] == '/' || string[end] == '\0'){
				for(size_t i=0; i<end-start; i++)
					tmp[i] = string[start+i];
				tmp[end-start] = '\0';

				Vector* vect = Vector::from_string(tmp);
				start = end;

				if(matrix->get_f()==0 || matrix->c == vect->get_size()){
					matrix->add_vector(vect, false);
					start++;
				}
				else{
					delete vect;
					break;
				}
			}

			if(!string[end])
				break;
			end++;
		}

		return matrix;
	}

protected:

	Vector** rmatrix;
	size_t f, c;
};

#endif