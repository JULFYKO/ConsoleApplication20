#include <iostream>
#include <vector>
#include <typeinfo>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Grandpa {
public:
    Grandpa(const string& name) : name(name) {}
    virtual ~Grandpa() = default;

    virtual void Sleep() const {
        cout << typeid(*this).name() << " sleep" << endl;
    }

private:
    string name;
};

class Daddy : public Grandpa {
public:
    Daddy(const string& name) : Grandpa(name) {}

    virtual void Walk() const {
        cout << typeid(*this).name() << " walk" << endl;
    }

    virtual void Sleep() const override {
        cout << typeid(*this).name() << " sleep" << endl;
    }
};

class Son : public Daddy {
public:
    Son(const string& name) : Daddy(name) {}

    virtual void Walk() const override {
        cout << typeid(*this).name() << " walk" << endl;
    }

    virtual void Sleep() const override {
        cout << typeid(*this).name() << " sleep" << endl;
    }

    virtual void Play() const {
        cout << typeid(*this).name() << " play" << endl;
    }
};

void printWithDynamicCast(vector<Grandpa*>& family) {
    cout << "Using dynamic_cast:" << endl;
    for (Grandpa* item : family) {
        item->Sleep();
        if (auto daddy = dynamic_cast<Daddy*>(item)) {
            daddy->Walk();
        }
        if (auto son = dynamic_cast<Son*>(item)) {
            son->Play();
        }
    }
}

void printWithTypeid(vector<Grandpa*>& family) {
    cout << "Using typeid:" << endl;
    for (Grandpa* item : family) {
        item->Sleep();
        if (typeid(*item) == typeid(Daddy)) {
            static_cast<Daddy*>(item)->Walk();
        }
        else if (typeid(*item) == typeid(Son)) {
            static_cast<Son*>(item)->Walk();
            static_cast<Son*>(item)->Play();
        }
    }
}

int main() {
    vector<Grandpa*> family{
        new Grandpa("Ivan"),
        new Daddy("Matviy"),
        new Son("Pavlo")
    };

    printWithDynamicCast(family);
    printWithTypeid(family);

    for (Grandpa* member : family) {
        delete member;
    }

    return 0;
}
