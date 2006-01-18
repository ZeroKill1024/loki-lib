////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2006 Peter K�mmel
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author makes no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// $Header:

#define LOKI_CLASS_LEVEL_THREADING

#include "Thread.h"

#include <loki/LockingPtr.h>
#include <loki/SafeFormat.h>

using namespace Loki;


int g;
int numThreads = 10;
int loop = 5;


struct A
{
#define  DO for(int i=0; i<10000000; i++) g++;

    void print(void* id)
    {
        DO;Printf("%p: ----------------\n")(id);
        DO;Printf("%p: ---------------\n")(id);
        DO;Printf("%p: --------------\n")(id);
        DO;Printf("%p: -------------\n")(id);
        DO;Printf("%p: ------------\n")(id);
        DO;Printf("%p: -----------\n")(id);
        DO;Printf("%p: ----------\n")(id);
        DO;Printf("%p: ---------\n")(id);
        DO;Printf("%p: --------\n")(id);
        DO;Printf("%p: -------\n")(id);
        DO;Printf("%p: ------\n")(id);
        DO;Printf("%p: -----\n")(id);
        DO;Printf("%p: ----\n")(id);
        DO;Printf("%p: ---\n")(id);
        DO;Printf("%p: --\n")(id);
        DO;Printf("%p: -\n")(id);
        DO;Printf("%p: \n")(id);
        DO;Printf("%p: \n")(id);
    }
};

typedef Loki::LockingPtr<A,Loki::Mutex> LPtr;

void* RunLocked(void *id)
{
    A a;
    static Loki::Mutex m;    
    for(int i=0; i<loop; i++)
    {
        LPtr l(a,m);
        l->print(id);
    }
    return 0;
}

void* Run(void *id)
{
    A a;
    for(int i=0; i<loop; i++)
        a.print(id);
    return 0;
}

int main ()
{
    std::vector<Thread*> threads;

    for(int i=0; i<numThreads; i++)
    {
        Printf("Creating thread %d\n")(i);
        threads.push_back(new Thread(RunLocked,(void*)i));
    }
    for(int i=0; i<numThreads; i++)
        threads.at(i)->start();

    Thread::JoinThreads(threads);
    Thread::DeleteThreads(threads);

    Printf("--------------------------------------------------------------------------------------\n");
    Printf("--------------------------------------------------------------------------------------\n");
    Printf("--------------------------------------------------------------------------------------\n");

    for(int i=0; i<numThreads; i++)
    {
        Printf("Creating thread %d\n")(i);
        threads.push_back(new Thread(Run,(void*)i));
    }
    for(int i=0; i<numThreads; i++)
        threads.at(i)->start();

    Thread::JoinThreads(threads);
    Thread::DeleteThreads(threads);
}

