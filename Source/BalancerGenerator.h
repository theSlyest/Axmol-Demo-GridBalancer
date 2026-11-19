#pragma once

#include <functional>

#include "2d/DrawNode.h"
#include "2d/Label.h"
#include "2d/Menu.h"

class BalancerGenerator : public ax::DrawNode
{
public:
    static BalancerGenerator* create(const ax::Color4F& color, const std::string& name);

    virtual bool init(const ax::Color4F& color, const std::string& name);

    // Fired when the player clicks an arrow.
    std::function<void()> onIncrease;
    std::function<void()> onDecrease;

    // Show a level between 0 and 1 on the bar.
    void setValue(float value) const;

    // Enable or disable the arrow buttons.
    void setEnabled(bool enabled) const;

private:
    static const ax::Size SIZE;
    static const ax::Color4F BG_COLOR;
    static const ax::Color4F BORDER_COLOR;
    static constexpr float BORDER = 4.0f;
    static constexpr float SPACING = 16.0f;
    static constexpr float BAR_PADDING = 4.0f;
    static constexpr float BAR_HEIGHT = 160.0f;
    
    ax::Label* _label = nullptr;
    ax::DrawNode* _bar = nullptr;
    ax::Menu* _menu = nullptr;
};
