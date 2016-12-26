/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#include "Exception.h"

Exception::Exception(int errcode, const char *msg)
    : errcode(errcode), message(msg) {

}

Exception::~Exception() throw(){

}

const char* Exception::what() const throw(){
    return this->message;
}

const int Exception::code()  const throw() {
    return this->errcode;
}
