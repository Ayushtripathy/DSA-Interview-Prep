// Overview of Classes and Objects
class Person {//Person is class
    public://access specifier
    string name;
    int id;//data members
    int age;

    void printAge();//member function declared outside the class

    void getDetails(){//member function declared inside the class
      cout<<"Name"<<name<<"Roll No."<<id<<endl;
    }
};
// Definition of printAge using scope resolution operator ::
void Person::printAge(){
    cout<<"Age"<<age<<endl;
}
int main(){
    Person ayush;//ayush is object of class Person

    ayush.name = "Ayush";//Accessing a data member
    ayush.age = 21;
    ayush.id = 02214803118;

    ayush.printAge();//Accessing member function outside class
    ayush.getDetails();//Accessing member function
    return 0;
}