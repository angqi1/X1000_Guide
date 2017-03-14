#include<Mutex.h>

void Mutex::lock()
{
        pthread_mutex_lock(&mutex);

}

void Mutex::unlock()
{
        pthread_mutex_unlock(&mutex);

}

Mutex::Mutex()
{
        pthread_mutex_init(&mutex, NULL);

}

Mutex::~Mutex()
{
        pthread_mutex_destroy(&mutex);
}


