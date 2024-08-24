#ifndef UTIL_H
#define UTIL_H


#include <thread>
#include <fstream>
#include <filesystem>

class Noncopyable{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;

    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

inline std::thread::id GetThreadId()
{
    return std::this_thread::get_id();
}

bool OpenForWrite(std::ofstream& ofs, const std::string& filename, std::ios_base::openmode mode);



#endif // COMMON_H
