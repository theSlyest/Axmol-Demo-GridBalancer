#pragma once

#include <functional>

#include "2d/DrawNode.h"
#include "2d/Label.h"

// The "Out of strikes" panel with the banked uptime, the best score and a
// Play Again button.
class BalancerGameOverLayer : public ax::DrawNode
{
public:
    bool init() override;

    CREATE_FUNC(BalancerGameOverLayer);

    // Fired when the player presses Play Again.
    std::function<void()> onPlayAgain;

    void show(int upTime, int best);
    void hide() { setVisible(false); }

private:
    static constexpr ax::Vec2 SIZE = ax::Vec2(400.0f, 300.0f);

    ax::Label* _upTimeLbl = nullptr;
    ax::Label* _bestLbl = nullptr;
};
