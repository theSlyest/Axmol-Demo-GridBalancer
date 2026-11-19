#pragma once

#include <array>
#include <memory>

#include "2d/DrawNode.h"
#include "2d/Label.h"
#include "2d/Scene.h"
#include "BalancerGame.h"
#include "BalancerValue.h"
#include "BalancerGenerator.h"
#include "BalancerChart.h"

class BalancerScene : public ax::Scene
{
public:
    bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(BalancerScene);

    void update(float dt) override;

private:
    const float UI_OFFSET = 32.0f;
    
    struct GeneratorSpec
    {
        std::string name;
        ax::Color4F color;
        float rate; // how fast the bar moves toward its target, in full ranges per second
    };

    const std::array<GeneratorSpec, 3> GENERATORS = {{
        { "FAST",   ax::Color4F(0.4f, 1.0f, 0.4f, 1.0f), 0.5f },
        { "MEDIUM", ax::Color4F(0.2f, 0.6f, 1.0f, 1.0f), 0.25f },
        { "SLOW",   ax::Color4F(1.0f, 0.2f, 1.0f, 1.0f), 0.125f }
    }};
    const char* BEST_KEY = "Best";

    int _best = 0;

    std::unique_ptr<BalancerGame> _game;

    BalancerValue* _upTimeUi = nullptr;
    BalancerValue* _strikesUi = nullptr;
    BalancerValue* _bestUi = nullptr;

    std::vector<BalancerGenerator*> _gens;

    BalancerChart* _chart = nullptr;

    ax::DrawNode* _endLayer = nullptr;
    ax::Label* _upTimeLbl = nullptr;
    ax::Label* _bestLbl = nullptr;

    void setBest(int best);

    void initGame();
    void initGenerators(const ax::Vec2& size, const ax::Vec2& origin);
    void initEndLayer(const ax::Vec2& size, const ax::Vec2& origin);

    void gameOver();
    void reset();
};
