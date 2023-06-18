#ifndef MURSE_H
#define MURSE_H

#include <godot_cpp/classes/object.hpp>
#include <pthread.h>
#include <unistd.h>
#include "murse_c_export.h"

namespace godot {
    class Murse : public Object{
        GDCLASS(Murse, Object)
        private:
            pthread_t murse_thread;
            pthread_mutex_t murse_mutex;
            int out_pipe[2];
        protected:
            static void _bind_methods();
        public: 
            Murse();
            ~Murse();
            Variant start_update(Variant path, Variant dl_url, Variant key);
            Variant start_verify(Variant path, Variant dl_url, Variant key);
            Variant start_repair(Variant path, Variant dl_url, Variant key);
            Variant complete();
            Variant is_complete();
            Variant get_lines();

    };
}

#endif