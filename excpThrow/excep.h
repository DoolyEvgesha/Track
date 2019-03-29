#ifndef EXCPTHROW_EXCEP_H
#define EXCPTHROW_EXCEP_H

static std::ofstream fout("logFile.txt");

enum NUMS{
    MAX_NUM_EXCEP = 10
};

class MyException{
private:
    //some kind of array to store the information
    std::string info_;
public:
    MyException                 ();
    ~MyException                ();

    const char* what    () const noexcept;
    //const char*         exwhat  () const noexcept;
    void * operator     new     (size_t size);

};

#endif //EXCPTHROW_EXCEP_H
