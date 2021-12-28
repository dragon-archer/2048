#ifndef _COMMMON_H
#define _COMMMON_H 1

#include <Pch.h>

size_t ReadBestScore(const std::string& filename = std::string());
bool WriteBestScore(const std::string& filename, size_t bestScore = 0);

#endif /* _COMMON_H */
