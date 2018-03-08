/* @Author
* Name: Orçun Özdemir
* ID: 150140121
* Date: 25/12/2016
*/

#define _USE_MATH_DEFINES	// Mathematical constant macro for "e" = M_E
#include <iostream>			// Basic input/output functions.
#include <cstring>			// String operation functions such as strcmp, strcpy...
#include <cmath> 			// Mathematical functions such as pow, log, fmod...
#include <cstdlib> 			// Return EXIT_SUCCESS and other basic functions.
#include <fstream>			// File operation functions.
#include <climits>			// LONG_MAX and LONG_MIN values.
#define SIZE 100			// Size of input string.
#define FLAG "#"			// Required for prefix to postfix converter. It gives a warning after compiling but it is negligible.

using namespace std;

struct node{
	char data[SIZE];	// To store string values.
	long datac;			// To store long values for calculation.
	node *next;
};

struct stack{
	node *head;
	void create();
	void push(char []);
	void pushc(long);
	char* pop();
	long popc();
	char* top();
	long topc();
	void print();
	bool isEmpty();
	void prefixtopostfix(node *);		// Prefix to Postfix Converter Function
	long postfixcalculator(node *);		// Postfix Calculator Function
	bool isOperator(char *);
	void close();
};

struct queue{
	node *front;
	node *rear;
	void create();
	void enqueue(char []);
	void enqueuec(long);
	char* dequeue();
	void print();
	void printc();
	bool isEmpty();
	void close();
};

stack stack;	// Stack to convert prefix notations to postfix notations and calculate postfix notations.
queue prefix;	// Queue to store prefix value.
queue postfix;	// Queue to store converted postfix value.
queue answer;	// Queue to store answers.

void queue::create(){
	front = NULL;
	rear = NULL;
}

void queue::enqueue(char data[SIZE]){
	node *newnode = new node;
	strcpy(newnode->data, data);
	newnode->next = NULL;
	{
		if (rear == NULL){
			front = newnode;
		}
		else {
		rear->next = newnode;
	}
		
	rear = newnode;
	}
}

void queue::enqueuec(long datac){
	node *newnode = new node;
	newnode->datac = datac;
	newnode->next = NULL;
	{
		if (rear == NULL){
			front = newnode;
		}
		else {
		rear->next = newnode;
	}
		
	rear = newnode;
	}
}

char* queue::dequeue(){
	char *temp;
	temp = front->data;
	front = front->next;
	return temp;
}

void queue::print(){
	node *temp = front;
	while (temp){
	cout << temp->data << " ";
	temp = temp->next;
	}
}

void queue::printc(){
	int x = 0;
	node *temp = front;
	while (temp){
		if (x == 0){
	cout << temp->datac;
	temp = temp->next;
	x++;
	}
	else {
		cout << " -> " << temp->datac;
	temp = temp->next;
	}
	}	
}

bool queue::isEmpty(){
	if (front == NULL){
		return true;
	}
	
	else {
		return false;
	}
}

void queue::close(){
	node *temp = front;
	while (temp){
		front = front->next;
		delete temp;
		temp = temp->next;
	}
}

void stack::create(){
	head = NULL;
}

void stack::push(char *data){
	node *newnode = new node;
	strcpy(newnode->data, data);
	newnode->next = head;
	head = newnode;
}

void stack::pushc(long datac){
	node *newnode = new node;
	newnode->datac = datac;
	newnode->next = head;
	head = newnode;
}

char* stack::pop(){
	char *temp = head->data;
	head = head->next;
	return temp;
}

long stack::popc(){
	long temp = head->datac;
	head = head->next;
	return temp;
}

bool stack::isEmpty(){
	if (head == NULL){
		return true;
	}
	
	else {
		return false;
	}
}

char* stack::top(){
	return head->data;
}

long stack::topc(){
	return head->datac;
}

void stack::print(){
	node *temp = head;
	while (temp){
		cout << temp->data << " ";
		temp = temp->next;
	}
}

void stack::close(){
	node *temp = head;
	while (temp){
		head = head->next;
		delete temp;
		temp = head;
	}
}

void stack::prefixtopostfix(node *head_prefix){
	for (node *temp = head_prefix; temp; temp = temp->next){
		
		if (isOperator(temp->data)){
			push(temp->data);
		}
		
		else {
			if (!(strcmp(temp->data, "(") == 0) && !(strcmp(temp->data, ")") == 0)){
			postfix.enqueue(temp->data);
			}

			while (!isEmpty() && strcmp(top(), FLAG) == 0){
				pop();
				if (isEmpty()) {
					break;
				}
				if (!(strcmp(top(), "sum") == 0) && !(strcmp(top(), "product") == 0) && !(strcmp(top(), "min") == 0)
				&& !(strcmp(top(), "max") == 0) && !(strcmp(temp->data, "(") == 0) && !(strcmp(temp->data, ")") == 0)) {
				postfix.enqueue(pop());
				}
			}
			push(FLAG);
		}
	}
			while (!isEmpty()){

					if (strcmp(top(), FLAG) == 0){
						pop();
					}
					
					if (!isEmpty()){
					postfix.enqueue(pop());
				}
			} 
}

