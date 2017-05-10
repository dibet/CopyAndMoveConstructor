#include <QCoreApplication>
#include <iostream>

class A {

public:

    std::vector<int> p;
    int size;
    int * q;



    A() : size(0), q(new int[0]) {
        p.clear();
        std::cout << "A()" << std::endl;

    }



    A(int s) : size(s),  q(new int[s]) {
        p.resize(s);
        std::cout << "A(int s)" << std::endl;
    }





    A(const A& a) : size(a.size), q(new int[a.size]){
        std::copy(a.p.begin(),a.p.end(), std::back_inserter(this->p));
        std::copy(a.q, a.q + a.size, this->q);

        std::cout << "A() de copy" << std::endl;
    }



    A(A&& a) : q(NULL), size(0){
        p.clear();

        *this = std::move(a);

        std::cout << "A() de move" << std::endl;
    }


    A& operator=(A&& a){

        if (this != &a){
            delete[] q;
            p.clear();

            q = a.q;
            size = a.size;
            this->p = std::move(a.p);

            a.q = NULL;
            a.p.clear();
            a.size = 0;
        }
        std::cout << "op = " << std::endl;
        return *this;
    }





};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    A a1;
    A a2(2);
    a2.p.at(0) = 1;
    a2.p.at(1) = 2;
    a2.q[0] = 3;
    a2.q[1] = 4;

    A a3(a2);
    A a4(4);

    a4.p.at(0) = 5;
    a4.p.at(1) = 6;
    a4.p.at(2) = 7;
    a4.p.at(3) = 8;
    a4.q[0] = 9;
    a4.q[1] = 10;
    a4.q[2] = 11;
    a4.q[3] = 12;

    A a5 = a4;

    A a6(a4);
    A a7 = std::move(a6);

    std::cout << "finish" << std::endl;

    return 0;
}
