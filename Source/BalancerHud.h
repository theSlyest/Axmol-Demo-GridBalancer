#pragma once

#include "2d/Node.h"
#include "BalancerValue.h"

// The three boxes along the top of the screen: uptime, strikes and best score.
class BalancerHud : public ax::Node
{
public:
    // The HUD covers an area of the given size; place the node at the visible origin.
    static BalancerHud* create(const ax::Vec2& size);

    bool init(const ax::Vec2& size);

    void setUpTime(float seconds) const;
    void setStrikes(int strikes) const;
    void setBest(int seconds) const;

    // Bottom edge of the boxes, in the HUD's own coordinates.
    float getBottom() const;

private:
    static constexpr float OFFSET = 32.0f;

    BalancerValue* _upTime = nullptr;
    BalancerValue* _strikes = nullptr;
    BalancerValue* _best = nullptr;
};
