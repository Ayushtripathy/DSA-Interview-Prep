// Overview of Classes and Objects
class Person {//Person is class
    private://access specifier
    string name;
    int id;//data members
    int age;
    char* alias;
    static bool alive;//Belongs to class

    //Constructor overloading(Const. is called depending upon the args passed)
    Person(){//Custom Constructor
        count<<"Constructor called"<<endl;
        alias = new char[10];//Dynamically allocating in heap
    }

    Person(int age){//Parametrized Constructor
      //this points to the current object
      //Put the incoming age from constructor into the object's age
      this->age = age;
    }

    Person(Person &newGuy){//My custom copy constructor
       char* ch = new char[strlen(newGuy.alias) + 1];
       strcpy(ch,newGuy.alias);
       this->alias = ch;
       this->age = newGuy.age;//Put curr obj age into newGuy's age
    }

    public:
    void printAge();//member function declared outside the class

    void setDetails(string naam,int umra,int rollNo){
        name = naam;
        age = umra;
        id = rollNo;
    }

    void getDetails(){//member function declared inside the class
      cout<<"Name"<<name<<"Age"<<age<<"Roll No."<<id<<endl;
    }

    void setAlias(char alias[]){
        this->alias = alias;
    }

    static bool status(){//Static fn can only access static members
        return alive;
    }

    ~Person(){//Destructor
    cout<<"Destructor called"<<endl;
    }
};
// Definition of printAge using scope resolution operator ::
void Person::printAge(){
    cout<<"Age"<<age<<endl;//Age is private so can't access
}
//Initialize the static variable
bool Person::alive = true;//data type-> class -> name = value
int main(){
    //Static allocation
    Person ayush;//ayush is object of class Person

    //Dynamic allocation
    Person* ayush = new Person(18);//Calls Parametrized constructor
    //Here ayush is address so we have to dereference it to call fn
    (*ayush).getDetails();
    //A better way to write it
    ayush->getDetails();
    //Destructor call manually for dynamic allocation of obj 
    delete ayush;

    //Directly accessing the data members and functions
    // ayush.name = "Ayush";//Accessing a data member
    // ayush.age = 21;
    // ayush.id = 02214803118;

    //Getter and setter
    ayush.setDetails("Ayush",21,022);//Sets the details
    ayush.getDetails();//Accessing member function

    //Copy Constructor
    Person saharsh(ayush);
    
    //Function outside the class(gives error as age is private)
    ayush.printAge();//Accessing member function outside class

    //Shallow copy
    Person ayush;
    ayush.setDetails("Ayush",21,022);//Sets the details
    char alias[10] = 'CapCool';
    //Use default copy constructor(makes shallow copy)
    Person saharsh(ayush);//Makes a same copy of ayush
    ayush.alias[3] = 'F';//Makes alias CapFool
    //If we print saharsh alias now -> it's also changed to CapFool

    //Deep copy
    Person ayush;
    ayush.setDetails("Ayush",21,022);//Sets the details
    char alias[10] = 'CapCool';
    //Use own custom copy constructor(makes deep copy)
    Person saharsh(ayush);//Makes a same copy of ayush
    ayush.alias[3] = 'F';//Makes alias CapFool
    //If we print saharsh alias now -> it's not changed to CapFool

    //Call static variable
    cout<< Person::alive<<endl;//Call without creating obj
    //Call static function
    cout<< Person::status()<<endl;//Call without creating obj

    return 0;
}


// Pillars of OOPS
// 1. Encapsulation (Wrapping of data in single entity)
class Student {
    // private data members
    private:
    string studentName;
    int studentRollno;
    int studentAge;

    // get method for student name to access  
    // private variable studentName
    public:
    string getStudentName() {
        return studentName;
    }

    // set method for student name to set 
    // the value in private variable studentName
    void setStudentName(string studentName) {
        this->studentName = studentName;
    }

    // get method for student rollno to access  
    // private variable studentRollno
    int getStudentRollno() {
        return studentRollno;
    }

    // set method for student rollno to set 
    // the value in private variable studentRollno
    void setStudentRollno(int studentRollno) {
        this->studentRollno = studentRollno;
    }

    // get method for student age to access  
    // private variable studentAge
    int getStudentAge() {
        return studentAge;
    }

    // set method for student age to set 
    // the value in private variable studentAge
    void setStudentAge(int studentAge) {
        this->studentAge = studentAge;
    }
};
int main() {
    Student obj;
    // setting the values of the variables
    obj.setStudentName("Ayush");
    obj.setStudentRollno(1022);
    obj.setStudentAge(21);
    // printing the values of the variables
    cout << "Student Name : " << obj.getStudentName() << endl;
    cout << "Student Rollno : " << obj.getStudentRollno() << endl;
    cout << "Student Age : " << obj.getStudentAge();
}


