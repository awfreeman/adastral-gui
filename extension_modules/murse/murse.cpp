#include "murse.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
using namespace std;
void Murse::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("gimmethat"), &Murse::);
}

Murse::Murse(){
    if (pipe(out_pipe)!=0){
        throw;
    }
    murse_mutex = PTHREAD_MUTEX_INITIALIZER;

}
Murse::~Murse(){

}

void output_callback_reciever(int pipe, pthread_mutex_t *mutex, char *line, int length){
    pthread_mutex_lock(mutex);
    write(pipe, line, length);
    pthread_mutex_unlock(mutex);
}

Variant Murse::start_update(Variant dl_url, Variant game_dir, Variant key){
    
}

Variant Murse::start_verify(Variant path, Variant dl_url, Variant key){
    
}

Variant Murse::start_repair(Variant path, Variant dl_url, Variant key){
    
}
Variant Murse::complete(){

}
Variant Murse::is_complete(){
}

Variant Murse::get_lines(){
    
}