#ifndef __MVECTOR_HPP__
#define __MVECTOR_HPP__

#include <stack>
#include <iostream>
#include <stdio.h>

class Vector{
public:
	Vector(size_t t, double value=0.0){
		// Crea el Vector
		// 		t: longitud
		//		value: valor inicial del vector 
		
		size = t;
		if(t == 0){
			arr = nullptr;
		}else{
			arr = new double[size];
			for(int i=0; i<size; i++)
				arr[i] = value;
		}
	}

	~Vector(){
		// Libera la memoria
		if(arr)
			delete arr;
	}

	Vector* copy(){
		// Copia este vector
		Vector* vc = new Vector(size);
		for(int i=0; i<size; i++)
			vc->set_value(i, arr[i]);
		return vc;
	}

	// ----- MSG ERROR INFO -----

	void show(const char * text_before = "", const char * text_end = "\n"){
		// Muestra el vector
		//		text_before: nombre del vector
		//		text_end: sufijo del texto

		printf("%s[", text_before);
		for(int i=0; i<size; i++){
			printf("%g", arr[i]);
			if(i != size-1)
				printf(" ");
		}
		printf("]%s", text_end);
	}

	// ----- OPERATIONS -----

	void add_value(double v){
		// Agrega un valor al vector
		// v: valor
		// [1 2 3]+9 => [1 2 3 9]

		if(arr){
			double* arrx = new double[size+1];
			for(int i=0; i<size; i++)
				arrx[i] = arr[i];
			arrx[size] = v;
			delete arr;
			arr = arrx;
			size++;
		}else{
			arr = new double[1];
			arr[0] = v;
			size = 1;
		}
	}

	bool is_null(){
		// Comprueba si un vector es nulo
		// [0 1 2] => False
		// [0 0 0] => True

		for(int i=0; i<size; i++){
			if(at(i) != 0)
				return false;
		}
		return true;
	}

	bool same_size(Vector* other){
		// Compara los tamaños de dos vectores
		// [2 1], [3 1 2] => False
		// [1 2 3], [1 2 4] => True

		return size == other->get_size();
	}

	double plus(){
		// Suma todos los valores de un vector
		// [2 1 2] => 5
		// [1 -2] => -1

		double v = 0;
		for(int i=0; i<size; i++)
			v += arr[i];
		return v;
	}

	Vector* add(Vector* other){
		// Suma un vector y devuelve el mismo vector
		// [3 1 2] + [1 2 -1] => [4 3 1]
		// [3 2] + [3 2 1] => nullptr

		if(same_size(other)){
			for(int i=0; i<size; i++)
				at(i) += other->at(i);
			return this;
		}else{
			printf(" :: ERROR :: ");
			show("\"", "\"");
			printf(" y ");
			other->show("\"", "\"");
			printf(" NO SE PUEDEN SUMAR\n");
			
			return nullptr;
		}
	}

	Vector* scale(double s){
		// Multiplica un vector por un escalar
		// [2 1 0.5] * 6 = [12 6 3]

		for(int i=0; i<size; i++)
			arr[i] *= s;
		return this;
	}

	Vector* mul(Vector* other){
		// Multiplica los valores de dos vectores
		// [2 1 2] [1 0 1] => [2 0 2]
		// [2 1] [3 1 2] => nullptr

		if(same_size(other)){
			for(int i=0; i<size; i++)
				at(i) *= other->at(i);
			return this;
		}else{
			printf(" :: ERROR :: ");
			show("\"", "\"");
			printf(" y ");
			other->show("\"", "\"");
			printf(" NO SE PUEDEN MULTIPLICAR\n");
			
			return nullptr;
		}
	}

	Vector* load(Vector* other){
		// Copia a otro vector
		// [2 3], [3 1 2 2] => [3 1 2 2]

		if(arr)
			delete arr;
		size = other->get_size();
		arr = new double[size];
		for(int i=0; i<size; i++)
			arr[i] = other->at(i);
		return this;
	}

	Vector* load_values(Vector* other){
		// Copia los valores de un vector
		// [2 3] [3 1] => [3 1]
		// [2 1 2] [3 1] => nullptr

		if(same_size(other)){
			for(int i=0; i<size; i++)
				arr[i] = other->at(i);
			return this;
		}else{
			printf(" :: ERROR :: ");
			show("\"", "\"");
			printf(" NO PUEDE CARGAR LOS VALORES DE ");
			other->show("\"", "\"\n");
			return nullptr;
		}
	}

	int unique(){
		// Retorna el valor indice del valor que es el unico no cero
		// [0 0 6 0 0] => 2
		// [0 0 0 0 0] => -1
		// [0 1 2 1 2] => -1

		int count = 1;
		int index = -1;
		for(int i=0; i<get_size(); i++)
			if ( at(i) != 0){
				count--;
				index = i;
			}
				
		return count==0?index:-1;
	}

	std::stack<int>* uniques(){
		// [CREO QUE VOY A BORRAR ESTO]
		std::stack<int>* stack_x = new std::stack<int>;
		for(int i=0; i<get_size(); i++)
			if ( at(i) != 0)
				stack_x->push(i);
		return stack_x;
	}

	// ----- SETTERS -------

	void set_value(size_t index, double value){
		// Fija el valor en un indice
		// [2 3 1 2].set_value(1, -1) => [2 -1 1 2]
		// [2 3 1 2].set_value(2, -1) => [2 3 -1 2]

		arr[index] = value;
	}

	// ---- GETTERS ---------

	size_t get_size(){
		// Obtiene el tamaño del vector
		// [2 3] => 2
		// [1 1 2] => 3
		return size;
	}

	double& at(size_t index){
		// Obtiene el valor de un indice
		// [3 0 2 1].at(1) = 0
		// [2 1 5 3].at(2) = 5
		return arr[index];
	}

	// ---- STATICS -------

	static Vector* from_scratch(){
		// Vector Vacio
		// Vector::from_scratch() => []
		return new Vector(0);
	}

	static Vector* from_xy(double x, double y){
		// Vector de 2
		// Vector::from_xy(1, 2) => [1 2]
		Vector* vect = new Vector(2);
		vect->at(0) = x;
		vect->at(1) = y;
		return vect;
	}

	static Vector* from_xyz(double x, double y, double z){
		// Vector de 3
		// Vector::from_xyz(1, 2, -2) => [1 2 -2]
		Vector* vect = new Vector(2);
		vect->at(0) = x;
		vect->at(1) = y;
		vect->at(2) = z;
		return vect;
	}

	static Vector* from_string(const char* text){
		// Vector de un texto
		// Vector::from_string("3 1 2") => [3 1 2]
		
		char tmp[100];
		size_t start = 0;
		size_t end = 0;

		bool last_space = true;

		size_t count = 0;
		std::stack<double> stack_;

		while(true){
			if(text[end] == '\n' || text[end] == ' ' || !text[end]){
				if(!last_space){
					last_space = true;
					for(size_t i=0; i<end-start; i++)
						tmp[i] = text[start+i];
					tmp[end-start] = '\0';
					start = end;

					stack_.push(atof(tmp));
					count++;
				}
			}else{
				last_space = false;
			}
			if(!text[end])
				break;
			end++;
		}

		Vector* vector = new Vector(count);
		while(!stack_.empty()){
			vector->at(--count) = stack_.top();
			stack_.pop();
		}

		return vector;
	}

protected:

	double* arr;
	size_t size;
};

#endif