// 2. Inheritance (Inherit properties from existing class)
// class parent_class {};
// class child_class: access_modifier parent_class {};

// Single Inheritance
class Animal {// Parent class
    public:
    void eat() {
        cout << "eating" << endl;
    }
};
class Dog: public Animal {// Child class
    public:
    void bark(){
        cout << "barking";
    }
};
int main() {
    // Creating an object of the child class
    Dog obj;
    // calling methods
    obj.eat();//accessing the parent member function
    obj.bark();
}

// Multilevel Inheritance
class Animal {
    public:
    void eat() {
        cout << "eating" << endl;
    }
};
class Dog: public Animal {// Child class
    public:
    void bark() {
    cout << "barking" << endl;
    }
};
class BabyDog: public Dog {
    public:
    void weep() {
        cout << "weeping";
    }
};
int main() {
    // Creating an object of the child class
    BabyDog obj;
    // can access all methods of ancestors
    obj.eat();
    obj.bark();
    obj.weep();
}

// Multiple Inheritance
class Animal {// Parent class
    public:
    void eat() {
        cout << "eating" << endl;
    }
};
class Dog {//Another parent
    public:
    void bark() {
        cout << "barking" << endl;
    }
};
// Inherited both parents
class BabyDog: public Animal, public Dog {
    public:
    void weep() {
        cout << "weeping";
    }
};
int main() {
    // Creating an object of the child class
    BabyDog obj;
    // calling methods
    obj.eat();
    obj.bark();
    obj.weep();
}

// Hierarchial Inheritance
class Animal {// Parent class
    public:
    void eat() {
        cout << "eating" << endl;
    }
};
class Dog: public Animal {// child class1
    public:
    void bark() {
        cout << "barking" << endl;
    }
};
class Cat: public Animal {// child class2
    public: void meow() {
        cout << "meowing" << endl;
    }
};
int main() {
    Cat obj;
    // Can only access itself and parent class methods not sibling(dog)
    obj.eat();
    obj.meow();
}

// Hybrid Inheritance
class Vehicle {// Parent class1
    public:
    Vehicle() {
        cout << "This is a Vehicle" << endl;
    }
};
class Fare {//Parent class2 
    public:
    Fare() {
        cout << "Fare of Vehicle\n";
    }
};
//Child class1
class Car: public Vehicle {};
//Child class2 
class Bus: public Vehicle, public Fare {};
// main function 
int main() {
    // creating object of sub class will 
    // invoke the constructor of base class 
    Bus obj2;
    return 0;
}


// 3. Polymorphism (Many forms)

// Compile time polymorphism
// Function Overloading
int add(int num1, int num2) {
    return num1 + num2;
}
// Function with three parameters
int add(int num1, int num2, int num3) {
    return num1 + num2 + num3;
}
int main() {
    cout << add(10, 20) << endl;
    cout << add(10, 20, 30);
    return 0;
}
// Operator Overloading
class Complex {
    private:
        int real, imag;
    public:
        Complex(int r = 0, int i = 0) {
            real = r;
            imag = i;
        }
    // This is automatically called when '+' is used with 
    // between two Complex objects 
    Complex operator + (Complex const & b) {
        Complex a;
        a.real = real + b.real;
        a.imag = imag + b.imag;
        return a;
    }
    void print() {
        cout << real << " + i" << imag << endl;
    }
};
int main() {
    Complex c1(10, 5), c2(2, 4);
    Complex c3 = c1 + c2; // An example call to "operator+" 
    c3.print();
}

// Runtime Polymorphism
// Method Overriding
class Parent {
    public:
        void show() {
            cout << "Inside parent class" << endl;
        }
};
class subclass1: public Parent {
    public: void show() {
        cout << "Inside subclass1" << endl;
    }
};
class subclass2: public Parent {
    public: void show() {
        cout << "Inside subclass2";
    }
};
int main() {
    subclass1 o1;
    subclass2 o2;
    o1.show();
    o2.show();
}


// Friend Function
class Rectangle {
    private:
        int length;
    public:
        Rectangle() {
            length = 10;
        }
    friend int printLength(Rectangle); //friend function    
};
int printLength(Rectangle b) {
    b.length += 10;//Can access private data members inside the class
    return b.length;
}
int main() {
    Rectangle b;
    cout << "Length of Rectangle: " << printLength(b) << endl;
    return 0;
}