/*Implement a vector (mutable array with automatic resizing):
 Practice coding using arrays and pointers, and pointer math to jump to an index instead of using indexing.
 new raw data array with allocated memory
can allocate int array under the hood, just not use its features
start with 16, or if starting number is greater, use power of 2 - 16, 32, 64, 128
 size() - number of items
 capacity() - number of items it can hold
 is_empty()
 at(index) - returns item at given index, blows up if index out of bounds
 push(item)
 insert(index, item) - inserts item at index, shifts that index's value and trailing elements to the right
 prepend(item) - can use insert above at index 0
 pop() - remove from end, return value
 delete(index) - delete item at index, shifting all trailing elements left
 remove(item) - looks for value and removes index holding it (even if in multiple places)
 find(item) - looks for value and returns first index with that value, -1 if not found
 resize(new_capacity) // private function
when you reach capacity, resize to double the size
when popping an item, if size is 1/4 of capacity, resize to half*/
#include <iostream>
using namespace std;
class Vector{
  public:
  	Vector();
  	Vector(int cap);
  	Vector(Vector& v);
  	~Vector();
  	int size_show();
  	int capacity_show();
  	bool is_empty();
  	int at(int index);
  	void insert(int index, int item);
  	int pop();
  	void del(int index);
  	void remove(int item);
  	int find(int item);
  private:
  	int size;
  	int capacity;
  	int* array;
  	void resize(int new_capacity);
};
Vector::Vector(){ //default constructor
  capacity = 2;
  size = 0;
  array = new int[capacity];
}
Vector::Vector(int cap){ //normal constructor
  capacity = cap;
  size = 0;
  array = new int[capacity];
}
Vector::Vector(Vector& v){ //copy constructor
  capacity = v.capacity;
  size = v.size;
  array = new int[capacity];
  for(int i = 0; i <= capacity-1; i++){
	array[i] = v.array[i];
  }
}
Vector::~Vector(){ //destructor
	delete [] array;
}
int Vector::size_show(){return size;}

int Vector::capacity_show(){return capacity;}

bool Vector::is_empty(){if(size == 0) return 1;}

int Vector::at(int index){return array[index];}

void Vector::insert(int index, int item){
  if(size == capacity){
  	resize(capacity*2);
  }
  int array1[size];
  for(int j=0; j <= size -1; j++){
  	array1[j] = array[j];
  }
  for(int i = index+ 1; i <= size; i++){
    array[i] = array1[i-1]; //the problem with putting the value array[3] = array[2] and then then array[4] = array[3] => array[4] = array[2] 
    //the code will end up copying all the values. 
  }
  array[index] = item;
  size++;
}
int Vector::pop(){
	int poped = array[size-1];
	size--;
	if(size < capacity/4){
	  resize(capacity/2);
	}
	return poped;
}
void Vector::del(int index){

	for(int i=index; i <= size-2 ; i++){
	  array[i] = array[i+1];
	}
	size--;
	if(size < capacity/4){
	  resize(capacity/2);
	}
}
void Vector::remove(int item){
	for(int i=0; i <= size-1; i++){
		if(array[i] == item)
			del(i);
	}
}
int Vector::find(int item){
	for(int i = 0 ; i <= size-1 ; i++){
	  if(array[i] == item)
	    return i; 
	}
}
void Vector::resize(int new_capacity){
  int* array_new;
  array_new = new int[new_capacity];
  for(int i=0 ; i <= size-1; i++){
  	array_new[i] = array[i];
  }
  array = array_new;
  capacity = new_capacity;
}
int main(){
  Vector V1;  //V1 = V3 = V4
  Vector V2(8);
  Vector V3(V1);
  Vector V4 = V3;
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  cout << V2.size_show() << ' ' << V2.capacity_show() << endl;
  cout << V3.size_show() << ' ' << V3.capacity_show() << endl;
  V1.insert(0,20);
  for(int i=0; i < V1.size_show(); i++){ cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;

  V1.insert(0,30);
  for(int i=0; i < V1.size_show(); i++){ cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;

  V1.insert(2,50);
  for(int i=0; i < V1.size_show(); i++){ cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  
  V1.insert(3,70);
  for(int i=0; i < V1.size_show(); i++){ cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  
  V1.insert(2,90);
  for(int i=0; i < V1.size_show(); i++){ cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  
  V1.del(1);
  for(int i=0; i < V1.size_show(); i++){ cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  
  V1.pop();
  for(int i=0; i < V1.size_show(); i++){cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  
  V1.del(0);
  for(int i = 0 ; i < V1.size_show(); i++) {cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;
  
  V1.pop();
  for(int i = 0 ; i < V1.size_show(); i++) {cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;

  V1.pop();
  for(int i = 0 ; i < V1.size_show(); i++) {cout << V1.at(i) << ' ';}
  cout << V1.size_show() << ' ' << V1.capacity_show() << endl;

  return 0;
}