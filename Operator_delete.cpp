#include <iostream>
#include <new>
#include <memory>

void* operator new(size_t n) {
    std::cout << n << std::endl;
    return malloc(n);
}
void operator delete(void *ptr) noexcept {
    free(ptr);
}

void* operator new[](size_t n) {
    std::cout << n << std::endl;
    return malloc(n);
}

void operator delete[](void *ptr) noexcept {
    free(ptr);
}


class Base {
protected:
    // A non-virtual protected destructor prevents accidental polymorphic deletion
    // but allows derived classes to access it for cleanup.
    ~Base() {
        std::cout << "Base destructor called." << std::endl;
    }
public:
    // This is the only way to destroy an object.
    void operator delete(Base* p, std::destroying_delete_t) {
        if (!p) return;

        std::cout << "Base destroying operator delete called." << std::endl;

        // At this point, no destructors have been called.
        // We can inspect the object via the Base pointer.

        // We must manually invoke the destructor.
        // The virtual dispatch mechanism is not used here.
        p->~Base();

        ::operator delete(p);
    }
};

class CustomObject : public Base {
private:
    int m_value;
protected:
    // CustomObject's destructor is automatically called by the compiler
    // before Base's destructor, as per C++ rules.
    ~CustomObject() {
        std::cout << "CustomObject destructor called, value is: " << m_value << std::endl;
    }
public:
    CustomObject(int val) : m_value(val) {
        std::cout << "CustomObject created with value: " << m_value << std::endl;
    }
};

int main() {
    // We cannot create an object on the stack if the destructor is not public
    // CustomObject obj(10); // Compiler error: 'CustomObject::~CustomObject()' is protected

    CustomObject* obj = new CustomObject(42);

    // Deleting through a base class pointer that uses destroying_delete_t
    delete obj;

    return 0;
}