#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#include <vector>
#include <iostream>
#include <thread>

#define BUF_SIZE 2048
#define BIND_ERROR -2
#define CREATE_ERROR -1
#define CONNECTION_ERROR -3
