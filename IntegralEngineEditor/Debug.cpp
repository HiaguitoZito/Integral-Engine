#include <iostream>

class Foo
{
     int x_;
public:
     int x() const { return x_; }
     void x(int x) { x_ = std::move(x); }
};
Foo operator*(Foo& f, const Foo& f2){
    f.x(f.x() * f2.x());
    return f;
}

int main(){
    Foo f = Foo();
    Foo f2 = Foo();
    f.x(10);
    f2.x(30);
    f = f * f2;
    std::cout << f.x() << std::endl;
    return 0;
}