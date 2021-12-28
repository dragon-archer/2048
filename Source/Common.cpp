#include <Pch.h>
#include <Common.h>

size_t ReadBestScore(const std::string& filename)
{
    std::ifstream f(filename);
    if(!f.is_open())
    {
        return 0;
    }
    size_t ans;
    f >> ans;
    f.close();
    return ans;
}

bool WriteBestScore(const std::string& filename, size_t bestScore)
{
    std::ofstream f(filename);
    if(!f.is_open())
    {
        return false;
    }
    f << bestScore;
    f.close();
    return true;
}
