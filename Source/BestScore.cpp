#include "BestScore.h"

#include "UserDefault.h"

namespace {
constexpr auto KEY = "Best";
}

BestScore::BestScore() : _best(ax::UserDefault::getInstance()->getIntegerForKey(KEY, 0))
{
}

bool BestScore::submit(const int seconds)
{
    if (seconds <= _best)
        return false;

    _best = seconds;
    const auto userDefault = ax::UserDefault::getInstance();
    userDefault->setIntegerForKey(KEY, seconds);
    userDefault->flush();
    return true;
}
