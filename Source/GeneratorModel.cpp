#include "GeneratorModel.h"

#include <algorithm>

void GeneratorModel::reset(const float value)
{
    _value = std::clamp(value, 0.0f, 1.0f);
    _target = _value;
}

void GeneratorModel::increase()
{
    _target = std::min(1.0f, _target + STEP);
}

void GeneratorModel::decrease()
{
    _target = std::max(0.0f, _target - STEP);
}

void GeneratorModel::update(const float dt)
{
    const float shift = dt * _rate;
    if (_value < _target)
        _value = std::min(_value + shift, _target);
    else
        _value = std::max(_value - shift, _target);
}
