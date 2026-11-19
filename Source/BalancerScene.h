#pragma once

#include <array>
#include <memory>

#include "2d/Scene.h"
#include "BalancerChart.h"
#include "BalancerGame.h"
#include "BalancerGameOverLayer.h"
#include "BalancerGenerator.h"
#include "BalancerHud.h"
#include "BestScore.h"

class BalancerScene : public ax::Scene
{
public:
    bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(BalancerScene);

    void update(float dt) override;

private:
    const float UI_OFFSET = 32.0f;
    const float GENERATOR_SPACING = 240.0f; // distance between two generators, centered on the screen
    
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

    std::unique_ptr<BalancerGame> _game;
    BestScore _best;

    BalancerHud* _hud = nullptr;

    std::vector<BalancerGenerator*> _gens;

    BalancerChart* _chart = nullptr;

    BalancerGameOverLayer* _endLayer = nullptr;

    void initGame();
    void initGenerators(const ax::Vec2& size, const ax::Vec2& origin);
    void initEndLayer(const ax::Vec2& size, const ax::Vec2& origin);

    void gameOver();
    void reset();
};
