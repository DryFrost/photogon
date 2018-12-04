#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX_NAME_LENGTH 20

using namespace std;

class client {
public:
    char *name;
    int id;
    int sock;
public:
    client();
    void SetName(const char *name);
    void SetId(int id);
};

#endif // CLIENT_H
