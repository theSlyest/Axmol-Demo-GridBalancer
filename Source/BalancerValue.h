#pragma once

#include "2d/DrawNode.h"
#include "2d/Label.h"

class BalancerValue : public ax::DrawNode
{
public:
    static BalancerValue* create(const ax::Color4F& color, const std::string& name);

    virtual bool init(const ax::Color4F& color, const std::string& name);

    void setValue(const std::string& value) const { _label->setString(_title + ": " + value); }

private:
    static ax::Vec2 PADDING;
    static ax::Color4F BG_COLOR;
    static constexpr float BORDER = 4.0f;

    std::string _title;
    ax::Label* _label = nullptr;
};
