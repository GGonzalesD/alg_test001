#ifndef __MMREADER_HPP__
#define __MMREADER_HPP__

#include "mvector.hpp"
#include "mmatrix.hpp"
#include <vector>
#include <string.h>

#define XD_NEW_VECTOR "new_vector"
#define XD_SHOW_VECTOR "show_vector"

#define XD_NEW_MATRIX "new_matrix"

#define XD_SAVE_LAST "save_last"

#define XD_ADD_VECTOR "add_vectors"

#define XD_NOTHING ""

class Box{
public:
	Box(const char * name_, void * value){
		name = nullptr;
		set_name(name_);
		set_info(value);
	}
	~Box(){
		if(name)
			delete name;
	}
	char * get_name(){
		return name;
	}
	void set_name(const char * name_){
		if(name)
			delete name;
		size_t len = strlen(name_)+1;
		name = new char[len];
		for(int i=0; i<len; i++)
			name[i] = name_[i];
	}
	void* get_info(){
		return info;
	}
	void set_info(void * value){
		info = value;
	}

	void show(const char * text_start = "", const char * text_end = "\n"){
		printf("%s(\"%s\":%p)%s", text_start, name, info, text_end);
	}

private:
	char * name;
	void * info;
};



std::vector<Box*> variables;
void* last_point = nullptr;
bool show_info = true;


void * get_from_variables(const char * key){
	for(size_t i=0; i<variables.size(); i++){
		if(strcmp(key, variables[i]->get_name()) == 0)
			return variables[i]->get_info();
	}
	return nullptr;
}

bool xd_execute(const char * command, const char * param1, const char * param2){
	//printf("CMD: %s \"%s\" \"%s\"\n", command, param1, param2);

	if(strcmp(command, XD_SHOW_VECTOR) == 0){
		Vector* vect = (Vector*)get_from_variables(param1);
		if(vect){
			printf("[I]: SHOW \"%s\": ", param1);
			vect->show();
		}else{
			printf("[E]: NO SE PUEDE OBTENER \"%s\"\n", param1);
		}
		
	}

	if(strcmp(command, XD_NEW_VECTOR) == 0){
		// Para crear un vector a partir de una asignacion simple: cmd [name] "x y z w ..."
		Vector* vect = Vector::from_string(param2);
		Box* box = new Box(param1, vect);
		variables.push_back(box);
		
		printf("[I]: Se ha agregador Vector(\"%s\"): ", param1);
		vect->show("", " ");
		printf("como ");
		box->show();
	}
	if(strcmp(command, XD_SAVE_LAST) == 0){
		if(last_point){
			Box* box = new Box(param1, last_point);
			variables.push_back(box);
			printf("[I]: Se ha guardado LAST como ");
			box->show();

		}else{
			printf("[E]: LAST NO TIENE VALOR\n");
		}
	}

	if(strcmp(command, XD_NEW_MATRIX) == 0){
		Matrix* matr = Matrix::from_string(param2);
		Box* box = new Box(param1, matr);
		variables.push_back(box);
		
		printf("[I]: Se ha agregador Matriz: (%d, %d) ", matr->get_f(), matr->get_f());
		printf("como ");
		box->show();
	}

	if(strcmp(command, XD_ADD_VECTOR) == 0){

		Vector* vect_a = (Vector*)get_from_variables(param1);
		Vector* vect_b = (Vector*)get_from_variables(param2);

		if(vect_a && vect_b){
			Vector* vlast = vect_a->copy();


			vlast->add(vect_b);
			printf("[I]: La suma de \"%s\" y \"%s\"es ", param1, param2);
			vlast->show();
			last_point = vlast;
		}else{
			printf("[E]: NO SE PUEDE OBTENER ");
			if(vect_a && !vect_b)
				printf("\"%s\"\n", param2);
			else if(vect_b && !vect_a)
				printf("\"%s\"\n", param1);
			else
				printf("\"%s\" y \"%s\"\n", param1, param2);
		}

	}

	return true;
}	


#endif