long stack::postfixcalculator(node *head_postfix){
	close();
	create();
	long temp, temp2, check;
	
	for (node *traverse = head_postfix; traverse; traverse = traverse->next){
		if (strcmp(traverse->data, "ans") == 0){
			pushc(answer.rear->datac);	
		}
		
		else if (strcmp(traverse->data, "inf") == 0){
			pushc(LONG_MAX);
		}
		
		else if (strcmp(traverse->data, "-inf") == 0){
			pushc(LONG_MIN);
		}
		
		else if (!isOperator(traverse->data)){
			pushc(atol(traverse->data));
		}
		
		else {
			if (strcmp(traverse->data, "sum") == 0){
				pushc(popc() + popc());
				check = popc();
				while (!isEmpty()){
					pushc(check + popc());
					check = popc();
				}
				pushc(check);
			}
			
			else if (strcmp(traverse->data, "sub") == 0){
				temp = popc();
				if (isEmpty()){
					pushc(temp);
				}
				else {
					temp2 = popc();
					pushc(temp2 - temp);
				}
			}
			
			else if (strcmp(traverse->data, "product") == 0){
				pushc(popc() * popc());
				check = popc();
				while (!isEmpty()){
					pushc(check * popc());
					check = popc();
				}
				pushc(check);
			}
			
			else if (strcmp(traverse->data, "min") == 0){
				pushc(min(popc(), popc()));
				check = popc();
				while (!isEmpty()){
					pushc(min(popc(), check));
					check = popc();
				}
				pushc(check);
			}
			
			else if (strcmp(traverse->data, "max") == 0){
				pushc(max(popc(), popc()));
				check = popc();
				while (!isEmpty()){
					pushc(max(popc(), check));
					check = popc();
				}
				pushc(check);
			}
				
			else if (strcmp(traverse->data, "div") == 0){
				temp = popc();
				if (temp == 0){
					cout << "Syntax error. (Dividing by zero is invalid!)";		// Division by zero error!
					break;
				}
				if (isEmpty()){
					pushc(temp / 1);
				}
				else {
					temp2 = popc();
					pushc(temp2 / temp);
				}
			}
			
			else if (strcmp(traverse->data, "exp") == 0){
				check = popc();
				if (isEmpty()){
					pushc(pow(M_E, check));
				}
				else {
					pushc(pow(popc(), check));
					}	
				}
				
			else if (strcmp(traverse->data, "mod") == 0){
				check = popc();
				if (isEmpty()){
					pushc(fmod(check, 10));
				}
				else {
					pushc(fmod(check, popc()));
					}	
				}
				
			else if (strcmp(traverse->data, "log") == 0){
				check = popc();
				if (isEmpty()){
					pushc(log(check));
				}
				else {
					pushc(log(check) / log(popc()));
					}	
				}
		
			else if (strcmp(traverse->data, "abs") == 0){
			pushc(abs(popc()));
			}
		
			else if (strcmp(traverse->data, "sqrt") == 0){
			pushc(sqrt(popc()));
		}
	}
}
	answer.enqueuec(topc());
	return topc();
}

bool stack::isOperator(char *temp){
	if (strcmp(temp, "sum") == 0 || strcmp(temp, "div") == 0 || strcmp(temp, "sub") == 0 || strcmp(temp, "exp") == 0 || strcmp(temp, "product") == 0 ||
	strcmp(temp, "abs") == 0 || strcmp(temp, "sqrt") == 0 || strcmp(temp, "min") == 0 || strcmp(temp, "max") == 0 || strcmp(temp, "log") == 0 || strcmp(temp, "mod") == 0){
		return true;
	}
	
	else {
		return false;
	}
}

void splitandwritetoprefix(char *array){		// Function to split input into string and write them in prefix queue.
	char *splitter = strtok(array, " ");
  	do
  	{
    	prefix.enqueue(splitter);
    	splitter = strtok(NULL, " ");
  	} while (splitter != NULL); 
}

int main(int argc, char* argv[]){			// Arguments to determine whether program to run in read mode or interpreter mode.
	
	if (argc < 2) {
	cout << "Initializing the interpreter...\n\n";
	answer.create();
  	
  	while (true){
  		stack.create();
  		prefix.create();
 	 	postfix.create();

		char array[SIZE];
		cin.getline(array, SIZE, '\n');
		
		  	if (strcmp(array, "exit") == 0){
		  		cout << endl;
				break;
			}
	
		splitandwritetoprefix(array);
		
			if(!stack.isOperator(prefix.front->data)){		// Prefix notations have to start with operators if not throw a syntax error on the screen.
				cout << "\nSyntax error.\n\n";
				continue;
			}
	
		stack.prefixtopostfix(prefix.front);
	
		cout << "\nPostfix string: "; 
		postfix.print();
		cout << endl;
	
		cout << "Answer: " << stack.postfixcalculator(postfix.front) << endl << endl;
	
		stack.close();
		prefix.close();
		postfix.close();
	}
	
	cout << "Terminating the interpreter...\n";
	cout << "Answer queue: ";
	answer.printc();
	cout << endl;
	system("pause");
	}
	
	else if (argc == 2){
		ifstream input;
		input.open("input.txt");
		
			if (input.fail()) {
				cout << "File couldn't be opened.\n";
				}
				
		while (!(input.eof())) {
			char inputarray [SIZE];
			input.getline(inputarray, 50, '\n');
			stack.create();
  			prefix.create();
 	 		postfix.create();
			splitandwritetoprefix(inputarray);
			stack.prefixtopostfix(prefix.front);
			stack.postfixcalculator(postfix.front);
			stack.close();
			prefix.close();
			postfix.close();
			}
			
			cout << "Answer queue: ";
			answer.printc();
			cout << endl;
			
			system("pause");
			
	input.close();
}
  	
	return EXIT_SUCCESS;
}
