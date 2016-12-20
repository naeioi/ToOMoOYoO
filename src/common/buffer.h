#ifndef __BUFFER_H
#define __BUFFER_H

namespace TMY {

class Buffer {
private:
    char *data;
public:
    Buffer() {
        data = NULL;
    }
    Buffer(char * data_) {
        data = data_;
    }   
    ~Buffer() {
        try {
            delete data;
        }
        catch(e) {}
    }
    char* raw() {
        return data;
    }
};

}

#endif