#include <iostream>
#include <cstring>

#define MEMSPACE 10000
#define MES_SIZE 256

class ChainedException : public std::exception {
private:
    ChainedException *      prev_;
    static char             memory_     [MEMSPACE];
    char                    message_    [MES_SIZE];
    static char *           head_; //the position in memory, which is full
public:
    ChainedException   ();
    ChainedException   (const char *, ChainedException *prev = nullptr);
    ChainedException   (const ChainedException &) = delete;
    ChainedException   (ChainedException &&);
    virtual ~ChainedException  ();

    void * operator new (std::size_t count);
    void operator delete(void *ptr, std::size_t count);
    virtual const char * what   () const noexcept override;
    void pew();
};
char ChainedException::memory_[MEMSPACE] = {};
char* ChainedException::head_ = ChainedException::memory_;

void * ChainedException::operator new(std::size_t count)
{
    head_ += sizeof(ChainedException);
    return head_ - sizeof(ChainedException);
}

void ChainedException::operator delete(void *ptr, std::size_t count)
{
    head_ -= sizeof(ChainedException);
}

ChainedException::ChainedException() :
    prev_       (nullptr)
{
    strncpy(message_, "ChainedException", MES_SIZE);
}


ChainedException::ChainedException(const char * string, ChainedException * prev) :
    prev_           (prev)
{
    strncpy(message_, string, MES_SIZE);
}

ChainedException::ChainedException(ChainedException && other) :
    prev_       (other.prev_)
{
    strncpy(message_, other.message_, MES_SIZE);
    other.prev_ = nullptr;
}

const char* ChainedException::what() const noexcept
{
    return message_;
}

ChainedException::~ChainedException()
{
    delete prev_;
}

void ChainedException::pew()
{
    ChainedException *p = this;
    while(p != nullptr) {
        std::cout << p->message_ << std::endl;
        p = p->prev_;
    }
}

void boo()
{
    throw ChainedException("boo");
}

void foo()
{
    try{
        boo();
    } catch (ChainedException &e) {
        throw ChainedException("foo", new ChainedException(std::move(e)));
    }
}

int main() {
    try {
        foo();
    } catch (ChainedException &e) {
        e.pew();
    }
    return 0;
}