//
// Created by zjl on 10/28/16.
//

#include "Event.h"
#include "../base/Exception.h"

Event::Event()
    : flag(0),
      bsem(false) {

}

Event::Event(bool bsem)
    : flag(0),
      bsem(bsem) {

}

Event::~Event() {

}

void Event::set() {

    try {
        MutexLockGuard guard(&this->mutex);

        this->flag++;

    } catch (Exception e) {
        printf("Exception Info: [%d, %s].\n", e.code(), e.what());
        throw Exception(EEVENTSET, "Event Set Exception");
    }
}

void Event::wait() {

    try {
        MutexLockGuard guard(&this->mutex);

        while (this->flag == 0)
            this->condition.wait(&this->mutex);

        if (bsem)
            this->flag--;
        else
            this->flag = 0;

    } catch (Exception e) {
        printf("Exception Info: [%d, %s].\n", e.code(), e.what());
        throw Exception(EEVENTWAIT, "Event Wait Exception");
    }
}