#ifndef MURSE_H
#define MURSE_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/thread.hpp>
//#include "murse_c_export.h"

namespace godot {
    class Murse : public Object{
        GDCLASS(Murse, Object)
        private:
            //Mutex output_mutex;
            //Array output_lines;
            //Thread murse_thread;
            //void output_callback_reciever(const char *line);
        protected:
            static void _bind_methods();
        public: 
            Murse();
            ~Murse();
            Variant gimmethat();
    };
}

#endif