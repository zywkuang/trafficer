#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "src/net/InetAddress.h"
#include "src/base/Json.h"

void *thr_fn(void *arg) {

    printf("Hello Wrold, %d.\n", pthread_self());

    pthread_join(pthread_self(), 0);

    sleep(2);

    printf("Detach Thread.\n");

    pthread_detach(pthread_self());

    sleep(4);

    printf("Exit Thread.\n");
}

void thread_test() {

    pthread_t tid;
    pthread_create(&tid, NULL, thr_fn, NULL);

    //pthread_join(tid, 0);
    //pthread_detach(tid);

    while(true) {
        sleep(1);
        printf("HHHHH\n");
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    InetAddress sa("192.168.1.1", 1024);

    std::cout << sa.toIpPortString() << std::endl;
    std::cout << sa.toIpString() << std::endl;
    std::cout << sa.getPortNumber() << std::endl;

    InetAddress *psa = new InetAddress(1024);
    InetAddress::resolveHostName("zjl-kb310", psa);

    std::cout << psa->toIpPortString() << std::endl;
    std::cout << psa->toIpString() << std::endl;
    std::cout << psa->getPortNumber() << std::endl;


    JsonObject *json = cJsonCreateObject();
    cJsonAddIntToObject(json, "age", 23);
    cJsonAddStringToObject(json, "name", "zhaojl");
    cJsonAddIntToObject(json, "grade", 100);

    std::cout << cJsonPrint(json) << std::endl;
    std::cout << cJsonPrintUnformatted(json) << std::endl;
    cJsonDelete(json);

    thread_test();

    return 0;
}