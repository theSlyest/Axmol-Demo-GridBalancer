#include "BalancerGame.h"

#include <cmath>

BalancerGame::BalancerGame(Config config, DemandCurve::Random random)
    : _config(std::move(config)), _demand(std::move(random))
{
    for (const float rate : _config.generatorRates)
        _generators.emplace_back(rate);
}

void BalancerGame::reset()
{
    for (auto& generator : _generators)
        generator.reset(_config.startValue);

    _demand.reset(_config.startValue);
    _supply = _config.startValue;
    _downTime = 0.0f;
    _over = false;

    setStrikes(_config.strikes);
    setUpTime(0.0f);
    if (onGraceChanged)
        onGraceChanged(false, 0.0f);
}

void BalancerGame::update(const float dt)
{
    if (_over)
        return;

    float supply = 0.0f;
    for (auto& generator : _generators) {
        generator.update(dt);
        supply += generator.getValue();
    }
    _supply = supply / static_cast<float>(_generators.size());
    _demand.update(dt);

    if (std::abs(_supply - _demand.getValue()) > _config.tolerance) {
        _downTime += dt;
        if (onGraceChanged)
            onGraceChanged(true, _downTime);

        if (_downTime >= _config.gracePeriod) {
            setStrikes(_strikes - 1);
            _downTime -= _config.gracePeriod;
            if (_strikes == 0) {
                _over = true;
                if (onGameOver)
                    onGameOver();
            }
        }
    }
    else {
        _downTime = 0.0f;
        if (onGraceChanged)
            onGraceChanged(false, 0.0f);
        setUpTime(_upTime + dt);
    }
}

void BalancerGame::increase(const size_t generator)
{
    if (!_over)
        _generators[generator].increase();
}

void BalancerGame::decrease(const size_t generator)
{
    if (!_over)
        _generators[generator].decrease();
}

void BalancerGame::setStrikes(const int strikes)
{
    _strikes = strikes;
    if (onStrikesChanged)
        onStrikesChanged(strikes);
}

void BalancerGame::setUpTime(const float upTime)
{
    _upTime = upTime;
    if (onUpTimeChanged)
        onUpTimeChanged(upTime);
}
