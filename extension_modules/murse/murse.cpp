#include "murse.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Murse::_bind_methods() {
    ClassDB::bind_method(D_METHOD("gimmethat"), &Murse::gimmethat);
}

Murse::Murse(){

}
Murse::~Murse(){

}

Variant Murse::gimmethat(){
    return Variant("Hello Godot 4 i hate c++");
}