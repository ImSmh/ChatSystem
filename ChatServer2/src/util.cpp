#include "util.h"

bool OpenForWrite(std::ofstream& ofs, const std::string& filename, std::ios_base::openmode mode)
{
    // 尝试打开文件
    ofs.open(filename, mode);
    
    // 如果文件未打开，尝试创建目录并重新打开
    if (!ofs.is_open()) {
        std::filesystem::path filePath(filename);
        std::filesystem::path dir = filePath.parent_path();

        // 创建目录（如果不存在）
        if (!dir.empty() && !std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
        }

        // 再次尝试打开文件
        ofs.open(filename, mode);
    }

    return ofs.is_open();
}
